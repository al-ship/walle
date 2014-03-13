/*
 * defines.h
 *
 *  Created on: 16.12.2012
 *      Author: shipulya
 */

#ifndef DEFINES_H_
#define DEFINES_H_

//минимальное время движения в млс (влияет на поворот на угол)
#define MIN_MOVE_TIME 600
//минимальное расстояние до препятствия
#define MIN_DISTANCE 20
//максимальное расстояние до препятствия
#define MAX_DISTANCE 25

//серва головы
#define HEAD_DDR DDRB
#define HEAD_PORT PORTB
#define HEAD_PIN PB0

//глаза (HC-SR04)
// триггер
#define AYES_TRIG_DDR DDRD
#define AYES_TRIG_PORT PORTD
#define AYES_TRIG_PIN PD6
// детектор
#define AYES_SENS_DDR DDRD
#define AYES_SENS_IN PIND
#define AYES_SENS_PIN PD7

//Светодиод
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PB5

//двигатели (moving.cpp)
// вкл
#define ENG_EN_PORT PORTB
#define ENG_EN_DDR DDRB
#define ENG_EN_PIN PB1
//правый 1-й вывод
#define ENG_R_1_PORT PORTD
#define ENG_R_1_DDR DDRD
#define ENG_R_1_PIN PD2
//правый 2-й вывод
#define ENG_R_2_PORT PORTD
#define ENG_R_2_DDR DDRD
#define ENG_R_2_PIN PD3
//левый 1-й вывод
#define ENG_L_1_PORT PORTD
#define ENG_L_1_DDR DDRD
#define ENG_L_1_PIN PD4
//левый 2-й вывод
#define ENG_L_2_PORT PORTD
#define ENG_L_2_DDR DDRD
#define ENG_L_2_PIN PD5

#endif /* DEFINES_H_ */
