#ifndef     __FLASH_H__
#define     __FLASH_H__

#include "main.h"

void ErasingMemory(void);

/* Flash_write */
void writeFlashData (uint32_t address, uint32_t data);

/* Flash_read */
uint32_t readFlashData (uint32_t address);

#endif
