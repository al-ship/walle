/*
 * Moving.h
 *
 *  Created on: 30.07.2011
 *      Author: shipulya
 */
#ifndef MOVING_H_
#define MOVING_H_

class MovVect
{
private:

// управление двигателями
   //двигатель левый вперёд
   void Move_lf();
   //двиг. левый стоп
   void Stop_l();
   //двиг левый назад
   void Move_lr();
   //двигатель правый вперёд
   void Move_rf();
   //двиг. правый стоп
   void Stop_r();
   //двигат. правый назад
   void Move_rr();
// управление движением
public:
   MovVect();
   //вперед
   void moveForward();
   //назад
   void moveBack();
   //разворот вправо
   void spinRihgt();
   //разворот влево
   void spinLeft();
   //поворот направо
   void turnRight();
   //поворот налево
   void turnLeft();
   //поворот направо задний
   void turnRight_r();
   //поворот налево задний
   void turnLeft_r();
   void stop();
};
#endif /* MOVING_H_ */
