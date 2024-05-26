#include "Flash_io.h"
#include "Flash.h"
#include "ReceiveTransmit.h"

extern uint16_t usSRegHoldBuf[];

static memoryChip memoryDevice;

void storeParametersToFlash()
{
  if (usSRegHoldBuf[9] == TRUE)
  { /* Чтение дыннх из Flash */
    if (usSRegHoldBuf[10] == TRUE)
    {
      for (int i = 0; i < 6; i += 2)
      {
        dataReceiveMBHold_uint(12 + i, readFlashData(0x0801FC00 + (i * 2)));
      }
      usSRegHoldBuf[10] = FALSE;
    }

    memoryDevice.deviceIdMB = dataReceiveMB_uint(12);
    switch (dataReceiveMB_uint(14))
    {
      case 1:
          memoryDevice.BaudRate = 9600;
          break;
      case 2:
          memoryDevice.BaudRate = 19200;
          break;
      case 3:
          memoryDevice.BaudRate = 38400;
          break;
      case 4:
          memoryDevice.BaudRate = 115200;
          break;
    }

    /* Запись данных в Flash */
    if (usSRegHoldBuf[11] == TRUE)
      {
        ErasingMemory();
        writeFlashData(0x0801FC00, memoryDevice.deviceIdMB);
        writeFlashData(0x0801FC04, memoryDevice.BaudRate);
        usSRegHoldBuf[11] = FALSE;
      }
    }
}

