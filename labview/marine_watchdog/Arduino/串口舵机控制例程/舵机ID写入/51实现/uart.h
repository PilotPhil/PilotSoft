/******************************************************
 * FileName:      uart.h
 * Company:       ????
 * Date:           2016/07/08  20:02
 * Description:    Lobot???????????,??stc89c52rc??,
 *                 ???????????????????????
 *****************************************************/

#ifndef UART_H_
#define UART_H_

#include "typedef.h"
#include "STC12C5A60S2.H"

extern void uartInit(void);
extern void uartWriteByte(uint8_t dat);
extern void uartWriteBuf(uint8_t *buf, uint8_t len);
extern bool isRxCompleted(void);

#endif
