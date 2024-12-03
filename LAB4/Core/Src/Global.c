/*
 * Global.c
 *
 *  Created on: Nov 5, 2024
 *      Author: dangk
 */

#include "Global.h"

uint8_t scan_led_1, scan_led_2, update_led;

int modeFSM = NORMAL_MODE;

int durationRed = 5000;
int durationGreen = 3000;
int durationYellow = 2000;

int modifyRed = 0;
int modifyYellow = 0;
int modifyGreen = 0;

int ledBuffer[2];
int green1, red1, yellow1;
int green2, red2, yellow2;

void init_Led()
{
	red1 = red2 = modifyRed = durationRed / 1000;
	yellow1 = yellow2 = modifyYellow = durationYellow / 1000;
	green1 = green2 = modifyGreen = durationGreen / 1000;
	ledBuffer[0] = durationGreen / 1000;
	ledBuffer[1] = durationRed / 1000;
}

void update_Led_Traffic()
{
	if (green1 > 0)
	{
		ledBuffer[0] = green1--;
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, RESET);
	}

	else if (yellow1 > 0)
	{
		ledBuffer[0] = yellow1--;
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
	}
	else if (red1 > 0)
	{
		ledBuffer[0] = red1--;
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
	}
	else
	{
		red1 = durationRed / 1000;
		yellow1 = durationYellow / 1000;
		green1 = durationGreen / 1000;
		ledBuffer[0] = green1--;
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, RESET);
	}

	if (red2 > 0)
	{
		ledBuffer[1] = red2--;
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
	}

	else if (green2 > 0)
	{
		ledBuffer[1] = green2--;
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, RESET);
	}
	else if (yellow2 > 0)
	{
		ledBuffer[1] = yellow2--;
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
	}
	else
	{
		red2 = durationRed / 1000;
		yellow2 = durationYellow / 1000;
		green2 = durationGreen / 1000;
		ledBuffer[1] = red2--;
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
	}
}

void display_Led_Buffer(int index)
{
	display_Led7_Segment(ledBuffer[index % 2]);
}
void scan_Led_1()
{
	display_Led_Buffer(0);
	HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, RESET);
	HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, SET);
}
void scan_Led_2()
{
	display_Led_Buffer(1);
	HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, SET);
	HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, RESET);
}
