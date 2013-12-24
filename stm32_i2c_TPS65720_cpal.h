/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_I2C_TPS65720_CPAL_H
#define __STM32_I2C_TPS65720_CPAL_H

#ifdef __cplusplus
 extern "C" {
#endif
   
   
/* Includes ------------------------------------------------------------------*/
#include "cpal_i2c.h"
   
/* Exported types ------------------------------------------------------------*/
typedef enum
{
  TPS6572_OK = 0,
  TPS6572_FAIL
}TPS6572_Status_TypDef;

/* Exported constants --------------------------------------------------------*/
    
/* CPAL Structure configuration : Select I2C device (uncomment relative define) */

#define TPS6572_DevStructure                I2C1_DevStructure   
//#define TPS6572_DevStructure                I2C2_DevStructure  
//#define TPS6572_DevStructure                I2C3_DevStructure 

   
/* Select clock Speed */
/* To use the I2C at 400 KHz (in fast mode), the PCLK1 frequency (I2C peripheral
   input clock) must be a multiple of 10 MHz */

#define I2C_SPEED                        20000

/* Select interrupt programming model : By default DMA programming model is selected.
 To select interrupt programming model uncomment this define */
//#define TPS6572_IT

/* Maximum Timeout values for waiting until device is ready for communication.*/
   
#define TPS6572_TIMEOUT        ((uint32_t)0x3FFFF)

/**
  * @brief  Internal register Memory
  */
  
#define TPS6572_ADDR           0x48   /*!< TPS6572 address */

#define TPS6572_REG_TEMP       0x00  /*!< Temperature Register of TPS6572 */
#define TPS6572_REG_CONF       0x01  /*!< Configuration Register of TPS6572 */
#define TPS6572_REG_THYS       0x02  /*!< Temperature Register of TPS6572 */
#define TPS6572_REG_TOS        0x03  /*!< Over-temp Shutdown threshold Register of TPS6572 */
   

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

void TPS6572_DeInit(void);
void TPS6572_Config(void);
ErrorStatus TPS6572_GetStatus(void);
uint16_t TPS6572_ReadTemp(void);
uint16_t TPS6572_ReadReg(uint8_t RegName);
uint8_t TPS6572_WriteReg(uint8_t RegName, uint16_t RegValue);
uint8_t TPS6572_ReadConfReg(void);
uint8_t TPS6572_WriteConfReg(uint8_t RegValue);
uint8_t TPS6572_ShutDown(FunctionalState NewState);


 
#ifdef __cplusplus
}
#endif

#endif /* __STM32_I2C_TPS65720_CPAL_H */
