#pragma once
#include <iostream>
#include <math.h>
#include <vector>
class MoveBalans
{
	// coordinats.first = x;
	// coordinats.second = y;
	// изначал угол angleBag_1 = 60;

	// начальна€ координата сцепки
	std::pair<double, double>   couplCoordinats;
	// координата предмета
	std::pair<double, double> subjectCoordinats;
	// начальный угол подени€
	double angleStart;
	// напровление движение ма€тника
	// лево - true 
	// право - false
	bool narrative;
	// радиус
	double radius;
	// четверть в координатной плоскости
	size_t counter;
	// вектор с индэксэми четверти
	std::vector<std::pair<int, int>> vecIndex;
	// сила приц€жени€
	const double powerGravity = 0.001;
	// скорость
	double speed;
	// доп скорость при ускарении
	double plusSpeed;
	// угол скорости
	double angleSpeed;
	// угол ускорение;
	double angleGravity;
	// угол ускорение дл€ колибровки;
	double angleAccel_1;

public:
	// 

	MoveBalans(double newAngleStart, double newRadius,
		double coulX,
		double coulY,
		bool newNarrative = true, size_t newcounter = 1, double newSpeed = 0) :
		                                             angleStart(newAngleStart),
	                                                 radius(newRadius),
		                                             couplCoordinats(coulX, coulY),
		                                             narrative(newNarrative),
		                                             counter(newcounter),
													 speed(newSpeed){

		vecIndex.push_back(std::pair <int, int>(1, 1));
		vecIndex.push_back(std::pair <int, int>(1, -1));
		vecIndex.push_back(std::pair <int, int>(-1,-1));
		vecIndex.push_back(std::pair <int, int>(-1, 1));
	};
	std::pair<double, double>  setCouplCoordinats()const { return couplCoordinats; }
	std::pair<double, double>  setsubjectCoordinats()const { return couplCoordinats; }

	double  getCouplPOS_X()const { return couplCoordinats.first; }
	double  getCouplPOS_Y()const { return couplCoordinats.second; }

	double  getSubjectPOS_X()const { return subjectCoordinats.first; }
	double  getSubjectPOS_Y()const { return subjectCoordinats.second; }

	size_t  getAngleStart()const { return angleStart; }
	double  getRadius()const { return radius; }
	bool    getNarrative()const { return narrative; }

	std::vector<std::pair<int, int>> getVecIndex()const { return vecIndex; }
	//________________________________________________________________________________


	void setCouplPOS_X(double newCouplPOS_X) { 
		couplCoordinats.first  = newCouplPOS_X; }
	void  setCouplPOS_Y(double newCouplPOS_Y) {
		couplCoordinats.second = newCouplPOS_Y; }

	void  setSubjectPOS_X(double newSubjectPOS_X) {
		subjectCoordinats.first = newSubjectPOS_X;}
	void  setSubjectPOS_Y(double newSubjectPOS_Y) {
		subjectCoordinats.second = newSubjectPOS_Y;}

	void  setAngleStart(size_t newAngleStart) { angleStart = newAngleStart; }
	void  setRadius(double newRadius) { radius = newRadius; }
	void  setNarrative(double newNarrative) { narrative = newNarrative; }
	
	//  вычмсление координаты
	void calcCoordinat(std::pair<int, int>, double&, double&);
	// 1 вычмсление первой координаты
	void calcFirstCoordinat();
	// 2 вычисление угла
	void calculationAngleBag();
	// вычисление угла рит€жени€
	double  calculationAngleGravity(const double, const double, const size_t);
	// вычисление длинны сороны
	double CalculationlengthSide(const double, const double);
	// основна€ функци€ лд€ подсчета всех данных
	void countingDataToMove(const short);
	// перехход угла по четверт€м
	void transition();

	
	~MoveBalans() {};
};
/*std::pair<double, double> subjectCoordinats,
		const std::pair<double, double>  couplCoordinats,
		const double radius,
		const size_t angleStart*/
