/*
 * FSM_Settings.c
 *
 *  Created on: Nov 5, 2024
 *      Author: dangk
 */

#include "FSM_Settings.h"


void FSM_Normal_Mode()
{
	  init_Led();
	  update_led = SCH_Add_Task(update_Led_Traffic, 0, 1000);
	  scan_led_1 = SCH_Add_Task(scan_Led_1, 0, 1000);
	  scan_led_2 = SCH_Add_Task(scan_Led_2, 500, 1000);
}

void FSM_Settings_run()
{
	switch (modeFSM) {
		case NORMAL_MODE:
			// SCH_Add_Task(FSM_Normal_Mode, 0, 0);
			if (isSelectMode() == 1)
			{
				HAL_GPIO_WritePin(GPIOA, LED_RED_1_Pin|LED_YELLOW_1_Pin|LED_GREEN_1_Pin|LED_RED_2_Pin
				                          |LED_YELLOW_2_Pin|LED_GREEN_2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, RESET);
				HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, RESET);
				SCH_Delete_Task(update_led);
				SCH_Delete_Task(scan_led_1);
				SCH_Delete_Task(scan_led_2);
				modeFSM = MODIFY_RED;
			}
			break;
		case MODIFY_RED:
			display_Led7_Segment(modifyRed);
			HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, RESET);
			if (isModifyMode() == 1)
			{
				modifyRed = (modifyRed + 1) % 100;
			}
			if (isSetMode() == 1)
			{
				HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
				HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
				durationRed = modifyRed * 1000;
				modeFSM = MODIFY_YELLOW;
			}
			if (isSelectMode() == 1)
			{
				HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
				HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
				modeFSM = MODIFY_YELLOW;
			}
			break;
		case MODIFY_YELLOW:
			display_Led7_Segment(modifyYellow);
			HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, RESET);
			if (isModifyMode() == 1)
			{
				if (modifyGreen >= 1)
					modifyYellow = (modifyYellow + 1) % 100;
			}
			if (isSetMode() == 1)
			{
				HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
				HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
				durationYellow = modifyYellow * 1000;
				modifyGreen = modifyRed - modifyYellow;
				durationGreen = modifyGreen * 1000;
				modeFSM = MODIFY_GREEN;
			}
			if (isSelectMode() == 1)
			{
				HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
				HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
				modeFSM = MODIFY_GREEN;
			}
			break;
		case MODIFY_GREEN:
			display_Led7_Segment(modifyGreen);
			HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, RESET);
			if (isModifyMode() == 1)
			{
				if (modifyYellow >= 1)
					modifyGreen = (modifyGreen + 1) % 100;
			}
			if (isSetMode() == 1)
			{
				durationGreen = modifyGreen * 1000;
				modifyYellow = modifyRed - modifyGreen;
				durationYellow = modifyYellow * 1000;
				HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
				HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
				SCH_Add_Task(FSM_Normal_Mode, 0, 0);
				modeFSM = NORMAL_MODE;
			}
			if (isSelectMode() == 1)
			{
				HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
				HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
				SCH_Add_Task(FSM_Normal_Mode, 0, 0);
				modeFSM = NORMAL_MODE;
			}
			break;
		default:
			break;
	}
}
