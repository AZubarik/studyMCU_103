#include "initADC.h"
#include "AD7793.h"
#include "ReceiveTransmit.h"
#include "math.h"

extern uint16_t usSRegHoldBuf[];

uint16_t pinNumber;
BOOL Flag;

float GAIN = 1;            /* Gain of the AD7793 unternal instrumentation amplifier */
float V;                   /* The voltage read on the analog input channel 2 (should be between -0.57 +0.57 when gain is set to 1) */
float RRTD;                /* The measured resistance of the RTD */
float tempChip;            /* The temperature read on the analog input channel 1 */
const float RREF = 2000.0; /* The reference resistor: here, 2.0 Kohm, 0.1%, 10ppm/C */
const float Vref = 1.17;   /* The external reference voltage applied between pins REFIN(+) and REFIN(-)and resulting from the excitation current flowing through the reference resistor  */
const float R0 = 1000.0;   /* RTD resistance at 0C */
const float A = 3.9083E-3; /* Coefficient for t in the Callender-Van Dusen equation for temperature > 0C */
const float B = -5.775E-7; /* Coefficient for t squared in the Callender-Van Dusen equation for temperature > 0C */

void ADC_chanel(uint16_t CS)
{
  pinNumber = CS;
  if (!usSRegHoldBuf[0])
  {
    AD7793_Init();
    tempCPU_AD();
    dataTransmitMB_float(Chanel_1_tempChip, tempChip);
    usSRegHoldBuf[0] = TRUE;
    Flag = 0;
  }
  if (usSRegHoldBuf[1])
  {
    AD7793_Calibrate(AD7793_MODE_CAL_INT_ZERO, AD7793_CH_AIN1P_AIN1M); /* Performs Internal Zero calibration to the specified channel. */
    AD7793_Calibrate(AD7793_MODE_CAL_INT_FULL, AD7793_CH_AIN1P_AIN1M); /* Performs Internal Full Calibration to the specified channel. */
    usSRegHoldBuf[1] = FALSE;
  }

  if (!usSRegHoldBuf[2])
  {
    AD7793_Reset();
    AD7793_Configuration_Register(AD7793_VBIAS_GEN_DISABL, AD7793_GAIN_1, AD7793_REFSEL_EXT, AD7793_CH_AIN1P_AIN1M);
    AD7793_IO_Register(AD7793_DIR_IEXC1_IOUT1_IEXC2_IOUT2, AD7793_EN_IXCEN_210uA);

    float tempRTD = temp(AD7793_ContinuousReadAvg(10));

    if ((tempRTD > 0) && (tempRTD < 100))
    {
      dataTransmitMB_float(Chanel_1_tempRTD, tempRTD);
    }
    else
    {
      dataTransmitMB_float(Chanel_1_tempRTD, 404);
    }
  }
}

void ADC_chanel_(uint16_t CS)
{
  pinNumber = CS;
  if (!usSRegHoldBuf[3])
  {
    AD7793_Init();
    tempCPU_AD();
    dataTransmitMB_float(Chanel_2_tempChip, tempChip);
    usSRegHoldBuf[3] = TRUE;
  }
  if (usSRegHoldBuf[4])
  {
    AD7793_Calibrate(AD7793_MODE_CAL_INT_ZERO, AD7793_CH_AIN1P_AIN1M); /* Performs Internal Zero calibration to the specified channel. */
    AD7793_Calibrate(AD7793_MODE_CAL_INT_FULL, AD7793_CH_AIN1P_AIN1M); /* Performs Internal Full Calibration to the specified channel. */
    usSRegHoldBuf[4] = FALSE;
  }

  if (!usSRegHoldBuf[5])
  {
    AD7793_Reset();
    AD7793_Configuration_Register(AD7793_VBIAS_GEN_DISABL, AD7793_GAIN_1, AD7793_REFSEL_EXT, AD7793_CH_AIN1P_AIN1M);
    AD7793_IO_Register(AD7793_DIR_IEXC1_IOUT1_IEXC2_IOUT2, AD7793_EN_IXCEN_210uA);
    float tempRTD = temp(AD7793_ContinuousReadAvg(10));
    dataTransmitMB_float(Chanel_2_tempRTD, tempRTD);

    // if ((tempRTD > 0) && (tempRTD < 100))
    // {
    //   dataTransmitMB_float(Chanel_2_tempRTD, tempRTD);
    // }
    // else
    // {
    //   dataTransmitMB_float(Chanel_2_tempRTD, 404);
    // }
  }
}


void tempCPU_AD()
{
  AD7793_Reset();
  AD7793_Configuration_Register(AD7793_VBIAS_GEN_DISABL, AD7793_GAIN_1, AD7793_REFSEL_EXT, AD7793_CH_TEMP);
  tempChip = tempChip(AD7793_ContinuousReadAvg(2));
}

void Calibrate()
{
  AD7793_Calibrate(AD7793_MODE_CAL_INT_ZERO, AD7793_CH_AIN1P_AIN1M); /* Performs Internal Zero calibration to the specified channel. */
  AD7793_Calibrate(AD7793_MODE_CAL_INT_FULL, AD7793_CH_AIN1P_AIN1M); /* Performs Internal Full Calibration to the specified channel. */
}
