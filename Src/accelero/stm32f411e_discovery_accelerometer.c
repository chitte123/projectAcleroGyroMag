
/* Includes ------------------------------------------------------------------*/
#include "stm32f411e_discovery_accelerometer.h"
#include "main.h"
#include <stdio.h>
#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "projdefs.h"
#include "semphr.h"

extern TaskHandle_t *tapHandle;
static ACCELERO_DrvTypeDef *AccelerometerDrv;
extern uint8_t msg[MAX_STRING_SIZE];
int16_t pDataXYZ[3] = {0};
extern SemaphoreHandle_t xMutex;

void acceleroInit(void)
{
  BSP_ACCELERO_Init();
  BSP_ACCELERO_Click_ITConfig();
}

void startAccelero(void)
{
  while(1)
  {
      BSP_ACCELERO_GetXYZ(pDataXYZ);
//      printf("X = %d\r\n",pDataXYZ[0]);
//      printf("Y = %d\r\n",pDataXYZ[1]);
//      printf("Z = %d\r\n",pDataXYZ[2]);
//      HAL_Delay(50);
    vTaskDelay(pdMS_TO_TICKS( 100 ));
  }
}

void printAccelero(void)
{
  uint8_t label[] = "-------ACCELERO-------\r\n";
  
  while(1)
  {
  xSemaphoreTake( xMutex, portMAX_DELAY );
uartSend(label); 
    sprintf(msg,"AX = %d\r\nAY = %d\r\nAZ = %d\r\n",pDataXYZ[0],pDataXYZ[1],pDataXYZ[2]);
    uartSend(msg);
  xSemaphoreGive(xMutex);
//    vTaskDelay(pdMS_TO_TICKS( 600 ));
  }
}

void tapDetected(void)
{
  uint8_t label[] = "Tap detected\r\n";
  
  while(1)
  {
    uint32_t timeout = HAL_GetTick();
    while((HAL_GetTick() - timeout) < 500)
    {
      xSemaphoreTake( xMutex, portMAX_DELAY );
      uartSend(label);
      xSemaphoreGive(xMutex);
    }
    vTaskSuspend(tapHandle);
  }
}

/**
  * @brief  Set Accelerometer Initialization.
  * @retval ACCELERO_OK if no problem during initialization
  */
uint8_t BSP_ACCELERO_Init(void)
{
  uint8_t ret = ACCELERO_ERROR;
  uint16_t ctrl = 0x0000;
  ACCELERO_InitTypeDef         LSM303DLHC_InitStructure;
  ACCELERO_FilterConfigTypeDef LSM303DLHC_FilterStructure = {0,0,0,0};
  
  if(Lsm303dlhcDrv.ReadID() == I_AM_LMS303DLHC)
  {
    /* Initialize the Accelerometer driver structure */
    AccelerometerDrv = &Lsm303dlhcDrv;

    /* MEMS configuration ----------------------------------------------------*/
    /* Fill the Accelerometer structure */
    LSM303DLHC_InitStructure.Power_Mode = LSM303DLHC_NORMAL_MODE;
    LSM303DLHC_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
    LSM303DLHC_InitStructure.Axes_Enable = LSM303DLHC_AXES_ENABLE;
    LSM303DLHC_InitStructure.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
    LSM303DLHC_InitStructure.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
    LSM303DLHC_InitStructure.Endianness = LSM303DLHC_BLE_LSB;
    LSM303DLHC_InitStructure.High_Resolution = LSM303DLHC_HR_ENABLE;
    
    /* Configure MEMS: data rate, power mode, full scale and axes */
    ctrl |= (LSM303DLHC_InitStructure.Power_Mode | LSM303DLHC_InitStructure.AccOutput_DataRate | \
                       LSM303DLHC_InitStructure.Axes_Enable);
    
    ctrl |= ((LSM303DLHC_InitStructure.BlockData_Update | LSM303DLHC_InitStructure.Endianness | \
                      LSM303DLHC_InitStructure.AccFull_Scale | LSM303DLHC_InitStructure.High_Resolution) << 8);
    
    /* Configure the Accelerometer main parameters */
    AccelerometerDrv->Init(ctrl);
    
    /* Fill the Accelerometer LPF structure */
    LSM303DLHC_FilterStructure.HighPassFilter_Mode_Selection =LSM303DLHC_HPM_NORMAL_MODE;
    LSM303DLHC_FilterStructure.HighPassFilter_CutOff_Frequency = LSM303DLHC_HPFCF_16;
    LSM303DLHC_FilterStructure.HighPassFilter_AOI1 = LSM303DLHC_HPF_AOI1_DISABLE;
    LSM303DLHC_FilterStructure.HighPassFilter_AOI2 = LSM303DLHC_HPF_AOI2_DISABLE;
    
    /* Configure MEMS: mode, cutoff frquency, Filter status, Click, AOI1 and AOI2 */
    ctrl = (uint8_t) (LSM303DLHC_FilterStructure.HighPassFilter_Mode_Selection |\
                      LSM303DLHC_FilterStructure.HighPassFilter_CutOff_Frequency|\
                      LSM303DLHC_FilterStructure.HighPassFilter_AOI1|\
                      LSM303DLHC_FilterStructure.HighPassFilter_AOI2);

    /* Configure the Accelerometer LPF main parameters */
    AccelerometerDrv->FilterConfig(ctrl);

    ret = ACCELERO_OK;
  }
  else
  {
    ret = ACCELERO_ERROR;
  }

  return ret;
}

/**
  * @brief  Reboot memory content of Accelerometer.
  */
void BSP_ACCELERO_Reset(void)
{
  if(AccelerometerDrv->Reset != NULL)
  {
    AccelerometerDrv->Reset();
  }  
}

/**
  * @brief  Configure Accelerometer click IT. 
  */
void BSP_ACCELERO_Click_ITConfig(void)
{
  if(AccelerometerDrv->ConfigIT!= NULL)
  {
    AccelerometerDrv->ConfigIT();
  }
}

/**
  * @brief  Get XYZ axes acceleration.
  * @param  pDataXYZ: Pointer t`o 3 angular acceleration axes.  
  *                   pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis
  */
void BSP_ACCELERO_GetXYZ(int16_t *pDataXYZ)
{
  int16_t SwitchXY = 0;
  
  if(AccelerometerDrv->GetXYZ!= NULL)
  {
    AccelerometerDrv->GetXYZ(pDataXYZ);
    
    /* Switch X and Y Axes in case of LSM303DLHC MEMS */
    if(AccelerometerDrv == &Lsm303dlhcDrv)
    { 
      SwitchXY  = pDataXYZ[0];
      pDataXYZ[0] = pDataXYZ[1];
      
      /* Invert Y Axis to be conpliant with LIS3DSH */
      pDataXYZ[1] = -SwitchXY;
    } 
  }
}
