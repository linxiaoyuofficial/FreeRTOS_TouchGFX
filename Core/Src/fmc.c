/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : FMC.c
  * Description        : This file provides code for the configuration
  *                      of the FMC peripheral.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "fmc.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"
/* USER CODE END 0 */

SDRAM_HandleTypeDef hsdram1;        //SDRAM_HandleTypeDef 结构体变量
FMC_SDRAM_CommandTypeDef command;	// 控制指令

/******************************************************************************************************
*	函 数 名: SDRAM_Initialization_Sequence
*	入口参数: hsdram - SDRAM_HandleTypeDef定义的变量，即表示定义的sdram
*				 Command	- 控制指令
*	返 回 值: 无
*	函数功能: SDRAM 参数配置
*	说    明: 配置SDRAM相关时序和控制方式
*******************************************************************************************************/

void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef* hsdram, FMC_SDRAM_CommandTypeDef* Command)
{
	__IO uint32_t tmpmrd = 0;

	/* Configure a clock configuration enable command */
	Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;	// 开启SDRAM时钟
	Command->CommandTarget = FMC_COMMAND_TARGET_BANK; 	// 选择要控制的区域
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = 0;

	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	// 发送控制指令
	HAL_Delay(1);		// 延时等待

	/* Configure a PALL (precharge all) command */
	Command->CommandMode = FMC_SDRAM_CMD_PALL;		// 预充电命令
	Command->CommandTarget = FMC_COMMAND_TARGET_BANK;	// 选择要控制的区域
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = 0;

	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);  // 发送控制指令

	/* Configure a Auto-Refresh command */
	Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;	// 使用自动刷新
	Command->CommandTarget = FMC_COMMAND_TARGET_BANK;          // 选择要控制的区域
	Command->AutoRefreshNumber = 8;                                // 自动刷新次数
	Command->ModeRegisterDefinition = 0;

	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	// 发送控制指令

	/* Program the external memory mode register */
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2 |
		SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
		SDRAM_MODEREG_CAS_LATENCY_3 |
		SDRAM_MODEREG_OPERATING_MODE_STANDARD |
		SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;	// 加载模式寄存器命令
	Command->CommandTarget = FMC_COMMAND_TARGET_BANK;	// 选择要控制的区域
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = tmpmrd;

	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	// 发送控制指令

	HAL_SDRAM_ProgramRefreshRate(hsdram, 918);  // 配置刷新率

}

