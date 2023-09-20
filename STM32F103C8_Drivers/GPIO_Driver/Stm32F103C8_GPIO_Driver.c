/*
 * Stm32F103C8_GPIO_Driver.c
 *
 *  Created on: Sep 20, 2023
 *      Author: Ziad Mahmoud Saad
 */

//-*-*-*-*-*
//	Includes
//-*-*-*-*-*

#include "Stm32F103C8_GPIO_Driver.h"


//=========================================================


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//	Macros Configuration References
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*






//=========================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//	APIs Supported by "MCAL GPIO DRIVER"
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


uint8_t Get_CRLH_Position(uint16_t PinNum){
	switch (PinNum) {
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}



//***********************************

/* @Fn			-GPIO_Init
* @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinConfig pointer to a GPIO_PinConfig_t structure that contains the configuration information for the specified GPIO PIN.
* @retval 		-none
* Note			-Stm32F103x8 MCU has GPIO A,B,C,D,E Modules
*/


void GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PIN_Config* PinConfig )
{
	// Port configuration register low (GPIOx_CRL) Configure PINS from 0 >>> 7
	// Port configuration register High (GPIOx_CRH) Configure PINS from 8 >>> 15
	volatile uint32_t* ConfigReg = NULL ;
	volatile uint8_t Config_PIN = 0 ;

	ConfigReg =(PinConfig->pin_number < GPIO_PIN_8 )? &GPIOx->CRL : &GPIOx->CRH ;

	// Clear CNF & MODE
	(*ConfigReg) &= ~(0xF <<Get_CRLH_Position(PinConfig->pin_number)) ;

	// PIN is Output
	if((PinConfig->pin_mode == GPIO_MODE_Output_PUSH_PULL) || (PinConfig->pin_mode == GPIO_MODE_Output_OPEN_DRAIN) ||(PinConfig->pin_mode == GPIO_MODE_Output_AF_PUSH_PULL) ||(PinConfig->pin_mode == GPIO_MODE_Output_AF_OPEN_DRAIN))
	{
		// Set CNF & MODE
		Config_PIN = ((((PinConfig->pin_mode -4 ) << 2) | (PinConfig->pin_speed)) & 0xF);

	}
	else //PIN is Input
	{
		// Input Analog || Input floating
		if((PinConfig->pin_mode == GPIO_MODE_Analog) || (PinConfig->pin_mode == GPIO_MODE_Floating_Input))
		{
			// Set CNF & MODE
			Config_PIN = ((PinConfig->pin_mode << 2) & 0xF) ;
		}
		else // Input pull-down || Input pull-up
		{
			// Set CNF & MODE
			Config_PIN = ((GPIO_MODE_Input_PUll_UP << 2) & 0xF) ;

			if(PinConfig->pin_mode == GPIO_MODE_Input_PUll_DOWN)// Input pull-down
			{
				//PxODR = 0 Input pull-down :Table 20. Port bit configuration table
				GPIOx->ODR &= ~( PinConfig->pin_number ) ;
			}
			else // Input pull-up
			{
				//PxODR = 1 Input pull-up :Table 20. Port bit configuration table
				GPIOx->ODR |=  PinConfig->pin_number ;
			}
		}
	}

	// write on the CRL or CRH
	*ConfigReg |= (Config_PIN <<Get_CRLH_Position(PinConfig->pin_number));
}



//***********************************

/* @Fn			-GPIO_DeInit
* @brief 		-Reset all GPIO Registers
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @retval 		-none
* Note			-none
*/

void GPIO_DeInit (GPIO_TypeDef *GPIOx )
{
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= ( 1<<2 ) ;
		RCC->APB2RSTR &= ~( 1<<2 ) ;
	}
	else if( GPIOx == GPIOB )
	{
		RCC->APB2RSTR |= ( 1<<3 ) ;
		RCC->APB2RSTR &= ~( 1<<3 ) ;
	}
	else if( GPIOx == GPIOC )
	{
		RCC->APB2RSTR |= ( 1<<4 ) ;
		RCC->APB2RSTR &= ~( 1<<4 ) ;
	}
	else if( GPIOx == GPIOD )
	{
		RCC->APB2RSTR |= ( 1<<5 ) ;
		RCC->APB2RSTR &= ~( 1<<5 ) ;
	}
	else if( GPIOx == GPIOE )
	{
		RCC->APB2RSTR |= ( 1<<6 ) ;
		RCC->APB2RSTR &= ~( 1<<6 ) ;
	}
}



