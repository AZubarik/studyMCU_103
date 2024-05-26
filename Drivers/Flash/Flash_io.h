#ifndef     __FLASH_IO_H__
#define     __FLASH_IO_H__

#include "main.h"

#define ADDR_FLASH_PAGE_120   ((uint32_t)0x0801E000)     /* Base @ of Page 120, 1 Kbytes */
#define ADDR_FLASH_PAGE_121   ((uint32_t)0x0801E400)     /* Base @ of Page 121, 1 Kbytes */
#define ADDR_FLASH_PAGE_122   ((uint32_t)0x0801E800)     /* Base @ of Page 122, 1 Kbytes */
#define ADDR_FLASH_PAGE_123   ((uint32_t)0x0801EC00)     /* Base @ of Page 123, 1 Kbytes */
#define ADDR_FLASH_PAGE_124   ((uint32_t)0x0801F000)     /* Base @ of Page 124, 1 Kbytes */
#define ADDR_FLASH_PAGE_125   ((uint32_t)0x0801F400)     /* Base @ of Page 125, 1 Kbytes */
#define ADDR_FLASH_PAGE_126   ((uint32_t)0x0801F800)     /* Base @ of Page 126, 1 Kbytes */
#define ADDR_FLASH_PAGE_127   ((uint32_t)0x0801FC00)     /* Base @ of Page 127, 1 Kbytes */

typedef struct
{
	char deviceId;           // 1 byte

	uint8_t  deviceIdMB;        // 1 byte
	uint32_t BaudRate;          // 1 byte
} memoryChip;

void storeParametersToFlash(void);

#endif
