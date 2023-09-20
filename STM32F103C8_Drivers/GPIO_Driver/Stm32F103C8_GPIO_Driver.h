/*
 * Stm32F103C8_GPIO_Driver.h
 *
 *  Created on: Sep 20, 2023
 *      Author: Ziad Mahmoud Saad
 */

#ifndef STM32F103C8_GPIO_DRIVER_H_
#define STM32F103C8_GPIO_DRIVER_H_

//-*-*-*-*-*
//	Includes
//-*-*-*-*-*

#include "Stm32F103x8.h"


//=========================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//	User type definitions (structures)
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	uint16_t pin_number; 	// Specifies the GPIO pin to be configured
							// and must be set based on @ref GPIO_PINs_Define.
	uint16_t pin_mode;		// Specifies mode for the selected pin
							// and can be set based on @ref GPIO_MODE_Define
	uint16_t pin_speed;		// Specifies speed for the selected pin
							// and can be set based on @ref GPIO_SPEED_Define


}GPIO_PIN_Config;


//=========================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//	Macros Configuration References
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//------------------
//	@ref GPIO_PINs_Define
//------------------
#define GPIO_PIN_0			((uint16_t)0x0001)
#define GPIO_PIN_1			((uint16_t)0x0002)
#define GPIO_PIN_2			((uint16_t)0x0004)
#define GPIO_PIN_3			((uint16_t)0x0008)
#define GPIO_PIN_4			((uint16_t)0x0010)
#define GPIO_PIN_5			((uint16_t)0x0020)
#define GPIO_PIN_6			((uint16_t)0x0040)
#define GPIO_PIN_7			((uint16_t)0x0080)
#define GPIO_PIN_8			((uint16_t)0x0100)
#define GPIO_PIN_9			((uint16_t)0x0200)
#define GPIO_PIN_10			((uint16_t)0x0400)
#define GPIO_PIN_11			((uint16_t)0x0800)
#define GPIO_PIN_12			((uint16_t)0x1000)
#define GPIO_PIN_13			((uint16_t)0x2000)
#define GPIO_PIN_14			((uint16_t)0x4000)
#define GPIO_PIN_15			((uint16_t)0x8000)
#define GPIO_PIN_ALL		((uint16_t)0xFFFF)


//------------------
//	@ref GPIO_MODE_Define
//------------------
// 0: Analog mode
// 1: Floating input (reset state)
// 2: Input with pull-up
// 3: Input with pull-down
// 4: General purpose output push-pull
// 5: General purpose output Open-drain
// 6: Alternate function output Push-pull
// 7: Alternate function output Open-drain
#define GPIO_MODE_Analog					0x0U
#define GPIO_MODE_Floating_Input			0x1U
#define GPIO_MODE_Input_PUll_UP				0x2U
#define GPIO_MODE_Input_PUll_DOWN			0x3U
#define GPIO_MODE_Output_PUSH_PULL			0x4U
#define GPIO_MODE_Output_OPEN_DRAIN			0x5U
#define GPIO_MODE_Output_AF_PUSH_PULL		0x6U
#define GPIO_MODE_Output_AF_OPEN_DRAIN		0x7U


//------------------
//	@ref GPIO_SPEED_Define
//------------------
// 1: Output mode, max speed 10 MHz.
// 2: Output mode, max speed 2 MHz.
// 3: Output mode, max speed 50 MHz
#define GPIO_SPEED_10MHz  					0x1U
#define GPIO_SPEED_2MHz						0x2U
#define GPIO_SPEED_50MHz					0x3U


//------------------
//	@ref GPIO_PIN_State
//------------------
#define GPIO_PIN_SET  					1
#define GPIO_PIN_RESET					0


//------------------
//	@ref GPIO_PIN_State
//------------------
#define GPIO_PIN_LOCK_ENABLED			1
#define GPIO_PIN_LOCK_ERROR				0
//=========================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//	APIs Supported by "MCAL GPIO DRIVER"
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//***********************************

/* @Fn			-GPIO_Init
* @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinConfig pointer to a GPIO_PinConfig_t structure that contains the configuration information for the specified GPIO PIN.
* @retval 		-none
* Note			-Stm32F103x8 MCU has GPIO A,B,C,D,E Modules
*/

void GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PIN_Config* PinConfig );


//***********************************

/* @Fn			-GPIO_DeInit
* @brief 		-Reset all GPIO Registers
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @retval 		-none
* Note			-none
*/

void GPIO_DeInit (GPIO_TypeDef *GPIOx );


//***********************************

/* @Fn			-GPIO_ReadPin
* @brief 		-Read specified PIN value
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinNumber: Set pin number according to @ref GPIO_PINs_Define
* @retval 		-the input pin value ,based on @ref GPIO_PIN_State
* Note			-none
*/

uint8_t GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber );


//***********************************

/* @Fn			-GPIO_ReadPort
* @brief 		-Read specified GPIOx value
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @retval 		-the input port value
* Note			-none
*/

uint16_t GPIO_ReadPort (GPIO_TypeDef *GPIOx);


//***********************************

/* @Fn			-GPIO_WritePin
* @brief 		-Write on specified output pin
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinNumber: Set pin number according to @ref GPIO_PINs_Define
* @param [in] 	-Value: output pin value
* @retval 		-none
* Note			-none
*/

void GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber , uint8_t Value );



//***********************************

/* @Fn			-GPIO_WritePort
* @brief 		-Write on specified GPIOx
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-Value: output port value
* @retval 		-none
* Note			-none
*/

void GPIO_WritePort (GPIO_TypeDef *GPIOx, uint16_t Value );


//***********************************

/* @Fn			-GPIO_TogglePin
* @brief 		-Toggle specified output pin
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinNumber: Set pin number according to @ref GPIO_PINs_Define
* @retval 		-none
* Note			-none
*/

void GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber );



//***********************************

/* @Fn			-GPIO_LockPin
* @brief 		-Lock specified pin
* @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	-PinNumber: Set pin number according to @ref GPIO_PINs_Define
* @retval 		-lock state,If its OK or ERROR  based on @ref GPIO_PINs_LOCK_State
* Note			-none
*/

uint8_t GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber );

#endif /* STM32F103C8_GPIO_DRIVER_H_ */
