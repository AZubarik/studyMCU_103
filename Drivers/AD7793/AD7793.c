#include "AD7793.h"
#include "spi.h"
#include "gpio.h"
#include "stm32f1xx_it.h"

extern uint16_t pinNumber;

void AD7793_Init(void)
{
  uint8_t init_command[3] = {0x50, 0x00, 0x00};
  send_to_SPI(init_command, sizeof(init_command));
}

void AD7793_Reset(void)
{
  uint8_t dataToSend[5] = {0x03, 0xff, 0xff, 0xff, 0xff};
  send_to_SPI(dataToSend, sizeof(dataToSend));
}

void AD7793_WaitRdyGoLow(void)
{
  while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) != GPIO_PIN_RESET)
  {
  }
}

void AD7793_Mode_Register(uint8_t mode, uint8_t clksrc, uint8_t rate)
{
  uint8_t mode_comand[3] = {AD7793_REG_MODE, 0x00, 0x00};
  mode_comand[1] = mode << 5;
  mode_comand[2] = (clksrc << 6) + rate;
  HAL_GPIO_WritePin(GPIOB, pinNumber, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, mode_comand, 3, 1);
}

void AD7793_Configuration_Register(uint8_t vbias, uint8_t gain, uint8_t refsel, uint8_t channel)
{
  uint8_t vbias_gain = (vbias << 6) + gain;
  uint8_t refsel_chanel = 0x10 | ((refsel << 7) + channel);

  uint8_t conf_command[3] = {AD7793_REG_CONF, vbias_gain, refsel_chanel};
  send_to_SPI(conf_command, sizeof(conf_command));
}

void AD7793_IO_Register(uint8_t direction, uint8_t current)
{
  uint8_t io_comand[2] = {AD7793_REG_IO, current};
  io_comand[1] = (direction << 2) + current;
  send_to_SPI(io_comand, sizeof(io_comand));
}

void AD7793_Calibrate(uint8_t mode, uint8_t channel)
{
  AD7793_Configuration_Register(0, 0, 0, channel);
  AD7793_Mode_Register(mode, 0, 0);
  AD7793_WaitRdyGoLow();
  HAL_GPIO_WritePin(GPIOB, pinNumber, GPIO_PIN_SET);
}

unsigned long AD7793_SingleConversion(void)
{
  AD7793_Mode_Register(AD7793_MODE_SINGLE, AD7793_CLK_INT, AD7793_RATE_16_7_50_60);
  AD7793_WaitRdyGoLow();
  uint8_t conf[4] = {AD7793_REG_DATA};
  uint8_t out[4] = {0x00, 0x00, 0x00, 0x00};

  HAL_SPI_TransmitReceive(&hspi2, conf, out, sizeof(out), 1);
  HAL_GPIO_WritePin(GPIOB, pinNumber, GPIO_PIN_SET);

  uint32_t data_out = (((int32_t)out[1]) << 16) | (((int32_t)out[2]) << 8) | (((int32_t)out[3]));
  return (data_out);
}

unsigned long AD7793_ContinuousReadAvg(uint8_t sampleNumber)
{
  AD7793_Mode_Register(AD7793_MODE_CONT, AD7793_CLK_INT, AD7793_RATE_16_7_50);

  uint8_t conf[4] = {AD7793_REG_DATA};
  uint8_t out[4] = {0x00, 0x00, 0x00, 0x00};
  uint32_t samplesAverage = 0x0;
  uint8_t count = 0x0;

  for (count = 0; count < sampleNumber; count++)
  {
    AD7793_WaitRdyGoLow();
    HAL_SPI_TransmitReceive(&hspi2, conf, out, sizeof(out), 1);
    uint32_t data_out = (((int32_t)out[1]) << 16) | (((int32_t)out[2]) << 8) | (((int32_t)out[3]));
    samplesAverage += data_out;
  }
  HAL_GPIO_WritePin(GPIOB, pinNumber, GPIO_PIN_SET);
  samplesAverage = samplesAverage / sampleNumber;
  return (samplesAverage);
}

void send_to_SPI(uint8_t *data, uint16_t size)
{
  HAL_GPIO_WritePin(GPIOB, pinNumber, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, data, size, 1);
  HAL_GPIO_WritePin(GPIOB, pinNumber, GPIO_PIN_SET);
}
