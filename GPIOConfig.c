#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "lis3dsh.h"



/*
Configure_GPIO
No inputs, no outputs
configures the GPIO setting for the accelerometer interrupt
reads as an input, pulled down to ground --> THIS MAY NEED TO BE CHANGED
*/

GPIO_InitTypeDef GPIO_Init;

void Configure_Accel_GPIO ()
{

	__HAL_RCC_GPIOE_CLK_ENABLE();

	
  GPIO_Init.Pin = GPIO_PIN_0;
	GPIO_Init.Mode = GPIO_MODE_IT_RISING;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_Init.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE, &GPIO_Init);
	
	
}

LIS3DSH_InitTypeDef LIS3DSH_InitStruct;
LIS3DSH_DRYInterruptConfigTypeDef DRYInterruptConfig;

/*Configure the accelerometer
	*/
void Configure_Accel(void)
{
	LIS3DSH_InitStruct.Power_Mode_Output_DataRate = LIS3DSH_DATARATE_50;
	LIS3DSH_InitStruct.Axes_Enable = LIS3DSH_X_ENABLE | LIS3DSH_Y_ENABLE | LIS3DSH_Z_ENABLE;
	LIS3DSH_InitStruct.Full_Scale = LIS3DSH_FULLSCALE_4;
	LIS3DSH_InitStruct.AA_Filter_BW = LIS3DSH_AA_BW_200;
	LIS3DSH_InitStruct.Continous_Update = LIS3DSH_ContinousUpdate_Disabled;
	LIS3DSH_InitStruct.Self_Test = LIS3DSH_SELFTEST_NORMAL;
	
	
	DRYInterruptConfig.Dataready_Interrupt = LIS3DSH_DATA_READY_INTERRUPT_ENABLED;
	DRYInterruptConfig.Interrupt_signal = LIS3DSH_ACTIVE_HIGH_INTERRUPT_SIGNAL;
	DRYInterruptConfig.Interrupt_type = LIS3DSH_INTERRUPT_REQUEST_PULSED;
	
	
	LIS3DSH_DataReadyInterruptConfig(&DRYInterruptConfig);
	LIS3DSH_Init(&LIS3DSH_InitStruct);	
	
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	printf("Hello!");
}