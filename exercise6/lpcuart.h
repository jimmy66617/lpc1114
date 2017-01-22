#ifndef   __LPCUART_H__
#define   __LPCUART_H__
extern void UART_init(uint32_t baudrate);
extern uint8_t UART_recive(void);
extern void UART_send_byte(uint16_t byte);
extern void UART_send(uint8_t *BufferPtr, uint32_t Length);
#endif