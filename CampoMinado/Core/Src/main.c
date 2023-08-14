/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdlib.h> //biblioteca de sorteio
#include <stdio.h> //biblioteca de função com retorno

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

void PiscaLed(); //ok
void sorteio(); //ok
void fim(); //ok
void intermitente(); //ok
void Buzzer(); //ok
void Acerto(); //ok
char VerificaColuna(); //ok
char verificaLinha(); //ok
void LerCombinacao(); //ok


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  LerCombinacao();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, led_d7_Pin|led_d8_Pin|buzzer_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, led_d3_Pin|led_d4_Pin|led_d5_Pin|led_d6_Pin
                          |led_d1_Pin|led_d2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : led_d7_Pin led_d8_Pin buzzer_Pin */
  GPIO_InitStruct.Pin = led_d7_Pin|led_d8_Pin|buzzer_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : led_d3_Pin led_d4_Pin led_d5_Pin led_d6_Pin
                           led_d1_Pin led_d2_Pin */
  GPIO_InitStruct.Pin = led_d3_Pin|led_d4_Pin|led_d5_Pin|led_d6_Pin
                          |led_d1_Pin|led_d2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : bot_o_7_Pin bot_o_6_Pin bot_o_5_Pin bot_o_4_Pin */
  GPIO_InitStruct.Pin = bot_o_7_Pin|bot_o_6_Pin|bot_o_5_Pin|bot_o_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : bot_o_3_Pin bot_o_2_Pin bot_o_1_Pin bot_o_0_Pin */
  GPIO_InitStruct.Pin = bot_o_3_Pin|bot_o_2_Pin|bot_o_1_Pin|bot_o_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


void fim() {

	PiscaLed();

	Buzzer();
	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, 0);

	do {
		intermitente();
	}
	while (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7) && HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)
			&& HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) && HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) &&
			HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3) && HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)
			&& HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14) && HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)==0 );

	//desliga todos os leds
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0); //led 1
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0); //led 2
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0); //led 3
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0); //led 4
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0); //led 5
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0); //led 6
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0); //led 7
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, 0); //led 8

	return comeco();

}

void intermitente() {

	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1); //led 1
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1); //led 2
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); //led 3
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1); //led 4
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1); //led 5
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1); //led 6
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1); //led 7
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, 1); //led 8

	  HAL_Delay(200);

	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0); //led 1
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0); //led 2
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0); //led 3
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0); //led 4
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0); //led 5
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0); //led 6
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0); //led 7
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, 0); //led 8

	  HAL_Delay(200);
}

void Buzzer(){

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, 0);

}
void sorteio(){

	//linha = i; coluna = j;

	int CampoMinado [4][4];

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {
			CampoMinado[i][j] = 0;
		}
	}

	for (int b = 0; b < 4; b++) {

		int i = rand()%4;
		int j = rand()%4;

		if (CampoMinado[i][j] == 0) {
			CampoMinado[i][j] = 1;
		}

		else { b = b-1; }

	}

	LerCombinacao();

}

void PiscaLed(){

		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1); //led 1
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1); //led 2
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); //led 3
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1); //led 4
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1); //led 5
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1); //led 6
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1); //led 7
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, 1); //led 8

		  HAL_Delay(1000);

		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0); //led 1
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0); //led 2
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0); //led 3
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0); //led 4
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0); //led 5
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0); //led 6
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0); //led 7
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, 0); //led 8
}
void Acerto(){

	PiscaLed();//pisca os leds por 1 segundo
	Buzzer(); //toca o buzzer
	LerCombinacao();
}

char VerificaColuna(char *pr_c) {

	//leitura coluna
	int coluna1 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);
	int coluna2 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
	int coluna3 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
	int coluna4 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);

	//leitura linha
	int linha1 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
	int linha2 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15);
	int linha3 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14);
	int linha4 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13);

	char coluna;
	char linha;

	if (coluna1 == 1) {
		 coluna = "1";
	}
	else if (coluna2 == 1) {
		coluna = "2";
	}

	else if (coluna3 == 1) {
		coluna = "3";
	}
	else if (coluna4 == 1) {
		coluna = "4";
	}
	else { coluna = "X";
		   linha = "X"; }

	char *pr_coluna;
	pr_coluna = &coluna;
	return pr_coluna;

}

char VerificaLinha(*pr_l){

	char linha = "x";

	//leitura linha
		int linha1 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
		int linha2 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15);
		int linha3 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14);
		int linha4 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13);

		if (linha1 == 1) {
			linha = "1";
		}

		else if (linha2 == 1) {
			linha = "2";
		}

		else if (linha3 == 1) {
			linha = "3";
		}

		else if (linha4 == 1) {
			linha = "4";
		}

		*pr_linha = linha;
		pr_linha = &linha;
		return pr_linha;
}

void LerCombinacao(){

	char *pr_l;
	char *pr_c;
	VerificaColuna(*pr_c);
	VerificaLinha(*pr_l);

	if (CampoMinado[*pr_c][*pr_l] == 1) {
		fim();
	}
	else if(*pr_c == "X" || *pr_l == "X") {
		LerCombinacao();
	}
	else { Acerto();}

}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