//***********************************

/* @Fn			-GPIO_ReadPin
* @brief 		-Read specified PIN value
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinNumber: Set pin number according to @ref GPIO_PINs_Define
* @retval 		-the input pin value ,based on @ref GPIO_PIN_State
* Note			-none
*/


uint8_t GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber )
{
	uint8_t bitstatus ;
	if((( GPIOx->IDR ) & PinNumber) != (uint32_t)GPIO_PIN_RESET )
	{
		bitstatus = GPIO_PIN_SET ;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET ;
	}
	return bitstatus ;
}



//***********************************

/* @Fn			-GPIO_ReadPort
* @brief 		-Read specified GPIOx value
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @retval 		-the input port value
* Note			-none
*/

uint16_t GPIO_ReadPort (GPIO_TypeDef *GPIOx)
{
	return ((uint16_t) GPIOx->IDR) ;
}



//***********************************

/* @Fn			-GPIO_WritePin
* @brief 		-Write on specified output pin
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinNumber: Set pin number according to @ref GPIO_PINs_Define
* @param [in] 	-Value: output pin value
* @retval 		-none
* Note			-none
*/

void GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber , uint8_t Value )
{
	if( Value == GPIO_PIN_SET)
	{
	// Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
	// These bits are write-only and can be accessed in Word mode only.
	// 0: No action on the corresponding ODRx bit
	// 1: Set the corresponding ODRx bit
		GPIOx->BSRR =(uint32_t)PinNumber ;
	}
	else
	{
	// Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
	// These bits are write-only and can be accessed in Word mode only.
	// 0: No action on the corresponding ODRx bit
	// 1: Reset the corresponding ODRx bit
		GPIOx->BRR =(uint16_t)PinNumber ;
	}
}




//***********************************

/* @Fn			-GPIO_WritePort
* @brief 		-Write on specified GPIOx
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-Value: output port value
* @retval 		-none
* Note			-none
*/

void GPIO_WritePort (GPIO_TypeDef *GPIOx, uint16_t Value )
{
	GPIOx->ODR = (uint32_t)Value ;
}



//***********************************

/* @Fn			-GPIO_TogglePin
* @brief 		-Toggle specified output pin
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinNumber: Set pin number according to @ref GPIO_PINs_Define
* @retval 		-none
* Note			-none
*/

void GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber )
{
	GPIOx->ODR ^= (PinNumber) ;
}



//***********************************

/* @Fn			-GPIO_LockPin
* @brief 		-Lock specified pin
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinNumber: Set pin number according to @ref GPIO_PINs_Define
* @retval 		-lock state,If its OK or ERROR  based on @ref GPIO_PINs_LOCK_State
* Note			-none
*/

uint8_t GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber )
{
	// Bit 16 LCKK[16]: Lock key
	// This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	// 0: Port configuration lock key not active
	// 1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	// LOCK key writing sequence:
	// Write 1
	// Write 0
	// Write 1
	// Read 0
	// Read 1 (this read is optional but confirms that the lock is active)
	// Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	// Any error in the lock sequence will abort the lock.
	//
	// Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	// These bits are read write but can only be written when the LCKK bit is 0.
	// 0: Port configuration not locked
	// 1: Port configuration locked.

	volatile uint32_t temp = 0x10000 ;
	temp |= PinNumber ;

	// Write 1
	GPIOx->LCKR = temp ;
	// Write 0
	GPIOx->LCKR = PinNumber ;
	// Write 1
	GPIOx->LCKR = temp ;
	// Read 0
	temp = GPIOx->LCKR ;

	// Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & 0x10000))
	{
		return GPIO_PIN_LOCK_ENABLED ;
	}
	else
	{
		return GPIO_PIN_LOCK_ERROR ;
	}


}

