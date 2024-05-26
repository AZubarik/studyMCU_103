#include "main.h"
#include "ReceiveTransmit.h"

extern uint16_t usSRegInBuf[];
extern uint16_t usSRegHoldBuf[];

// uint16_t out;
uint16_t *tmpe = 0;

uint16_t RegisterValueOne;
uint16_t RegisterValueTwo;

uint32_t result = 0;
float value;

float dataReceiveMB_float(int registr)
{
  RegisterValueOne = usSRegHoldBuf[registr];
  RegisterValueTwo = usSRegHoldBuf[registr + 1];

  result = (RegisterValueOne) | (RegisterValueTwo << 16);

  memcpy(&value, &result, sizeof(value));

  return value;
}

uint32_t dataReceiveMB_uint(int registr)
{
  RegisterValueOne = usSRegHoldBuf[registr];
  RegisterValueTwo = usSRegHoldBuf[registr + 1];

  result = (RegisterValueOne) | (RegisterValueTwo << 16);

  return result;
}

void dataReceiveMBHold_uint(int registr, uint32_t out)
{
  tmpe = (uint16_t *)&out;
  usSRegHoldBuf[registr] = *tmpe;
  usSRegHoldBuf[registr + 1] = *(tmpe + 1);
}

void dataTransmitMB_float(int registr, float out)
{
  tmpe = (uint16_t *)&out;
  usSRegInBuf[registr] = *tmpe;
  usSRegInBuf[registr + 1] = *(tmpe + 1);
}

void dataTransmitMB_uint(int registr, uint32_t out)
{
  tmpe = (uint16_t *)&out;
  usSRegInBuf[registr] = *tmpe;
  usSRegInBuf[registr + 1] = *(tmpe + 1);
}
