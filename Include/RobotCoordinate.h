#ifndef ROBOT_COORDINATE_H
#define ROBOT_COORDINATE_H

#include <iostream>
#include "Robot.h"

extern uint8_t PlaneMatrixDimension_X;
extern uint8_t PlaneMatrixDimension_Y;


class RobotCoordinate
{
public:
	RobotCoordinate() : matrix_X(-1), matrix_Y(-1) { }
	RobotCoordinate(int x, int y) : matrix_X(x), matrix_Y(y) { }
	~RobotCoordinate() {}

	void SetRobotCoordinate_X(const int &coordinate_X)
	{
		matrix_X = coordinate_X;
	}

	void SetRobotCoordinate_Y(const int &coordinate_Y)
	{
		matrix_Y = coordinate_Y;
	}

	void SetRobotCoordinate_XY(const int &coordinate_X, const int &coordinate_Y)
	{
		matrix_X = coordinate_X;
		matrix_Y = coordinate_Y;
	}

	bool CheckCoordinateValidity_X(int &value_X)
	{
		return (value_X >= 0 && value_X <= PlaneMatrixDimension_X);
	}
	
	bool CheckCoordinateValidity_Y(int &value_Y)
	{
		return (value_Y >= 0 && value_Y <= PlaneMatrixDimension_Y);
	}

	bool CheckCoordinateValidity_XY(int &value_X, int &value_Y)
	{
		return ((value_X >= 0 && value_X <= PlaneMatrixDimension_X) && (value_Y >= 0 && value_Y <= PlaneMatrixDimension_Y));
	}

	int GetRobotCoordinate_X() const
	{
		return matrix_X;
	}

	int GetRobotCoordinate_Y() const
	{
		return matrix_Y;
	}

private:
	int matrix_X;
	int matrix_Y;
};



#endif // ROBOT_COORDINATE_H