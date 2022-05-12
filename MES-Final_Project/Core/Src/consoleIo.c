// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;

// Code from https://github.dev/zivkovic-msz/Making_Embedded_Systems_Course/tree/main/Assignments/Week_5
char readBuf[1];
__IO ITStatus UartReady = SET;

static int getch_noblock() {
	int retVal = EOF;

		if (UartReady == SET) {
			UartReady = RESET;
			HAL_UART_Receive_IT(&huart1, (uint8_t*)readBuf, 1);
			HAL_UART_Transmit_IT(&huart1, (uint8_t*)readBuf, 1); // echo
			retVal = *readBuf;
		}

	return retVal;
}
//

eConsoleError ConsoleIoInit(void)
{
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
	uint32_t i = 0;
	char ch;
	
	ch = getch_noblock();
	while ( ( EOF != ch ) && ( i < bufferLength ) )
	{
		buffer[i] = (uint8_t) ch;
		i++;
		ch = getch_noblock();
	}
	*readLength = i;
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}
