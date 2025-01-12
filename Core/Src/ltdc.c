/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
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
#include "ltdc.h"

/* USER CODE BEGIN 0 */
#include <lcd_rgb.h>
#include <stm32h7xx_hal.h>
#include <stm32h7xx_hal_ltdc.h>
/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
/*void MX_LTDC_Init(void)
{

   USER CODE BEGIN LTDC_Init 0

   USER CODE END LTDC_Init 0

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

   USER CODE BEGIN LTDC_Init 1

   USER CODE END LTDC_Init 1
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 0;
  hltdc.Init.VerticalSync = 0;
  hltdc.Init.AccumulatedHBP = 80;
  hltdc.Init.AccumulatedVBP = 40;
  hltdc.Init.AccumulatedActiveW = 880;
  hltdc.Init.AccumulatedActiveH = 520;
  hltdc.Init.TotalWidth = 1080;
  hltdc.Init.TotalHeigh = 542;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 800;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 480;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xC0000000;
  pLayerCfg.ImageWidth = 800;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
   USER CODE BEGIN LTDC_Init 2

   USER CODE END LTDC_Init 2

}*/

/*************************************************************************************************
*	函 数 名:	MX_LTDC_Init
*	入口参数:	无
*	返 回 值:	无
*	函数功能:	初始化LTDC引脚的IO口、全局参数、层设置等
*	说    明:	无
*************************************************************************************************/

void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};		          // layer0 相关参数

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;                              // LTCD句柄配置
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;         // 低电平有效
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;	      // 低电平有效
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;	      // 低电平有效，要注意的是，很多面板都是高电平有效，但是750需要设置成低电平才能正常显示
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;	      // 正常时钟
  /*-------------以下参数根据屏幕设置---------------*/
//  hltdc.Init.HorizontalSync = 0;
//  hltdc.Init.VerticalSync = 0;
//  hltdc.Init.AccumulatedHBP = 80;
//  hltdc.Init.AccumulatedVBP = 20;
//  hltdc.Init.AccumulatedActiveW = 880;
//  hltdc.Init.AccumulatedActiveH = 500;
//  hltdc.Init.TotalWidth = 1080;
//  hltdc.Init.TotalHeigh = 522;
  hltdc.Init.HorizontalSync 	= HSW - 1;
  hltdc.Init.VerticalSync 		= VSW	-1 ;
  hltdc.Init.AccumulatedHBP		= HBP + HSW -1;
  hltdc.Init.AccumulatedVBP 	= VBP + VSW -1;
  hltdc.Init.AccumulatedActiveW = LCD_Width  + HSW + HBP -1;
  hltdc.Init.AccumulatedActiveH = LCD_Height + VSW + VBP -1;
  hltdc.Init.TotalWidth 		= LCD_Width  + HSW + HBP + HFP - 1;
  hltdc.Init.TotalHeigh 		= LCD_Height + VSW + VBP + VFP - 1;
/*-----------------背景色初始化-------------------*/
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  /*--------------LTDC参数初始化-----------------*/
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  /*---------------------------------- layer0 显示配置 --------------------------------*/
  pLayerCfg.WindowX0 		= 0;							 // 水平起点
  pLayerCfg.WindowX1 		= LCD_Width;					 // 水平终点
  pLayerCfg.WindowY0 		= 0;							 // 垂直起点
  pLayerCfg.WindowY1 		= LCD_Height;					 // 垂直终点
  pLayerCfg.ImageWidth 		= LCD_Width;                     // 显示区域宽度
  pLayerCfg.ImageHeight 	= LCD_Height;                    // 显示区域高度
  pLayerCfg.PixelFormat 	= ColorMode_0;					 // 颜色格式

//	配置 layer0 的恒定透明度，最终写入 LTDC_LxCACR 寄存器
//	需要注意的是，这个参数是直接配置整个 layer0 的透明度，这里设置为255即不透明
  pLayerCfg.Alpha = 255;//layer0恒定透明度

// 设置 layer0 的层混合系数，最终写入 LTDC_LxBFCR 寄存器
// 该参数用于设置 layer0 和 底层背景 之间的颜色混合系数，计算公式为 ：
// 混合后的颜色 =  BF1 * layer0的颜色 + BF2 * 底层背景的颜色
// 如果 layer0 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;		// 混合系数1
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;		// 混合系数2

  pLayerCfg.FBStartAdress = LCD_MemoryAdd;                	// 显存地址
// 配置 layer0 的初始默认颜色，包括A,R,G,B 的值 ，最终写入 LTDC_LxDCCR 寄存器
  pLayerCfg.Alpha0          = 0;//layer0初始颜色，A
  pLayerCfg.Backcolor.Red   = 0;//layer0初始颜色，R
  pLayerCfg.Backcolor.Green = 0;//layer0初始颜色，G
  pLayerCfg.Backcolor.Blue  = 0;//layer0初始颜色，B

  /*-------------layer0参数初始化----------------*/
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
/*-------------判断是否使用24位或者32位色----------------*/
#if ( ( ColorMode_0 == LTDC_PIXEL_FORMAT_RGB888 )||( ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB8888 ) ) // 判断是否使用24位或者32位色

