#include "stdafx.h"
#include "MoveBalans.h"
#include <cmath>
#include <math.h>

#define PI 3.14159265  

double MoveBalans::CalculationlengthSide(const double onePoint, 
	                                     const double twoPoint) {
	if (onePoint <  0 && twoPoint < 0 ) {
		return  (double)abs(onePoint) - (double)abs(twoPoint);
	}
	else if(onePoint <  0 || twoPoint < 0) {
		return (double)abs(onePoint ) + (double)abs(twoPoint);
	}
	else {
		return abs((double)(onePoint) - (double)(twoPoint));
	}
}
// вынести pairindex 
void MoveBalans::calcCoordinat(const std::pair<int, int> pairIndex,
	double& coord1, double& coord2) {
	// нужно считать смищение
	switch (counter)
	{
	case(1):coord1 = radius * cos(angleStart * PI / 180) + couplCoordinats.first;
		    coord2 = radius * sin(angleStart * PI / 180) + couplCoordinats.second;
			break;
	case(2):coord1 = radius * cos(angleStart * PI / 180) + couplCoordinats.first;
		    coord2 = couplCoordinats.second - radius * sin(angleStart * PI / 180);
			break;
	case(3):coord1 = couplCoordinats.first - radius * cos(angleStart * PI / 180);
		    coord2 = couplCoordinats.second - radius * sin(angleStart * PI / 180);
      break;
	case(4):coord1 = couplCoordinats.first - radius * cos(angleStart * PI / 180);
		    coord2 = couplCoordinats.second + radius * sin(angleStart * PI / 180);

	default:
		break;
	}
}
	
// используется один раз

void  MoveBalans::calcFirstCoordinat() {
	// первый подсчет по стандарту
	lastAngleStart = angleStart;
	subjectCoordinats.first = radius * cos(angleStart * PI / 180) + couplCoordinats.first;
	subjectCoordinats.second = radius * sin(angleStart * PI / 180) + couplCoordinats.second;

	/*calcCoordinat(vecIndex.at(counter - 1), subjectCoordinats.first,
		subjectCoordinats.second);*/
}
double  MoveBalans::calculationAngleGravity(const double leghtX, 
	                                        const double leghtY,
	                                        const size_t counter) {
	// поэксперементировать
	if ((counter == 1 && narrative)  || (counter == 4 )) {
		
		return angleStart - atan((abs(leghtY) - powerGravity) / abs(leghtX)) * 180 / PI;
	}
	
	else {
		return(atan((leghtY + powerGravity) / (leghtX)) * 180 / PI) - 
			  (atan((leghtY) / (leghtX)) * 180 / PI);
	}
}



template <typename T>
T angleStartChange(const T value) {
	return value;
}
template <typename _First, typename... _MyTypes>
auto angleStartChange(const _First first, _MyTypes ... arg) {
	return first + angleStartChange(arg...);
}
 void MoveBalans::transition() {
	if (angleStart < 0 || angleStart > 90) {

		if ((lastAngleStart < angleStart)  && ( counter == 4 || counter == 1) ) {
			if (counter == 4) {
				narrative = angleSpeed > 0 ? false : true;
			}
			else if (counter == 1) {
				narrative = angleGravity > 0? true : false;
			}
			
			angleSpeed = 0;
			plusSpeed = 0;
			angleGravity = 0;
			speed = 0;
			counter = counter == 1 ? counter = 4 : counter = 1;
			
		}
		else if (narrative && counter == 4) {
			counter = 1;
			
		}
		else if (!(narrative) && counter == 1) {
			counter = 4;
			
			angleGravity = 0;
			
		}
		else if (narrative) {
			++counter;
		}
		else { --counter; }
	
	
		angleStart = abs(abs(90 - angleStart) - 90);
	
	}
}
//_________________________________________________________________________________________
void MoveBalans::countingDataToMove(const short index) {
	angleGravity = calculationAngleGravity(CalculationlengthSide(subjectCoordinats.first,
		                                                           couplCoordinats.first),
		                                   CalculationlengthSide(subjectCoordinats.second,
			                                                       couplCoordinats.second),
		                                                                          counter); 
	angleSpeed = atan(speed / radius);
	plusSpeed = (2 * radius * sin(angleSpeed / 2 * PI / 180)) +
		        (2 * radius * sin(angleGravity / 2 * PI / 180));

	if ((narrative  && (counter == 1 || counter == 2))||
	  (!(narrative) && (counter == 3 || counter == 4))) {
		// дабовлять ускорение к скорости
		// и непосредствеенно саму скорость
		// index либо 1 либо -1
	    //angleStart = angleStart - (angleStartChange(angleSpeed,angleGravity) * index);
		//narrative = angleStart < angleStart - (angleStartChange(angleSpeed, angleGravity) * index)? false:true;
		lastAngleStart = angleStart;
		 double a = (angleStartChange(angleSpeed, angleGravity) * index);

		 angleStart = angleStart - a;
		

		speed += plusSpeed;
		// нужен свич с индексами
		
		calcCoordinat(vecIndex.at(counter - 1), subjectCoordinats.first,
			subjectCoordinats.second);
		// переходи вcледующюю четверть
		
		transition();                
	}
	// просмотреть обратное движение 
	else {
		// расмотреть точку остоновки
		angleSpeed -= angleGravity;
		angleStart = angleStart - (angleStartChange(angleSpeed) * index * -1);
		
		if (angleSpeed <= 0) {
			narrative = narrative ? false : true;
			speed = 0;
		}
		else {
			calcCoordinat(vecIndex.at(counter - 1), subjectCoordinats.first,
				subjectCoordinats.second);
			speed -= plusSpeed;
			transition();
		}
	}
	// меняем координаты
}
//_______________________________________________________________
void MoveBalans::calculationAngleBag() {
	/// переделать условие
	if (counter == 1 || counter == 4) {
		countingDataToMove(1);
	}
	//если мы во воторой четверти
	else if (counter == 2|| counter == 3) {
		countingDataToMove(-1);
	}
	
}