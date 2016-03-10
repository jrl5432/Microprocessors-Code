/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program subroutine
	* Author						 : Ashraf Suyyagh
	* Version            : 1.0.0
	* Date							 : January 14th, 2016
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "lis3dsh.h"


/* Private variables ---------------------------------------------------------*/
static int16_t* values;


/* Private function prototypes -----------------------------------------------*/
int main(void)
{	
  /* MCU Configuration----------------------------------------------------------*/

  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();
	
  /* Initialize all configured peripherals */
	//first configure the GPIO for the accelerometer
	Configure_Accel_GPIO();
	Configure_Accel();
	
	while (1)
		{
			values = Accelerometer_Read();
			//printf("The x value is:\t%d\n",values[0]);
			//printf("The y value is:\t%d\n",values[1]);
			//printf("The z value is:\t%d\n",values[2]);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	printf("HELLO!");
}


#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line){
}
#endif

