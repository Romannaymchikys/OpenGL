#include "stdafx.h"
#include "MoveBalans.h"
#include <cmath>
#include <math.h>

#define PI 3.14159265  

// используется один раз
void  MoveBalans::calcFirstCoordinat() {
	calcCoordinat(vecIndex.at(counter - 1), subjectCoordinats.first,
		subjectCoordinats.second);
}


double MoveBalans::CalculationlengthSide(const double onePoint, 
	                                     const double twoPoint) {
	return (double)(abs(onePoint)) - (double)(abs(twoPoint));
}
void  MoveBalans::calcCoordinat(const std::pair<int, int> pairIndex, 
	                            double& coord1, double& coord2) {
	coord1 = radius * cos(angleStart * PI/ 180);
	coord2 = radius * sin(angleStart * PI / 180);
	subjectCoordinats.first  *= pairIndex.first;
	subjectCoordinats.second *= pairIndex.second;
}
double  MoveBalans::calculationAngleGravity(const double leghtX, 
	                                        const double leghtY,
	                                        const size_t counter) {
	if (counter == 1 || counter == 4) {
		return angleStart - atan((leghtY - powerGravity) / leghtX) * 180 / PI;
	}
	else {
		return(atan((leghtY + powerGravity) / (leghtX)) * 180 / PI) - 
			  (atan((leghtY) / (leghtX)) * 180 / PI);
	}
}

void MoveBalans::transition() {
	if (angleStart < 0 || angleStart > 90) {
		subjectCoordinats.first > 0 && subjectCoordinats.second > 0 ? counter = 1 :
		subjectCoordinats.first > 0 && subjectCoordinats.second < 0 ? counter = 2 :
		subjectCoordinats.first < 0 && subjectCoordinats.second < 0 ? counter = 3 : 
		subjectCoordinats.first < 0 && subjectCoordinats.second > 0 ? counter = 4 : 
		narrative ? ++counter : --counter;
		angleStart = abs(abs(90 - angleStart) - 90);
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
		// index либо 1 либо -1
	    angleStart = angleStart - (angleStartChange(angleSpeed,angleGravity) * index);
		speed += plusSpeed;
		calcCoordinat(vecIndex.at(counter - 1), subjectCoordinats.first,
			subjectCoordinats.second);
		// переходим вcледующюю четверть
		transition();
	}
	// просмотреть обратное движение 
	else {
		angleSpeed -= angleGravity;
		angleStart = angleStart - (angleStartChange(angleSpeed) * index * -1);
		// расмотреть точку остоновки
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
	// пользователь сам вводит угол 
	//если мы в перой четверти
	if (subjectCoordinats.first > couplCoordinats.first  &&
		subjectCoordinats.second > couplCoordinats.second) {
		countingDataToMove(1);
	}
	//если мы во воторой четверти
	else if (subjectCoordinats.first > couplCoordinats.first &&
		     subjectCoordinats.second < couplCoordinats.second) {
		countingDataToMove(-1);
	}
	//если мы в третей четверти
	else if (subjectCoordinats.first < couplCoordinats.first &&
		     subjectCoordinats.second < couplCoordinats.second) {
		countingDataToMove(-1);
	}
	//если мы в четвертой четверти
	else if (subjectCoordinats.first < couplCoordinats.first &&
		     subjectCoordinats.second > couplCoordinats.second) {
		countingDataToMove(1);
	}
}