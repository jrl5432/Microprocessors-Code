#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "lis3dsh.h"

/*All the necessary files to configure the timer
*/

TIM_HandleTypeDef TIM_Handle;
int digit_flag = 0;
int first_digit = 0;
int second_digit = 1;
int third_digit = 2;

long counter = 0;

void Timer_Config(void)
{
	__TIM3_CLK_ENABLE();
    TIM_Handle.Init.Prescaler = 6720;
    TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM_Handle.Init.Period = 1;
    TIM_Handle.Instance = TIM3;   //Same timer whose clocks we enabled
    HAL_TIM_Base_Init(&TIM_Handle);     // Init timer
    HAL_TIM_Base_Start_IT(&TIM_Handle); // start timer interrupts
    HAL_NVIC_SetPriority(TIM3_IRQn, 3, 3);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void)
{
    if (__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
    {
        if (__HAL_TIM_GET_ITSTATUS(&TIM_Handle, TIM_IT_UPDATE) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
					
					//change the code below!
					
					counter = counter +1;
					if(counter == 2500)
					{
						first_digit = 5;
						second_digit = 6;
						third_digit = 7;
					}
					else if(counter == 5000)
					{
						first_digit = 1;
						second_digit = 2;
						third_digit = 3;
						counter = 0;
					}
					if(digit_flag == 0)
					{
						First_Digit_Set();
						Set_Number(first_digit);
						digit_flag = 1;
					}
					else if(digit_flag == 1)
					{
						Second_Digit_Set();
						Set_Number(second_digit);
						digit_flag = 2;
					}
					else
					{
						Third_Digit_Set();
						Set_Number(third_digit);
						digit_flag = 0;
					}
					
        }
    }
}