#include "AD7793.h"
#include "spi.h"
#include "gpio.h"
#include "stm32f1xx_it.h"

void AD7793_Init(void)
{
	unsigned char init_command[3] = {0x50, 0x00, 0x00};
    send_to_SPI(init_command, sizeof(init_command));
}

void AD7793_Reset(void)
{
	unsigned char dataToSend[5] = {0x03, 0xff, 0xff, 0xff, 0xff};
    send_to_SPI(dataToSend, sizeof(dataToSend));
}

void AD7793_WaitRdyGoLow(void)
{
     HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
for(int i = 0; i < 600000; i++){
}
}

void AD7793_Mode_Register(unsigned char mode, unsigned long clksrc, unsigned long rate)
{
    unsigned char dataToSend[3] = {AD7793_REG_MODE, 0x00, 0x00};
                  dataToSend[1] = mode << 5;
                  dataToSend[2] = (clksrc << 6) + rate;
    CS_Pin_OFF; 
    HAL_SPI_Transmit(&hspi2, dataToSend, 3, 1);
    
}

void AD7793_Configuration_Register(unsigned char vbias, unsigned char gain, unsigned char refsel, unsigned char channel)
{
    uint8_t vbias_gain = (vbias << 6) + gain;
    uint8_t refsel_chanel = 0x10 | ((refsel << 7) + channel);
	uint8_t conf_command[3] = {AD7793_REG_CONF, vbias_gain, refsel_chanel};
    send_to_SPI(conf_command, sizeof(conf_command)); 
}

void AD7793_IO_Register(unsigned char direction, unsigned char current)
{
    unsigned char dataToSend[2] = {AD7793_REG_IO, current};
                  dataToSend[1] = (direction << 2) + current;          
    send_to_SPI(dataToSend, 2);
}

unsigned long AD7793_SingleConversion(void)
{
    AD7793_Mode_Register(AD7793_MODE_SINGLE, AD7793_CLK_INT, AD7793_RATE_19_6);
    AD7793_WaitRdyGoLow();
    uint8_t conf[4] = {AD7793_REG_DATA};
    uint8_t out[4] = {0x00, 0x00, 0x00, 0x00};
    
    CS_Pin_OFF;
        HAL_SPI_TransmitReceive(&hspi2, conf, out, sizeof(out) , 1);
    CS_Pin_ON;

    uint32_t data_out = (((int32_t)out[1])<<16) | (((int32_t)out[2])<<8) | (((int32_t)out[3]));
    return(data_out);
}

unsigned long AD7793_ContinuousReadAvg(unsigned char sampleNumber)
{
  
    uint8_t conf[4] = {AD7793_REG_DATA};
    uint8_t out[4] = {0x00, 0x00, 0x00, 0x00};
    unsigned long   samplesAverage = 0x0;
    unsigned char count = 0x0;
    
    CS_Pin_OFF;
    for(count = 0;count < sampleNumber;count ++)
    {
        HAL_SPI_TransmitReceive(&hspi2, conf, out, sizeof(out) , 1);
        uint32_t data_out = (((int32_t)out[1])<<16) | (((int32_t)out[2])<<8) | (((int32_t)out[3]));
        samplesAverage += data_out;
    }
    CS_Pin_ON;
    samplesAverage = samplesAverage / sampleNumber;
    return(samplesAverage);
}

void send_to_SPI(uint8_t *data, uint16_t size) 
{
    CS_Pin_OFF; 
	    HAL_SPI_Transmit(&hspi2, data, size, 1);
    CS_Pin_ON;    
}

