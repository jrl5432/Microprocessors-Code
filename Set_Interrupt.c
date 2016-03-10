#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "lis3dsh.h"
//#include "stm32f4xx_exti.h"



/*EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void Set_Interrupt()
{
	
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_ENABLE_IT();
	
	HAL_RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	HAL_SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
	
}*/