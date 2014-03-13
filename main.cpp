/*
 * main.cpp
 *
 *  Created on: 15.12.2012
 *      Author: shipulya
 */

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include "defines.h"
#include "moving.h"

static MovVect MV;

static void delay_us(int s)
{
	while(s > 0)
	{
		_delay_us(50); //50 будет точнее?
		s = s - 50;
	}
}

// p - угол (0-180)
static void turnHead(int p)
{
	//Mystery sd90 servo:
	//max = 1800+530;
	//min = 530;
	for (int i = 0; i < 50; i++)
	{
		HEAD_PORT |= _BV(HEAD_PIN);
		delay_us(530 + p*10);
		HEAD_PORT &= ~_BV(HEAD_PIN);
		_delay_ms(15);
	}
}

static int getNextHeadTurn(int current)
{
	int result = 90;
	if(current == 0)
		result = 135;
	else if(current == 180)
		result = -1;
	else if(current == 135)
		result = 180;
	else
		result = current - 45;
	//нормализуем
	if (result < 0)
		result = 0;
	if(result > 180)
		result = 180;
	return result;
}

//дистанция до объекта в см
static int getDistance()
{
	int time = 0;
	//импульс на триггер 13 мкс
	AYES_TRIG_PORT |= _BV(AYES_TRIG_PIN);
	_delay_us(10);
	AYES_TRIG_PORT &= ~_BV(AYES_TRIG_PIN);
	//ждем импульс на сенсоре
	loop_until_bit_is_set(AYES_SENS_IN, AYES_SENS_PIN);
	//считаем длительность импульса на сенсоре
	while(bit_is_set(AYES_SENS_IN, AYES_SENS_PIN) && time < 1000)
	{
		_delay_us(9);
		time++;
	}
	return (time * 10) / 58;
}

// узнаём свободное направление для движения (угол 0-180)
static int getDirection()
{
	int head = 90;
	int dist = 0;
	do
	{
		turnHead(head);
		dist = getDistance();
		if(dist < MIN_DISTANCE)
			head = getNextHeadTurn(head);
	}while(dist < MIN_DISTANCE && head >= 0);
	turnHead(90); //голова прямо
	if(dist < MIN_DISTANCE) // нет свободного пути, разворачиваемся
		return 180;
	else
		return head - 90;
}

//поворот корпуса на dir градусов
static void turn(int dir)
{
	if(dir == 180)
	{
		//разворот
		MV.turnLeft();
		_delay_ms(MIN_MOVE_TIME * 4);
	}
	else if(dir == 45)
	{//поворот влево на 45
		MV.turnLeft();
		_delay_ms(MIN_MOVE_TIME);
	}
	else if(dir == 90)
	{//поворот влево на 90
		MV.turnLeft();
		_delay_ms(MIN_MOVE_TIME * 2);
	}
	else if(dir == -45)
	{
		MV.turnRight();
		_delay_ms(MIN_MOVE_TIME);
	}
	else if(dir == -90)
	{
		MV.turnRight();
		_delay_ms(MIN_MOVE_TIME * 2);
	}
	else if(dir == -180)
	{
		MV.turnRight_r();
		_delay_ms(MIN_MOVE_TIME * 4);
	}
	if (dir != 0)//если поворачивались, остановим моторы
		MV.stop();
}

static void init()
{
	//пины
	HEAD_DDR |= _BV(HEAD_PIN); //выход сервы головы
	AYES_SENS_DDR &= ~_BV(AYES_SENS_PIN);//вход сенсора глаз
	AYES_TRIG_DDR |= _BV(AYES_TRIG_PIN);//выход триггера глаз
	LED_DDR |= _BV(LED_PIN);
	ENG_EN_DDR |= _BV(ENG_EN_PIN);

}

// движется ли препятствие
static bool checkMoving()
{
	int check = 0;
	int dist = 0;
	for(int i=0;i<10;i++)
	{
		dist = getDistance();
		_delay_ms(100);
		dist = dist - getDistance();
		if ( dist > 2 || dist < -2)
			check++;
	}
	return check > 3;
}

int main(void)
{
	init();
	//LED_PORT |= _BV(LED_PIN);
	_delay_ms(MIN_MOVE_TIME);
	turnHead(0);
	turnHead(180);
	turnHead(90);
	//вкл двигателя
	ENG_EN_PORT |= _BV(ENG_EN_PIN);
	while(1)
	{// осн цикл
		//смотрим препятствие, поворачиваемся
		int dist = getDistance();
		if(dist < MAX_DISTANCE)
		{//есть препятствие
			MV.stop();
			_delay_ms(MIN_MOVE_TIME);//ждем остановки
			while(checkMoving())
			{//что-то шевелится
				LED_PORT |= _BV(LED_PIN);
				MV.moveBack();
				_delay_ms(MIN_MOVE_TIME * 5);
				MV.stop();
				LED_PORT &= ~_BV(LED_PIN);
				_delay_ms(MIN_MOVE_TIME * 5);
			}
			//ищем свободное направление и поворачиваемся
			turn(getDirection());
		}
		//getDirection();
		//едем прямо
		MV.moveForward();
		_delay_ms(MIN_MOVE_TIME);
	}
}
