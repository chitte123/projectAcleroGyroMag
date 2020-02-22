#ifndef ACCELERO_H
#define ACCELERO_H


/*############################### ACCELEROMETER ##############################*/
/**
  * @brief  ACCELERO I2C1 Interface pins
  */
#define ACCELERO_DRDY_GPIO_PORT                 GPIOE                       /* GPIOE */
#define ACCELERO_DRDY_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOE_CLK_ENABLE() 
#define ACCELERO_DRDY_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOE_CLK_DISABLE() 
#define ACCELERO_DRDY_PIN                       GPIO_PIN_2                  /* PE.02 */
#define ACCELERO_DRDY_EXTI_IRQn                 TAMP_STAMP_IRQn

#define ACCELERO_INT_GPIO_PORT                  GPIOE                       /* GPIOE */
#define ACCELERO_INT_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOE_CLK_ENABLE()
#define ACCELERO_INT_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOE_CLK_DISABLE()
#define ACCELERO_INT1_PIN                       GPIO_PIN_4                  /* PE.04 */
#define ACCELERO_INT1_EXTI_IRQn                 EXTI4_IRQn 
#define ACCELERO_INT2_PIN                       GPIO_PIN_5                  /* PE.05 */
#define ACCELERO_INT2_EXTI_IRQn                 EXTI9_5_IRQn 


/*############################### I2Cx #######################################*/
#define DISCOVERY_I2Cx                          I2C1
#define DISCOVERY_I2Cx_CLOCK_ENABLE()           __HAL_RCC_I2C1_CLK_ENABLE()
#define DISCOVERY_I2Cx_GPIO_PORT                GPIOB                       /* GPIOB */
#define DISCOVERY_I2Cx_SCL_PIN                  GPIO_PIN_6                  /* PB.06 */
#define DISCOVERY_I2Cx_SDA_PIN                  GPIO_PIN_9                  /* PB.09 */
#define DISCOVERY_I2Cx_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE() 
#define DISCOVERY_I2Cx_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOB_CLK_DISABLE() 
#define DISCOVERY_I2Cx_AF                       GPIO_AF4_I2C1

#define DISCOVERY_I2Cx_FORCE_RESET()            __HAL_RCC_I2C1_FORCE_RESET()
#define DISCOVERY_I2Cx_RELEASE_RESET()          __HAL_RCC_I2C1_RELEASE_RESET()

/* I2C interrupt requests */
#define DISCOVERY_I2Cx_EV_IRQn                  I2C1_EV_IRQn
#define DISCOVERY_I2Cx_ER_IRQn                  I2C1_ER_IRQn

/* I2C speed and timeout max */
#define I2Cx_TIMEOUT_MAX                        0xA000 /*<! The value of the maximal timeout for I2C waiting loops */
#define I2Cx_MAX_COMMUNICATION_FREQ             ((uint32_t) 100000)


    
#endif