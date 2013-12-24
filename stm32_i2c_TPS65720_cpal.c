/**
  * @brief   This file provides a set of functions needed to manage the I2C TPS6572 
  *          temperature sensor mounted on STM32xx-EVAL board (refer to stm32_eval.h
  *          to know about the boards supporting this sensor). 
  *          It implements a high level communication layer for read and write 
  *          from/to this sensor. The needed STM32 hardware resources (I2C and 
  *          GPIO) are defined in stm32xx_eval.h file, and the initialization is 
  *          performed in TPS6572_LowLevel_Init() function declared in stm32xx_eval.c 
  *          file.
  *            
  *          @note This file is a modified version of stm32_eval_i2c_tsensor.c driver;
  *                I2C CPAL library drivers are used instead of the Standard Peripherals
  *                I2C driver.
  *                 
  *          You can easily tailor this driver to any other development board, 
  *          by just adapting the defines for hardware resources and 
  *          TPS6572_LowLevel_Init() function.
  *
  *     +-----------------------------------------------------------------+
  *     |                        Pin assignment                           |                 
  *     +---------------------------------------+-----------+-------------+
  *     |  STM32 I2C Pins                       |   TPS6572  |   Pin       |
  *     +---------------------------------------+-----------+-------------+
  *     | TPS6572_I2C_SDA_PIN/ SDA                 |   SDA     |    1        |
  *     | TPS6572_I2C_SCL_PIN/ SCL                 |   SCL     |    2        |
  *     |                                       |   OS/INT  |    3        |
  *     | .                                     |   GND     |    4  (0V)  |
  *     | .                                     |   GND     |    5  (0V)  |
  *     | .                                     |   GND     |    6  (0V)  |
  *     | .                                     |   GND     |    7  (0V)  |
  *     | .                                     |   VDD     |    8  (3.3V)|
  *     +---------------------------------------+-----------+-------------+
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_i2c_TPS65720_cpal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define TPS6572_SD_SET      0x01 /*!< Set SD bit in the configuration register */
#define TPS6572_SD_RESET    0xFE /*!< Reset SD bit in the configuration register */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
  
CPAL_TransferTypeDef  TPS6572_RXTransfer = { 
                        /* Initialize TX Transfer structure */
                        pNULL,
                        0,
                        0,
                        0};

CPAL_TransferTypeDef  TPS6572_TXTransfer = {
                        /* Initialize RX Transfer structure */
                        pNULL,
                        0,
                        0,
                        0};

uint8_t TPS6572_Buffer[2] = {0x00,0x00}; 

extern CPAL_InitTypeDef TPS6572_DevStructure;


__IO uint32_t  TPS6572_Timeout = TPS6572_TIMEOUT; 

