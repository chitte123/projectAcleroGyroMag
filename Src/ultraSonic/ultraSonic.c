#include "main.h"
#include "ultraSonic.h"
#include <stdio.h>
#include <string.h>

TIM_HandleTypeDef htim5;
extern UART_HandleTypeDef huart2;

uint32_t time = 0;
uint32_t sensorTime = 0;
uint32_t distance = 0;


void initUltraSonic(void)
{
  uint8_t msg[30] = {0};
  initTim5();

    while(1)
    {
      sensorTime = hcsr04_read();
      //distance  = sensorTime * .034/2;
      distance  = sensorTime / 58;
      sprintf(msg,"distance = %d cm\r\n",distance);
      HAL_UART_Transmit(&huart2,msg,30,1000);
      memset(msg,0,30);
      HAL_Delay(200);
    }
    
}

uint32_t hcsr04_read(void)
{
  time = 0;
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  delayUs(2);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
  delayUs(10);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  
  while(!(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)));
  while((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)))
  {
    time++;
    delayUs(1);
  }
   return time;  
}

void initTim5(void)
{
  __HAL_RCC_TIM5_CLK_ENABLE();
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 47;
  htim5.Init.Period = 0xFFFFFFFF - 1;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }  
}

void delayUs(uint32_t us)
{
    __HAL_TIM_SET_COUNTER(&htim5, 0);
      HAL_TIM_Base_Start(&htim5);
    while ((__HAL_TIM_GET_COUNTER(&htim5))<us);
}
