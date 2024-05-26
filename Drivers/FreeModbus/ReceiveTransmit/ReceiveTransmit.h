#ifndef __ReceiveTransmit_H
#define __ReceiveTransmit_H
#ifdef __cplusplus
extern "C"
{
#endif

// #include "main.h"
#include <string.h>

#include "mb.h"
#include "mbport.h"
#include "user_mb_app.h"

#define Chanel_1_tempRTD        0
#define Chanel_1_tempChip       2

#define Chanel_2_tempRTD        4
#define Chanel_2_tempChip       6

/* Parameters for temperature and vref STM32 */
#define vrefCPU_STM32           10
#define tempCPU_STM32           12


  float dataReceiveMB_float(int registr);

  uint32_t dataReceiveMB_uint(int registr);

  void dataTransmitMB_float(int registr, float out);

  void dataTransmitMB_uint(int registr, uint32_t out);

  void dataReceiveMBHold_uint(int registr, uint32_t out);

#ifdef __cplusplus
}
#endif
#endif /*__ ReceiveTransmit_H */
