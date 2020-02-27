#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "function.h"

#include "accelero.h"
#include "function.h"
#include "ultraSonic.h"
#include "lcdI2c.h"
#include "lcd_i2cModule.h"
#include "uart.h"
#include "gyroL3gd20.h"
#include "stm32f411e_discovery_accelerometer.h"


uint32_t mainDELAY_LOOP_COUNT = 10000;

//void freeRtosTask(void)
//{
//  xTaskCreate( vTask1, /* Pointer to the function that implements the task. */
//              "Task 1",/* Text name for the task. This is to facilitate 
//              debugging only. */
//              500, /* Stack depth - small microcontrollers will use much
//              less stack than this. */
//              NULL, /* This example does not use the task parameter. */
//              1, /* This task will run at priority 1. */
//              NULL ); /* This example does not use the task handle. */
//  
//  xTaskCreate( vTask2, "Task 2", 500, NULL, 1, NULL );
//  xTaskCreate( vTask3, "Task 2", 500, NULL, 1, NULL );
//  xTaskCreate( vTask4, "Task 2", 500, NULL, 1, NULL );
//
//    
//  
//  /* Start the scheduler so the tasks start executing. */
//  vTaskStartScheduler();
//}

void freeRtosTask(void)
{
  xTaskCreate((TaskFunction_t)startAccelero, /* Pointer to the function that implements the task. */
              "Accelero",/* Text name for the task. This is to facilitate 
              debugging only. */
              500, /* Stack depth - small microcontrollers will use much
              less stack than this. */
              NULL, /* This example does not use the task parameter. */
              1, /* This task will run at priority 1. */
              NULL ); /* This example does not use the task handle. */
  
  xTaskCreate((TaskFunction_t) gyroStart, "Gyro", 500, NULL, 1, NULL );
  //xTaskCreate( (TaskFunction_t)ultraSonicStart, "ultraSonic", 500, NULL, 1, NULL );
  //xTaskCreate( vTask4, "Task 2", 500, NULL, 1, NULL );

    
  
  /* Start the scheduler so the tasks start executing. */
  vTaskStartScheduler();
}

void vTask1( void *pvParameters )
{
//  const char *pcTaskName = "Task 1 is running\r\n";
  volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
    /* Print out the name of this task. */
//    vPrintString( pcTaskName );
    HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_SET);
    /* Delay for a period. */
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);

  } 
}

void vTask2( void *pvParameters )
{
//  const char *pcTaskName = "Task 1 is running\r\n";
  volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
    /* Print out the name of this task. */
//    vPrintString( pcTaskName );
    /* Delay for a period. */
    HAL_GPIO_WritePin(GPIOD,LD3_Pin, GPIO_PIN_SET);
    /* Delay for a period. */
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOD,LD3_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);

  } 
}

void vTask3( void *pvParameters )
{
//  const char *pcTaskName = "Task 1 is running\r\n";
  volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
    /* Print out the name of this task. */
//    vPrintString( pcTaskName );
    /* Delay for a period. */
    HAL_GPIO_WritePin(GPIOD,LD5_Pin, GPIO_PIN_SET);
    /* Delay for a period. */
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOD,LD5_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);

  } 
}

void vTask4( void *pvParameters )
{
//  const char *pcTaskName = "Task 1 is running\r\n";
  volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
    /* Print out the name of this task. */
//    vPrintString( pcTaskName );
    /* Delay for a period. */
    HAL_GPIO_WritePin(GPIOD,LD6_Pin, GPIO_PIN_SET);
    /* Delay for a period. */
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOD,LD6_Pin, GPIO_PIN_RESET); 
    HAL_Delay(500);

  } 
}

