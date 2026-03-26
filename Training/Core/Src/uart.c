/*
 * uart.c
 *
 *  Created on: Mar 26, 2026
 *      Author: Kjwon
 */

#include "main.h"
#include "uart.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if(huart->Instance == USART2) {
        // 받은 데이터를 다시 보냄 (테스트용)
//        HAL_UART_Transmit(&huart2, rxBuffer, 1, 10);

        // [중요] 다음 데이터를 받기 위해 다시 인터럽트 활성화
//        HAL_UART_Receive_IT(&huart2, rxBuffer, 1);
    }
}

void ReceiveUart(void)
{

}
