/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * Description of project
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "ts_calibration.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/



volatile int timer=0;
volatile int colour=0;


/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
	HAL_IncTick();

}
void EXTI0_IRQHandler(void){
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	timer = ! timer;
}
void EXTI3_IRQHandler(void){
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
	colour = ! colour;
}


/**

 */
int main(void)
{
	/* MCU Configuration--------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();


	int cnt=0;
	int cnt1=0;


	/* Initialize LCD and touch screen */
	LCD_Init();
	TS_Init(LCD_GetXSize(), LCD_GetYSize());
	/* touch screen calibration */
	//	TS_Calibration();

	/* Clear the LCD and display basic starter text */
	LCD_Clear(LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_YELLOW);
	LCD_SetBackColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font20);
	// There are 2 ways to print text to screen: using printf or LCD_* functions
	LCD_DisplayStringAtLine(0, "    HTL Wels");
	// printf Alternative
	LCD_SetPrintPosition(1, 0);
	printf(" Fischergasse 30");
	LCD_SetPrintPosition(2, 0);
	printf("   A-4600 Wels");

	LCD_SetFont(&Font8);
	LCD_SetColors(LCD_COLOR_DARKBLUE, LCD_COLOR_BLACK); // TextColor, BackColor
	LCD_DisplayStringAtLineMode(39, "copyright Mahic", CENTER_MODE);


	GPIO_InitTypeDef user;
	user.Alternate= 0;
	user.Mode=GPIO_MODE_IT_RISING;
	user.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOA, &user);

	GPIO_InitTypeDef led;
	led.Alternate=0;
	led.Mode=GPIO_MODE_OUTPUT_PP;
	led.Pull=GPIO_NOPULL;
	led.Speed=GPIO_SPEED_MEDIUM;
	led.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOG, &led);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	GPIO_InitTypeDef clr;
	clr.Alternate=0;
	clr.Mode=GPIO_MODE_IT_RISING;
	clr.Pull=GPIO_PULLDOWN;
	clr.Speed=GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOC, &clr);
	clr.Pin = GPIO_PIN_3;


	/* Infinite loop */
	while (1)
	{
		//execute main loop every 100ms
		HAL_Delay(100);

		// display timer

		LCD_SetFont(&Font20);



		LCD_SetPrintPosition(7, 0);
		printf("   Timer1: %.2f", cnt/10.0);
		LCD_SetPrintPosition(10, 0);
		printf("   Timer2: %.2f", cnt1/10.0);

		if(timer==0){
			cnt++;


		}if(timer==1){
			cnt1++;

		}

	}
}

/**
 * Check if User Button has been pressed
 * @param none
 * @return 1 if user button input (PA0) is high
 */