uint8_t SDRAM_Test(void)
{
	uint32_t i = 0;			// 计数变量
	uint16_t ReadData = 0; 	// 读取到的数据
	uint8_t  ReadData_8b;

	uint32_t ExecutionTime_Begin;		// 开始时间
	uint32_t ExecutionTime_End;		// 结束时间
	uint32_t ExecutionTime;				// 执行时间
	float    ExecutionSpeed;			// 执行速度

	printf("\r\n*****************************************************************************************************\r\n");
	printf("\r\n进行速度测试>>>\r\n");

// 写入 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms

	for (i = 0; i < SDRAM_Size/2; i++)
	{
 		*(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*i) = (uint16_t)i;		// 写入数据
	}
	ExecutionTime_End		= HAL_GetTick();											// 获取 systick 当前时间，单位ms
	ExecutionTime  = ExecutionTime_End - ExecutionTime_Begin; 				// 计算擦除时间，单位ms
	ExecutionSpeed = (float)SDRAM_Size /1024/1024 /ExecutionTime*1000 ; 	// 计算速度，单位 MB/S

	printf("\r\n以16位数据宽度写入数据，大小：%d MB，耗时: %lu ms, 写入速度：%.2f MB/s\r\n",SDRAM_Size/1024/1024,ExecutionTime,ExecutionSpeed);

// 读取	>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ExecutionTime_Begin 	= HAL_GetTick();	// 获取 systick 当前时间，单位ms

	for(i = 0; i < SDRAM_Size/2;i++ )
	{
		ReadData = *(__IO uint16_t*)(SDRAM_BANK_ADDR + 2 * i );  // 从SDRAM读出数据
	}
	ExecutionTime_End		= HAL_GetTick();											// 获取 systick 当前时间，单位ms
	ExecutionTime  = ExecutionTime_End - ExecutionTime_Begin; 				// 计算擦除时间，单位ms
	ExecutionSpeed = (float)SDRAM_Size /1024/1024 /ExecutionTime*1000 ; 	// 计算速度，单位 MB/S

	printf("\r\n读取数据完毕，大小：%d MB，耗时: %lu ms, 读取速度：%.2f MB/s\r\n",SDRAM_Size/1024/1024,ExecutionTime,ExecutionSpeed);

// 数据校验 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	printf("\r\n*****************************************************************************************************\r\n");
	printf("\r\n进行数据校验>>>\r\n");

	for(i = 0; i < SDRAM_Size/2;i++ )
	{
		ReadData = *(__IO uint16_t*)(SDRAM_BANK_ADDR + 2 * i );  // 从SDRAM读出数据
		if( ReadData != (uint16_t)i )      //检测数据，若不相等，跳出函数,返回检测失败结果。
		{
			printf("\r\nSDRAM测试失败！！\r\n");
			return ERROR;	 // 返回失败标志
		}
	}

	printf("\r\n16位数据宽度读写通过，以8位数据宽度写入数据\r\n");
	for (i = 0; i < 255; i++)
	{
 		*(__IO uint8_t*) (SDRAM_BANK_ADDR + i) =  (uint8_t)i;
	}
	printf("写入完毕，读取数据并比较...\r\n");
	for (i = 0; i < 255; i++)
	{
		ReadData_8b = *(__IO uint8_t*) (SDRAM_BANK_ADDR + i);
		if( ReadData_8b != (uint8_t)i )      //检测数据，若不相等，跳出函数,返回检测失败结果。
		{
			printf("8位数据宽度读写测试失败！！\r\n");
			printf("请检查NBL0和NBL1的连接\r\n");
			return ERROR;	 // 返回失败标志
		}
	}
	printf("8位数据宽度读写通过\r\n");
	printf("SDRAM读写测试通过，系统正常\r\n");
	return SUCCESS;	 // 返回成功标志
}
/* FMC initialization function */
void MX_FMC_Init(void)
{
  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 3;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */
  SDRAM_Initialization_Sequence(&hsdram1,&command);//配置SDRAM
  /* USER CODE END FMC_Init 2 */
}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void){
  /* USER CODE BEGIN FMC_MspInit 0 */

  /* USER CODE END FMC_MspInit 0 */
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (FMC_Initialized) {
    return;
  }
  FMC_Initialized = 1;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FMC;
    PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_ENABLE();

  /** FMC GPIO Configuration
  PF0   ------> FMC_A0
  PF1   ------> FMC_A1
  PF2   ------> FMC_A2
  PF3   ------> FMC_A3
  PF4   ------> FMC_A4
  PF5   ------> FMC_A5
  PH2   ------> FMC_SDCKE0
  PH3   ------> FMC_SDNE0
  PH5   ------> FMC_SDNWE
  PF11   ------> FMC_SDNRAS
  PF12   ------> FMC_A6
  PF13   ------> FMC_A7
  PF14   ------> FMC_A8
  PF15   ------> FMC_A9
  PG0   ------> FMC_A10
  PG1   ------> FMC_A11
  PE7   ------> FMC_D4
  PE8   ------> FMC_D5
  PE9   ------> FMC_D6
  PE10   ------> FMC_D7
  PE11   ------> FMC_D8
  PE12   ------> FMC_D9
  PE13   ------> FMC_D10
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PD10   ------> FMC_D15
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PG2   ------> FMC_A12
  PG4   ------> FMC_BA0
  PG5   ------> FMC_BA1
  PG8   ------> FMC_SDCLK
  PD0   ------> FMC_D2
  PD1   ------> FMC_D3
  PG15   ------> FMC_SDNCAS
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  */
  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN FMC_MspInit 1 */

  /* USER CODE END FMC_MspInit 1 */
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* sdramHandle){
  /* USER CODE BEGIN SDRAM_MspInit 0 */

  /* USER CODE END SDRAM_MspInit 0 */
  HAL_FMC_MspInit();
  /* USER CODE BEGIN SDRAM_MspInit 1 */

  /* USER CODE END SDRAM_MspInit 1 */
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void){
  /* USER CODE BEGIN FMC_MspDeInit 0 */

  /* USER CODE END FMC_MspDeInit 0 */
  if (FMC_DeInitialized) {
    return;
  }
  FMC_DeInitialized = 1;
  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_DISABLE();

  /** FMC GPIO Configuration
  PF0   ------> FMC_A0
  PF1   ------> FMC_A1
  PF2   ------> FMC_A2
  PF3   ------> FMC_A3
  PF4   ------> FMC_A4
  PF5   ------> FMC_A5
  PH2   ------> FMC_SDCKE0
  PH3   ------> FMC_SDNE0
  PH5   ------> FMC_SDNWE
  PF11   ------> FMC_SDNRAS
  PF12   ------> FMC_A6
  PF13   ------> FMC_A7
  PF14   ------> FMC_A8
  PF15   ------> FMC_A9
  PG0   ------> FMC_A10
  PG1   ------> FMC_A11
  PE7   ------> FMC_D4
  PE8   ------> FMC_D5
  PE9   ------> FMC_D6
  PE10   ------> FMC_D7
  PE11   ------> FMC_D8
  PE12   ------> FMC_D9
  PE13   ------> FMC_D10
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PD10   ------> FMC_D15
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PG2   ------> FMC_A12
  PG4   ------> FMC_BA0
  PG5   ------> FMC_BA1
  PG8   ------> FMC_SDCLK
  PD0   ------> FMC_D2
  PD1   ------> FMC_D3
  PG15   ------> FMC_SDNCAS
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  */

  HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

  HAL_GPIO_DeInit(GPIOH, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5);

  HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15);

  HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);

  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);

  /* USER CODE BEGIN FMC_MspDeInit 1 */

  /* USER CODE END FMC_MspDeInit 1 */
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* sdramHandle){
  /* USER CODE BEGIN SDRAM_MspDeInit 0 */

  /* USER CODE END SDRAM_MspDeInit 0 */
  HAL_FMC_MspDeInit();
  /* USER CODE BEGIN SDRAM_MspDeInit 1 */

  /* USER CODE END SDRAM_MspDeInit 1 */
}
/**
  * @}
  */

/**
  * @}
  */
