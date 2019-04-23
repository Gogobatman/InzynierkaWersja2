/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t data[5]={0,0,0,0,0};
uint8_t matrix[64]={
            
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
            
            
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
            
            
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
            
            
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
                    'X','X', 'X', 'X',
            
    };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch);
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,0);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
			HAL_StatusTypeDef status = HAL_UART_Receive(&huart1, data,3,1000);  //bez & bo tablica jest wskaznikiem, a 5 Ci mowi ile bajtow ma wziac
			//HAL_StatusTypeDef status = HAL_UART_Receive(&huart1, &data,1,1000);  gdy uint8_t data
			
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
			
			if(status == HAL_OK) {
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1);
					if(data[0]=='1' && data[1]=='1' && data[2]=='1'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[0]='R';
					}else if(data[0]=='2' && data[1]=='1' && data[2]=='1'){ 
							matrix[1]='R';
					}else if(data[0]=='3' && data[1]=='1' && data[2]=='1'){ 
							matrix[2]='R';
					}else if(data[0]=='4' && data[1]=='1' && data[2]=='1'){ 
							matrix[3]='R';
					}
					
					else if(data[0]=='1' && data[1]=='2' && data[2]=='1'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[4]='R';
					}else if(data[0]=='2' && data[1]=='2' && data[2]=='1'){ 
							matrix[5]='R';
					}else if(data[0]=='3' && data[1]=='2' && data[2]=='1'){ 
							matrix[6]='R';
					}else if(data[0]=='4' && data[1]=='2' && data[2]=='1'){ 
							matrix[7]='R';
					}
					
					else if(data[0]=='1' && data[1]=='3' && data[2]=='1'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[8]='R';
					}else if(data[0]=='2' && data[1]=='3' && data[2]=='1'){ 
							matrix[9]='R';
					}else if(data[0]=='3' && data[1]=='3' && data[2]=='1'){ 
							matrix[10]='R';
					}else if(data[0]=='4' && data[1]=='3' && data[2]=='1'){ 
							matrix[11]='R';
					}
					
					else if(data[0]=='1' && data[1]=='4' && data[2]=='1'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[12]='R';
					}else if(data[0]=='2' && data[1]=='4' && data[2]=='1'){ 
							matrix[13]='R';
					}else if(data[0]=='3' && data[1]=='4' && data[2]=='1'){ 
							matrix[14]='R';
					}else if(data[0]=='4' && data[1]=='4' && data[2]=='1'){ 
							matrix[15]='R';
					}
					////////////////////////////////////////
					if(data[0]=='1' && data[1]=='1' && data[2]=='2'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[16]='R';
					}else if(data[0]=='2' && data[1]=='1' && data[2]=='2'){ 
							matrix[17]='R';
					}else if(data[0]=='3' && data[1]=='1' && data[2]=='2'){ 
							matrix[18]='R';
					}else if(data[0]=='4' && data[1]=='1' && data[2]=='2'){ 
							matrix[19]='R';
					}
					
					else if(data[0]=='1' && data[1]=='2' && data[2]=='2'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[20]='R';
					}else if(data[0]=='2' && data[1]=='2' && data[2]=='2'){ 
							matrix[21]='R';
					}else if(data[0]=='3' && data[1]=='2' && data[2]=='2'){ 
							matrix[22]='R';
					}else if(data[0]=='4' && data[1]=='2' && data[2]=='2'){ 
							matrix[23]='R';
					}
					
					else if(data[0]=='1' && data[1]=='3' && data[2]=='2'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[24]='R';
					}else if(data[0]=='2' && data[1]=='3' && data[2]=='2'){ 
							matrix[25]='R';
					}else if(data[0]=='3' && data[1]=='3' && data[2]=='2'){ 
							matrix[26]='R';
					}else if(data[0]=='4' && data[1]=='3' && data[2]=='2'){ 
							matrix[27]='R';
					}
					
					else if(data[0]=='1' && data[1]=='4' && data[2]=='2'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[28]='R';
					}else if(data[0]=='2' && data[1]=='4' && data[2]=='2'){ 
							matrix[29]='R';
					}else if(data[0]=='3' && data[1]=='4' && data[2]=='2'){ 
							matrix[30]='R';
					}else if(data[0]=='4' && data[1]=='4' && data[2]=='2'){ 
							matrix[31]='R';
					}
					//////////////////////////////////////////////
					if(data[0]=='1' && data[1]=='1' && data[2]=='3'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[32]='R';
					}else if(data[0]=='2' && data[1]=='1' && data[2]=='3'){ 
							matrix[33]='R';
					}else if(data[0]=='3' && data[1]=='1' && data[2]=='3'){ 
							matrix[34]='R';
					}else if(data[0]=='4' && data[1]=='1' && data[2]=='3'){ 
							matrix[35]='R';
					}
					
					else if(data[0]=='1' && data[1]=='2' && data[2]=='3'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[36]='R';
					}else if(data[0]=='2' && data[1]=='2' && data[2]=='3'){ 
							matrix[37]='R';
					}else if(data[0]=='3' && data[1]=='2' && data[2]=='3'){ 
							matrix[38]='R';
					}else if(data[0]=='4' && data[1]=='2' && data[2]=='3'){ 
							matrix[39]='R';
					}
					
					else if(data[0]=='1' && data[1]=='3' && data[2]=='3'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[40]='R';
					}else if(data[0]=='2' && data[1]=='3' && data[2]=='3'){ 
							matrix[41]='R';
					}else if(data[0]=='3' && data[1]=='3' && data[2]=='3'){ 
							matrix[42]='R';
					}else if(data[0]=='4' && data[1]=='3' && data[2]=='3'){ 
							matrix[43]='R';
					}
					
					else if(data[0]=='1' && data[1]=='4' && data[2]=='3'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[44]='R';
					}else if(data[0]=='2' && data[1]=='4' && data[2]=='3'){ 
							matrix[45]='R';
					}else if(data[0]=='3' && data[1]=='4' && data[2]=='3'){ 
							matrix[46]='R';
					}else if(data[0]=='4' && data[1]=='4' && data[2]=='3'){ 
							matrix[47]='R';
					}
					////////////////////////////////////////
					if(data[0]=='1' && data[1]=='1' && data[2]=='1'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[48]='R';
					}else if(data[0]=='2' && data[1]=='1' && data[2]=='4'){ 
							matrix[49]='R';
					}else if(data[0]=='3' && data[1]=='1' && data[2]=='4'){ 
							matrix[50]='R';
					}else if(data[0]=='4' && data[1]=='1' && data[2]=='4'){ 
							matrix[51]='R';
					}
					
					else if(data[0]=='1' && data[1]=='2' && data[2]=='4'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[52]='R';
					}else if(data[0]=='2' && data[1]=='2' && data[2]=='4'){ 
							matrix[53]='R';
					}else if(data[0]=='3' && data[1]=='2' && data[2]=='4'){ 
							matrix[54]='R';
					}else if(data[0]=='4' && data[1]=='2' && data[2]=='4'){ 
							matrix[55]='R';
					}
					
					else if(data[0]=='1' && data[1]=='3' && data[2]=='4'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[56]='R';
					}else if(data[0]=='2' && data[1]=='3' && data[2]=='4'){ 
							matrix[57]='R';
					}else if(data[0]=='3' && data[1]=='3' && data[2]=='4'){ 
							matrix[58]='R';
					}else if(data[0]=='4' && data[1]=='3' && data[2]=='4'){ 
							matrix[59]='R';
					}
					
					else if(data[0]=='1' && data[1]=='4' && data[2]=='1'){ //pierwsze 3 to wspolrzedne, 4 to gracz, 4 czy wygrana
							matrix[60]='R';
					}else if(data[0]=='2' && data[1]=='4' && data[2]=='1'){ 
							matrix[61]='R';
					}else if(data[0]=='3' && data[1]=='4' && data[2]=='1'){ 
							matrix[62]='R';
					}else if(data[0]=='4' && data[1]=='4' && data[2]=='1'){ 
							matrix[63]='R';
					}
			HAL_UART_Transmit(&huart1,matrix,64,1000);
			HAL_Delay(3000);
			//NVIC_SystemReset(); //ogarnij czy to resetuje cala rozgrywke
  
}
}
	
}

  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
