#include "Flash.h"
#include "main.h"
#include "ReceiveTransmit.h"

extern uint16_t usSRegHoldBuf[];

void ErasingMemory()
{
	static FLASH_EraseInitTypeDef EraseInitStruct; // Cтруктура для очистки флеша

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;		// Постраничная очистка, FLASH_TYPEERASE_MASSERASE - очистка всего флеша
	EraseInitStruct.PageAddress = ((uint32_t)0x0801FC00); // Адрес 127-ой страницы
	EraseInitStruct.NbPages = 1;													// Кол-во страниц для стирания
	EraseInitStruct.Banks = FLASH_BANK_1;									// FLASH_BANK_2 - банк №2, FLASH_BANK_BOTH - оба банка

	uint32_t page_error = 0; // Переменная, в которую запишется адрес страницы при неудачном стирании

	HAL_FLASH_Unlock(); // Разблокировать флеш
	HAL_FLASHEx_Erase(&EraseInitStruct, &page_error);

	HAL_FLASH_Lock(); // Заблокировать флеш
}

void writeFlashData(uint32_t address, uint32_t data)
{
	HAL_FLASH_Unlock();
	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (uint32_t)address, data) != HAL_OK)
	{
		HAL_FLASH_GetError();
	}
	HAL_FLASH_Lock();
}

uint32_t readFlashData(uint32_t address)
{
	
	return *(uint32_t *)address;
}
