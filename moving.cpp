/*
 * Moving.cpp
 *
 *  Created on: 15.07.2011
 *      Author: shipulya
 */
#include "moving.h"
#include <avr/io.h>
#include "defines.h"


	MovVect::MovVect()
	{
		//конфигурируем выходы на двигатель
		ENG_L_1_DDR |= _BV(ENG_L_1_PIN);
		ENG_L_2_DDR |= _BV(ENG_L_2_PIN);
		ENG_R_1_DDR |= _BV(ENG_R_1_PIN);
		ENG_R_2_DDR |= _BV(ENG_R_2_PIN);
	}


// управление двигателями
   //левый - вперёд
   void MovVect::Move_lf()
   {
	   ENG_L_1_PORT |= _BV(ENG_L_1_PIN);
	   ENG_L_2_PORT &= ~_BV(ENG_L_2_PIN);
   }
   //двиг. левый стоп
   void MovVect::Stop_l()
   {
	   ENG_L_1_PORT &= ~_BV(ENG_L_1_PIN);
	   ENG_L_2_PORT &= ~_BV(ENG_L_2_PIN);
   }
   //двиг левый назад
   void MovVect::Move_lr()
   {
	   ENG_L_1_PORT &= ~_BV(ENG_L_1_PIN);
	   ENG_L_2_PORT |= _BV(ENG_L_2_PIN);
   }
   //двигатель правый вперёд
   void MovVect::Move_rf()
   {
	   ENG_R_1_PORT |= _BV(ENG_R_1_PIN);
	   ENG_R_2_PORT &= ~_BV(ENG_R_2_PIN);
   }
   //двиг. правый стоп
   void MovVect::Stop_r()
   {
	   ENG_R_1_PORT &= ~_BV(ENG_R_1_PIN);
	   ENG_R_2_PORT &= ~_BV(ENG_R_2_PIN);
   }
   //двигат. правый назад
   void MovVect::Move_rr()
   {
	   ENG_R_1_PORT &= ~_BV(ENG_R_1_PIN);
	   ENG_R_2_PORT |= _BV(ENG_R_2_PIN);
   }
// управление движением

   //вперед
   void MovVect::moveForward()
   {
	   Move_rf();
	   Move_lf();
   }
   //назад
   void MovVect::moveBack()
   {
	   Move_rr();
	   Move_lr();
   }
   //разворот вправо
   void MovVect::spinRihgt()
   {
	   Move_rr();
	   Move_lf();
   }
   //разворот влево
   void MovVect::spinLeft()
   {
	   Move_rf();
	   Move_lr();
   }
   //поворот направо
   void MovVect::turnRight()
   {
	   Stop_r();
	   Move_lf();
   }
   //поворот налево
   void MovVect::turnLeft()
   {
	   Stop_l();
	   Move_rf();
   }
   //поворот направо задний
   void MovVect::turnRight_r()
   {
	   Stop_r();
	   Move_lr();
   }
   //поворот налево задний
   void MovVect::turnLeft_r()
   {
	   Stop_l();
	   Move_rr();
   }
   void MovVect::stop()
   {
	   Stop_l();
	   Stop_r();
   }
