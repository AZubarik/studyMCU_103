#ifndef     __AD7793_H__
#define     __AD7793_H__

#include "main.h"

/*  AD7793 Registers*/
#define AD7793_REG_COMM		        0   /* Communications Register  (WO, 8-bit) */
#define AD7793_REG_STAT	            0   /* Status Register	        (RO, 8-bit) */
#define AD7793_REG_MODE	            0x08   /* Mode Register	     	(RW, 16-bit */
#define AD7793_REG_CONF	            0x10   /* Configuration Register   (RW, 16-bit)*/
#define AD7793_REG_DATA	            0x58   /* Data Register	     	(RO,   16-/24-bit) */
#define AD7793_REG_ID	            4   /* ID Register	     	    (RO, 8-bit)   */
#define AD7793_REG_IO	            0x28   /* IO Register	     	    (RO, 8-bit) */
#define AD7793_REG_OFFSET           6   /* Offset Register	        (RW, 24-bit */
#define AD7793_REG_FULLSCAL         7   /* Full-Scale Register	    (RW, 24-bit */

/* AD7793_MODE_SEL(x) options */
#define AD7793_MODE_CONT		    0   /* Continuous Conversion Mode */
#define AD7793_MODE_SINGLE		    1   /* Single Conversion Mode */
#define AD7793_MODE_IDLE		    2   /* Idle Mode */
#define AD7793_MODE_PWRDN		    3   /* Power-Down Mode */
#define AD7793_MODE_CAL_INT_ZERO    4   /* Internal Zero-Scale Calibration */
#define AD7793_MODE_CAL_INT_FULL    5   /*   Internal Full-Scale Calibration */
#define AD7793_MODE_CAL_SYS_ZERO    6   /* System   Zero-Scale Calibration */
#define AD7793_MODE_CAL_SYS_FULL    7   /* System Full-Scale   Calibration */

/* AD7793_MODE_CLKSRC(x) options */
#define AD7793_CLK_INT		        0   /* Internal 64 kHz Clk not available at the CLK pin */
#define AD7793_CLK_INT_CO	        1   /* Internal 64 kHz Clk available at the CLK pin */
#define AD7793_CLK_EXT		        2   /* External 64 kHz Clock */
#define AD7793_CLK_EXT_DIV2	        3   /* External Clock   divided by 2 */

/* AD7793_MODE_RATE(x) options */
#define AD7793_RATE_NIL     		0
#define AD7793_RATE_470    		    1
#define AD7793_RATE_242    		    2
#define AD7793_RATE_123    		    3
#define AD7793_RATE_62    		    4
#define AD7793_RATE_50   		    5
#define AD7793_RATE_39			    6
#define AD7793_RATE_33_2		    7
#define AD7793_RATE_19_6		    8   /* 60 Hz only  */
#define AD7793_RATE_16_7_50		    9 	/* 50 Hz only  */
#define AD7793_RATE_16_7_50_60      10	/* 50 and 60 Hz */
#define AD7793_RATE_12_5  		    11 	/* 50 and 60 Hz */
#define AD7793_RATE_10    	        12  /* 50 and 60 Hz */
#define AD7793_RATE_8_33  		    13 	/* 50 and 60 Hz */
#define AD7793_RATE_6_25  	  	    14 	/* 50 and 60 Hz */
#define AD7793_RATE_4_17  		    15  /* 50 and 60 Hz */

/* AD7793_CONF_VBIAS(x) options */
#define AD7793_VBIAS_GEN_DISABL    	0	/* Bias voltage generator disabled */
#define AD7793_VBIAS_AIN1_NEG    	1 	/* Bias voltage generator to AIN1(-) */
#define AD7793_VBIAS_AIN2_NEG    	2 	/* Bias voltage generator to AIN2(-) */

/*  AD7793_CONF_GAIN(x) options Gain and ADC input range (2.5V reference)*/
#define AD7793_GAIN_1               0	/* 1X (In-amp nor used)	2.5 */
#define AD7793_GAIN_2               1	/* 2X (In-amp nor used)	1.25 */
#define AD7793_GAIN_4               2	/* 4X 					625mV */
#define AD7793_GAIN_8               3	/* 8X 					312.5 mV*/
#define AD7793_GAIN_16              4	/* 16X					156.2 mV*/
#define AD7793_GAIN_32              5	/* 32X 					78.125 mV */
#define AD7793_GAIN_64              6	/* 64X					39.06 mV  */
#define AD7793_GAIN_128             7	/* 128X					19.53 mV */

/*  AD7793_CONF_REFSEL(x) options */

#define AD7793_REFSEL_EXT           0	/* External reference applied between   REFIN(+) and REFIN(–). */
#define AD7793_REFSEL_INT           1	/* Internal reference selected. */

/*  AD7793_CONF_CHAN(x) options */
#define AD7793_CH_AIN1P_AIN1M       0   /* Select channel AIN1(+) - AIN1(-) */
#define AD7793_CH_AIN2P_AIN2M       1   /* Select channel AIN2(+) - AIN2(-) */
#define AD7793_CH_AIN3P_AIN3M       2   /* Select channel AIN3(+) - AIN3(-) */
#define AD7793_CH_AIN1M_AIN1M       3   /* Select channel AIN1(-) - AIN1(-) */
#define AD7793_CH_TEMP              6   /* Temp Sensor, gain 1, Internal reference */
#define AD7793_CH_AVDD_MONITOR	    7   /* AVDD voltage Monitor, gain 1/6, Internal 1.17V reference */

/*  AD7793_IEXCDIR(x)   options*/
#define AD7793_DIR_IEXC1_IOUT1_IEXC2_IOUT2  0   /* IEXC1 connect to IOUT1, IEXC2 connect to IOUT2 */
#define AD7793_DIR_IEXC1_IOUT2_IEXC2_IOUT1	1   /* IEXC1 connect to IOUT2, IEXC2 connect to IOUT1 */
#define AD7793_DIR_IEXC1_IEXC2_IOUT1		2   /* Both current sources IEXC1,2 connect to IOUT1  */
#define AD7793_DIR_IEXC1_IEXC2_IOUT2		3   /* Both current sources IEXC1,2 connect to IOUT2 */

/*  AD7793_IEXCEN(x)   options*/
#define AD7793_EN_IXCEN_DISABLE				0  /* Disable excitation current*/
#define AD7793_EN_IXCEN_10uA				1  /* Excitation Current 10uA */
#define AD7793_EN_IXCEN_210uA				2  /* Excitation Current 210uA */
#define AD7793_EN_IXCEN_1mA					3  /* Excitation Current 1mA */


/*  Initialize AD7793 and check if the device is present.   */
void AD7793_Init(void);

/*  Sends 32 consecutive 1's on SPI in order to reset the part. */
void AD7793_Reset(void);

/* Waits for RDY pin to go low. */
void AD7793_WaitRdyGoLow(void);

/*  MODE REGISTER */
void AD7793_Mode_Register(unsigned char mode, unsigned long clksrc, unsigned long rate);

/*  CONFIGURATION REGISTER */
void AD7793_Configuration_Register(unsigned char vbias, unsigned char gain, unsigned char refsel, unsigned char channel);

/*  IO REGISTER 8-bit */
void AD7793_IO_Register(unsigned char direction, unsigned char current);

/*  Returns the result of a single conversion. */
unsigned long AD7793_SingleConversion(void);

/*  Returns the average of several conversion results. */
unsigned long AD7793_ContinuousReadAvg(unsigned char sampleNumber);

void send_to_SPI(uint8_t *data, uint16_t size);

#endif