/* Private function prototypes -----------------------------------------------*/
static void TPS6572_StructInit(void);
static void TPS6572_Init(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the TPS6572_I2C.
  * @param  None
  * @retval None
  */
void TPS6572_Config(void)
{
  TPS6572_StructInit ();
  TPS6572_Init();
}

/**
  * @brief  Deinitialize the TPS6572_I2C.
  * @param  None
  * @retval None
  */
void TPS6572_DeInit(void)
{
    /* Initialize CPAL peripheral */
  CPAL_I2C_DeInit(&TPS6572_DevStructure);
}

/**
  * @brief  Initializes the TPS6572_I2C.
  * @param  None
  * @retval None
  */
static void TPS6572_Init(void)
{
  /* Initialize CPAL peripheral */
  CPAL_I2C_Init(&TPS6572_DevStructure);
}

/**
  * @brief  Initializes the TPS6572_I2C.
  * @param  None
  * @retval None
  */
static void TPS6572_StructInit(void)
{
  /* Set CPAL structure parameters to their default values */  
  CPAL_I2C_StructInit(&TPS6572_DevStructure);
    
  /* Set I2C clock speed */
  TPS6572_DevStructure.pCPAL_I2C_Struct->I2C_ClockSpeed = I2C_SPEED;
  			 
#ifdef TPS6572_IT
  /* Select Interrupt programming model and disable all options */
  TPS6572_DevStructure.CPAL_ProgModel = CPAL_PROGMODEL_INTERRUPT;
  TPS6572_DevStructure.wCPAL_Options  = 0;
#else
  /* Select DMA programming model and activate TX_DMA_TC and RX_DMA_TC interrupts */
  TPS6572_DevStructure.CPAL_ProgModel = CPAL_PROGMODEL_DMA;
  TPS6572_DevStructure.wCPAL_Options  = 0;
#endif /* TPS6572_IT */  

  /* point to CPAL_TransferTypeDef structure */
  TPS6572_DevStructure.pCPAL_TransferTx = &TPS6572_TXTransfer;
  TPS6572_DevStructure.pCPAL_TransferRx = &TPS6572_RXTransfer;
}

static uint32_t TPS6572_Status (void)
{
  TPS6572_DevStructure.pCPAL_TransferTx = &TPS6572_TXTransfer;     
  TPS6572_DevStructure.pCPAL_TransferTx->wAddr1 = (uint32_t)TPS6572_ADDR;
  
  return CPAL_I2C_IsDeviceReady(&TPS6572_DevStructure);
}

/**
  * @brief  Checks the TPS6572 status.
  * @param  None
  * @retval ErrorStatus: TPS6572 Status (ERROR or SUCCESS).
  */
ErrorStatus TPS6572_GetStatus(void)
{  
  /* Test if TPS6572 is ready */
  while ((TPS6572_Status() == CPAL_FAIL) && TPS6572_Timeout)  
  {
    TPS6572_Timeout--;
  }
  
  /* If TPS6572 is not responding return ERROR */
  if (TPS6572_Timeout == 0)
  {
	CPAL_LOG("\n\rLOG <TPS6572_GetStatus> : ERROR TPS6572_Timeout");
    return ERROR;
  }
  
  /* In other case return SUCCESS */
  CPAL_LOG("\n\rLOG <TPS6572_GetStatus> : SUCCESS");
  return SUCCESS;  
}


#include "Accelerometer_LIS3DSH_REG.h"
/**
  * @brief  Read the specified register from the TPS6572.
  * @param  RegName: specifies the TPS6572 register to be read.
  *              This member can be one of the following values:  
  *                  - TPS6572_REG_TEMP: temperature register
  *                  - TPS6572_REG_TOS: Over-limit temperature register
  *                  - TPS6572_REG_THYS: Hysteresis temperature register
  * @retval TPS6572 register value.
  */
uint16_t TPS6572_ReadReg(uint8_t RegName)
{   
  uint16_t tmp = 0;
  
  TPS6572_Buffer[0] = 0;
  TPS6572_Buffer[1] = 0;
  
  /* Disable all options */
  TPS6572_DevStructure.wCPAL_Options = 0;

  /* point to CPAL_TransferTypeDef structure */
  TPS6572_DevStructure.pCPAL_TransferRx = &TPS6572_RXTransfer;
  
  /* Configure transfer parameters */  
  TPS6572_DevStructure.pCPAL_TransferRx->wNumData = 2;
  TPS6572_DevStructure.pCPAL_TransferRx->pbBuffer = TPS6572_Buffer ;
  TPS6572_DevStructure.pCPAL_TransferRx->wAddr1   = (uint32_t)LIS3DSH_DEVICE_ADDRES_SA0_1;
  TPS6572_DevStructure.pCPAL_TransferRx->wAddr2   = (uint32_t)RegName;
  
  /* Read Operation */
  if(CPAL_I2C_Read(&TPS6572_DevStructure) == CPAL_PASS)
  {
	CPAL_LOG("\n\rLOG <CPAL_I2C_Read> : CPAL_PASS");
    while ((TPS6572_DevStructure.CPAL_State != CPAL_STATE_READY) && (TPS6572_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
    { }
  }
  
  /* Store TPS6572_I2C received data */
  tmp = (uint16_t)(TPS6572_Buffer[0] << 8);
  tmp |= TPS6572_Buffer[1];
  
  /* return a Reg value */
  return (uint16_t)tmp;  
}

/**
  * @brief  Write to the specified register of the TPS6572.
  * @param  RegName: specifies the TPS6572 register to be written.
  *              This member can be one of the following values:    
  *                  - TPS6572_REG_TOS: Over-limit temperature register
  *                  - TPS6572_REG_THYS: Hysteresis temperature register
  * @param  RegValue: value to be written to TPS6572 register.  
  * @retval None
  */
uint8_t TPS6572_WriteReg(uint8_t RegName, uint16_t RegValue)
{   
  TPS6572_Buffer[0] = (uint8_t)(RegValue >> 8);
  TPS6572_Buffer[1] = (uint8_t)(RegValue);
     
  /* Disable all options */
  TPS6572_DevStructure.wCPAL_Options = 0;
  
  /* point to CPAL_TransferTypeDef structure */
  TPS6572_DevStructure.pCPAL_TransferTx = &TPS6572_TXTransfer;
  
  /* Configure transfer parameters */  
  TPS6572_DevStructure.pCPAL_TransferTx->wNumData = 2;
  TPS6572_DevStructure.pCPAL_TransferTx->pbBuffer = TPS6572_Buffer ;
  TPS6572_DevStructure.pCPAL_TransferTx->wAddr1   = (uint32_t)TPS6572_ADDR;
  TPS6572_DevStructure.pCPAL_TransferTx->wAddr2   = (uint32_t)RegName;
  
  /* Write Operation */
  if(CPAL_I2C_Write(&TPS6572_DevStructure) == CPAL_PASS)
  {
	CPAL_LOG("\n\rLOG <CPAL_I2C_Write> : CPAL_PASS");
    while ((TPS6572_DevStructure.CPAL_State != CPAL_STATE_READY) && (TPS6572_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
    { }
    
    if (TPS6572_DevStructure.CPAL_State == CPAL_STATE_ERROR)
    {
		 CPAL_LOG("\n\rLOG <CPAL_I2C_Write> : CPAL_STATE_ERROR");
      return TPS6572_FAIL;
    }
  }
  else
  {
	  CPAL_LOG("\n\rLOG <CPAL_I2C_Write> : TPS6572_FAIL");
    return TPS6572_FAIL;
  }
  
  return TPS6572_OK;
}

/**
  * @brief  Read Temperature register of TPS6572: double temperature value.
  * @param  None
  * @retval TPS6572 measured temperature value.
  */
uint16_t TPS6572_ReadTemp(void)
{   
  uint16_t tmp = 0;
  
  TPS6572_Buffer[0] = 0;
  TPS6572_Buffer[1] = 0;
  
  /* Disable all options */
  TPS6572_DevStructure.wCPAL_Options = 0;

  /* point to CPAL_TransferTypeDef structure */
  TPS6572_DevStructure.pCPAL_TransferRx = &TPS6572_RXTransfer;
  
  /* Configure transfer parameters */  
  TPS6572_DevStructure.pCPAL_TransferRx->wNumData = 2;
  TPS6572_DevStructure.pCPAL_TransferRx->pbBuffer = TPS6572_Buffer ;
  TPS6572_DevStructure.pCPAL_TransferRx->wAddr1   = (uint32_t)TPS6572_ADDR;
  TPS6572_DevStructure.pCPAL_TransferRx->wAddr2   = (uint32_t)TPS6572_REG_TEMP;
  
  /* Read Operation */
  if(CPAL_I2C_Read(&TPS6572_DevStructure) == CPAL_PASS)
  {
    while ((TPS6572_DevStructure.CPAL_State != CPAL_STATE_READY) && (TPS6572_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
    { }
  }
  
  /* Store TPS6572_I2C received data */
  tmp = (uint16_t)(TPS6572_Buffer[0] << 8);
  tmp |= TPS6572_Buffer[1];    
  
  /* Return Temperature value */
  return (uint16_t)(tmp >> 7);
}

/**
  * @brief  Read the configuration register from the TPS6572.
  * @param  None
  * @retval TPS6572 configuration register value.
  */
uint8_t TPS6572_ReadConfReg(void)
{    
  TPS6572_Buffer[0] = 0;
  
  /* Disable all options */
  TPS6572_DevStructure.wCPAL_Options = 0;
  
  /* point to CPAL_TransferTypeDef structure */
  TPS6572_DevStructure.pCPAL_TransferRx = &TPS6572_RXTransfer;
  
  /* Configure transfer parameters */  
  TPS6572_DevStructure.pCPAL_TransferRx->wNumData = 1;
  TPS6572_DevStructure.pCPAL_TransferRx->pbBuffer = TPS6572_Buffer ;
  TPS6572_DevStructure.pCPAL_TransferRx->wAddr1   = (uint32_t)TPS6572_ADDR;
  TPS6572_DevStructure.pCPAL_TransferRx->wAddr2   = (uint32_t)TPS6572_REG_CONF;
  
  /* Read Operation */
  if(CPAL_I2C_Read(&TPS6572_DevStructure) == CPAL_PASS)
  {
    while ((TPS6572_DevStructure.CPAL_State != CPAL_STATE_READY) && (TPS6572_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
    { }
  }
  
  /* Return Temperature value */
  return (uint8_t)TPS6572_Buffer[0];
}

/**
  * @brief  Write to the configuration register of the TPS6572.
  * @param  RegValue: specifies the value to be written to TPS6572 configuration 
  *         register.
  * @retval None
  */
uint8_t TPS6572_WriteConfReg(uint8_t RegValue)
{   
  TPS6572_Buffer[0] = (uint8_t)(RegValue);
    
  /* Disable all options */
  TPS6572_DevStructure.wCPAL_Options = 0;
  
  /* point to CPAL_TransferTypeDef structure */
  TPS6572_DevStructure.pCPAL_TransferTx = &TPS6572_TXTransfer;
  
  /* Configure transfer parameters */  
  TPS6572_DevStructure.pCPAL_TransferTx->wNumData = 1;
  TPS6572_DevStructure.pCPAL_TransferTx->pbBuffer = TPS6572_Buffer ;
  TPS6572_DevStructure.pCPAL_TransferTx->wAddr1   = (uint32_t)TPS6572_ADDR;
  TPS6572_DevStructure.pCPAL_TransferTx->wAddr2   = (uint32_t)TPS6572_REG_CONF;
  
  /* Write Operation */
  if(CPAL_I2C_Write(&TPS6572_DevStructure) == CPAL_PASS)
  {
    while ((TPS6572_DevStructure.CPAL_State != CPAL_STATE_READY) && (TPS6572_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
    { }
    
    if (TPS6572_DevStructure.CPAL_State == CPAL_STATE_ERROR)
    {
      return TPS6572_FAIL;
    }
  }
  else
  {
    return TPS6572_FAIL;
  }
  
  return TPS6572_OK;
  
}

/**
  * @brief  Enables or disables the TPS6572.
  * @param  NewState: specifies the TPS6572 new status. This parameter can be ENABLE
  *         or DISABLE.  
  * @retval None
  */
uint8_t TPS6572_ShutDown(FunctionalState NewState)
{   
  __IO uint8_t RegValue = 0;    
  
  TPS6572_Buffer[0] = 0;
  		  
  /* Disable all options */
  TPS6572_DevStructure.wCPAL_Options = 0;

  /* point to CPAL_TransferTypeDef structure */
  TPS6572_DevStructure.pCPAL_TransferRx = &TPS6572_RXTransfer;
  
  /* Configure transfer parameters */  
  TPS6572_DevStructure.pCPAL_TransferRx->wNumData = 1;
  TPS6572_DevStructure.pCPAL_TransferRx->pbBuffer = TPS6572_Buffer ;
  TPS6572_DevStructure.pCPAL_TransferRx->wAddr1   = (uint32_t)TPS6572_ADDR;
  TPS6572_DevStructure.pCPAL_TransferRx->wAddr2   = (uint32_t)TPS6572_REG_CONF;
  
  /* Read Operation */
  if(CPAL_I2C_Read(&TPS6572_DevStructure) == CPAL_PASS)
  {
    while ((TPS6572_DevStructure.CPAL_State != CPAL_STATE_READY) && (TPS6572_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
    { }
  }
  
  /* Get received data */
  RegValue = (uint8_t)TPS6572_Buffer[0];
  
  /*---------------------------- Transmission Phase ---------------------------*/
  
  /* Enable or disable SD bit */
  if (NewState != DISABLE)
  {
    /* Enable TPS6572 */
    TPS6572_Buffer[0] = RegValue & TPS6572_SD_RESET;
  }
  else
  {
    /* Disable TPS6572 */
    TPS6572_Buffer[0] = RegValue | TPS6572_SD_SET;
  }  
  
  /* point to CPAL_TransferTypeDef structure */
  TPS6572_DevStructure.pCPAL_TransferTx = &TPS6572_TXTransfer;
  
  /* Configure transfer parameters */  
  TPS6572_DevStructure.pCPAL_TransferTx->wNumData = 1;
  TPS6572_DevStructure.pCPAL_TransferTx->pbBuffer = TPS6572_Buffer ;
  TPS6572_DevStructure.pCPAL_TransferTx->wAddr1   = (uint32_t)TPS6572_ADDR;
  TPS6572_DevStructure.pCPAL_TransferTx->wAddr2   = (uint32_t)TPS6572_REG_CONF;
  
  /* Write Operation */
  if(CPAL_I2C_Write(&TPS6572_DevStructure) == CPAL_PASS)
  {
    while ((TPS6572_DevStructure.CPAL_State != CPAL_STATE_READY) && (TPS6572_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
    { }
    
    if (TPS6572_DevStructure.CPAL_State == CPAL_STATE_ERROR)
    {
      return TPS6572_FAIL;
    }
  }
  else
  {
    return TPS6572_FAIL;
  }
  
  return TPS6572_OK;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
