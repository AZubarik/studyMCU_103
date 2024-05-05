#ifndef __ReceiveTransmit_H
#define __ReceiveTransmit_H
#ifdef __cplusplus
extern "C" {
#endif

// #include "main.h"
#include <string.h>

#include "mb.h"
#include "mbport.h"
#include "user_mb_app.h"

#define Chanel_1_tempRTD            0
#define Chanel_1_tempChip           2

#define Chanel_2_tempRTD            4
#define Chanel_2_tempChip           6 

float dataReceive (int registr);
void dataTransmit (int registr, float out);

#ifdef __cplusplus
}
#endif
#endif /*__ ReceiveTransmit_H */