#include "main.h"
#include "lcdI2c.h"
#include "lcd_i2cModule.h"

I2C_HandleTypeDef hi2c3;

static void MX_I2C3_Init(void);

void lcdInit(void)
{
  MX_I2C3_Init();
  if(LCD_i2cDeviceCheck() == HAL_ERROR)
  {
    Error_Handler();
  }
  LCD_Init();
  LCD_BackLight(LCD_BL_ON);
  LCD_SetCursor(1,1);
	//Example 1 
//	int current = 10; //Example integer value
//	float volt = 227.89; //Example float value
//	LCD_SetCursor(1,1);
//  LCD_Print("volt:%.2f V", volt); //Example of printing float value 
//  LCD_SetCursor(2,1);	
//	LCD_Print("current:%.0f A", (float)current); //Example of  printing integer value
//  HAL_Delay(1000);
//  LCD_Clear();
//	HAL_Delay(20);
	
	//----------------------------------------------/
	//Example 2 	
//	LCD_Send_String("string example str no slide", STR_NOSLIDE); //Example of sending string value.
//	HAL_Delay(800);
//  LCD_Clear();
//	HAL_Delay(20);
	
	//----------------------------------------------/
	//Example 3
//	LCD_SetCursor(1,1);
//	LCD_Send_String("1.line slide example", STR_SLIDE); //Example of sliding string value.
//	LCD_SetCursor(2,1);
//	LCD_Send_String("2.line slide example", STR_SLIDE); //Example of sliding string value.
//	HAL_Delay(800);
//  LCD_Clear();
//	HAL_Delay(20);
  while(1)
  {    
    LCD_Send_String("Kunti",STR_SLIDE);
    HAL_Delay(800);
    //LCD_SetCursor(2,1);
    //LCD_Send_String("Putti",STR_SLIDE);
    LCD_Clear();
    HAL_Delay(20);
  }
}



/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */
}




