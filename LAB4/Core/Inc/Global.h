/*
 * global.h
 *
 *  Created on: Nov 5, 2024
 *      Author: dangk
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "Button.h"
#include "Led7-Segment.h"

#define NORMAL_MODE 0
#define MODIFY_RED 1
#define MODIFY_YELLOW 2
#define MODIFY_GREEN 3

extern int modeFSM;

extern int durationRed;
extern int durationGreen;
extern int durationYellow;

extern int modifyRed;
extern int modifyYellow;
extern int modifyGreen;

extern int red1, green1, yellow1;
extern int red2, green2, yellow2;
extern uint8_t scan_led_1, scan_led_2, update_led;

void init_Led();
void update_Led_Traffic();
void scan_Led_1();
void scan_Led_2();
#endif /* INC_GLOBAL_H_ */
