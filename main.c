#include "main.h"

void SystemClock_Config(void);

int main(void)
{
  //Set portC pin 9 as input
  //Enable portC clock
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  //Mode Register
  GPIOC->MODER &= ~GPIO_MODER_MODER9_0;
  GPIOC->MODER &= ~GPIO_MODER_MODER9_1;
  //Pull Up Pull Down Register
  GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR9_0;
  GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR9_1;

  //Set portA pin 7 as output
  //Enable portA clock
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  //Mode Register
  GPIOA->MODER |= GPIO_MODER_MODER7_0;
  GPIOA->MODER &= ~GPIO_MODER_MODER7_1;
  //Output Type Register
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT_7;
  //Output Speed Register
  GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR7_0;
  GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR7_1;

  int toggledThisPress = 0;

  while (1)
  {
	  //Turn LED on iff button is being pressed and led hasn't been toggled this press
	  if(GPIOC->IDR & 0x200){
		  if(!toggledThisPress){
			  GPIOA->ODR ^= GPIO_ODR_7;
			  toggledThisPress = 1;
		  }
	  }
	  else{toggledThisPress = 0;}

  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