// 因为750每个通道的低位都是采用伪随机抖动输出，如果不开启颜色抖动，则无法正常显示24位或者32位色

	HAL_LTDC_EnableDither(&hltdc); // 开启颜色抖动

#endif

/*---------------------------------- layer1 显示配置 --------------------------------*/

#if ( LCD_NUM_LAYERS == 2 )	//如果定义了双层

  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  pLayerCfg1.WindowX0    = 0;                       // 水平起点
  pLayerCfg1.WindowX1    = LCD_Width;               // 水平终点
  pLayerCfg1.WindowY0    = 0;                       // 垂直起点
  pLayerCfg1.WindowY1    = LCD_Height;              // 垂直终点
  pLayerCfg1.ImageWidth  = LCD_Width;               // 显示区域宽度
  pLayerCfg1.ImageHeight = LCD_Height;              // 显示区域高度
  pLayerCfg1.PixelFormat = ColorMode_1;             // 颜色格式，layer1 应配置为带有透明色的格式，例如ARGB8888或ARGB1555

//   配置 layer1 的恒定透明度，最终写入 LTDC_LxCACR 寄存器
//   需要注意的是，这个参数是直接配置整个 layer1 的透明度，这里设置为255即不透明
  pLayerCfg1.Alpha = 255;//layer1恒定透明度
//   如果 layer1 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
//   更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;// 混合系数1
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;// 混合系数2

  pLayerCfg1.FBStartAdress = LCD_MemoryAdd + LCD_MemoryAdd_OFFSET;

  pLayerCfg1.Alpha0           = 0;//layer1初始颜色，A
  pLayerCfg1.Backcolor.Red    = 0;//layer1初始颜色，R
  pLayerCfg1.Backcolor.Green  = 0;//layer1初始颜色，G
  pLayerCfg1.Backcolor.Blue   = 0;//layer1初始颜色，B

  /*-------------layer1参数初始化----------------*/
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }
#if ( ( ColorMode_1 == LTDC_PIXEL_FORMAT_RGB888 )||( ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB8888 ) ) // 判断是否使用24位或者32位色

	// 因为750每个通道的低位都是采用伪随机抖动输出，如果不开启颜色抖动，则无法正常显示24位或者32位色

		HAL_LTDC_EnableDither(&hltdc); // 开启颜色抖动

	#endif

#endif
  /* USER CODE BEGIN LTDC_Init 2 */
//	HAL_LTDC_ProgramLineEvent(&hltdc, 0);	    		// 设置行中断，第0行
//	HAL_NVIC_SetPriority(LTDC_IRQn, 15, 0);		    	// 设置优先级
//	HAL_NVIC_EnableIRQ(LTDC_IRQn);						// 使能中断
  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
//    PeriphClkInitStruct.PLL3.PLL3M = 25;
//    PeriphClkInitStruct.PLL3.PLL3N = 330;
//    PeriphClkInitStruct.PLL3.PLL3P = 2;
//    PeriphClkInitStruct.PLL3.PLL3Q = 2;
//    PeriphClkInitStruct.PLL3.PLL3R = 10;
#if LCD_RCC_25MHZ
        PeriphClkInitStruct.PLL3.PLL3M = 1;
        PeriphClkInitStruct.PLL3.PLL3N = 6;
        PeriphClkInitStruct.PLL3.PLL3P = 2;
        PeriphClkInitStruct.PLL3.PLL3Q = 2;
        PeriphClkInitStruct.PLL3.PLL3R = 6;
#endif
#if LCD_RCC_40MHZ
        PeriphClkInitStruct.PLL3.PLL3M = 1;
        PeriphClkInitStruct.PLL3.PLL3N = 8;
        PeriphClkInitStruct.PLL3.PLL3P = 2;
        PeriphClkInitStruct.PLL3.PLL3Q = 2;
        PeriphClkInitStruct.PLL3.PLL3R = 5;
#endif
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_0;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PE5     ------> LTDC_G0
    PE6     ------> LTDC_G1
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PA2     ------> LTDC_R1
    PH8     ------> LTDC_R2
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PA8     ------> LTDC_B3
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PD6     ------> LTDC_B2
    PG12     ------> LTDC_B1
    PG13     ------> LTDC_R0
    PG14     ------> LTDC_B0
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_LTDC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* LTDC interrupt Init */
	HAL_NVIC_SetPriority(LTDC_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(LTDC_IRQn);
	HAL_NVIC_SetPriority(LTDC_ER_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(LTDC_ER_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PE5     ------> LTDC_G0
    PE6     ------> LTDC_G1
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PA2     ------> LTDC_R1
    PH8     ------> LTDC_R2
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PA8     ------> LTDC_B3
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PD6     ------> LTDC_B2
    PG12     ------> LTDC_B1
    PG13     ------> LTDC_R0
    PG14     ------> LTDC_B0
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_5|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_6);

    HAL_NVIC_DisableIRQ(LTDC_IRQn);
    HAL_NVIC_DisableIRQ(LTDC_ER_IRQn);

  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
