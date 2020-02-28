#include "main.h"
#include "uart.h"
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

UART_HandleTypeDef huart2;

extern SemaphoreHandle_t xMutex;

void uartSend(uint8_t *string)
{
//  taskENTER_CRITICAL();
//  vTaskSuspendScheduler();
//  xSemaphoreTake( xMutex, portMAX_DELAY );
  uint8_t size = strlen(string);
  //sprintf("")
  HAL_UART_Transmit(&huart2,string,size,1000);
//  taskEXIT_CRITICAL();
//  xTaskResumeScheduler();
//  xSemaphoreGive(xMutex);
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
