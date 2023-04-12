#ifndef ROBOT_POSITION_H
#define ROBOT_POSITION_H

#include <iostream>
#include "RobotStringHelper.h"
#include "RobotCoordinate.h"
#include "RobotDirection.h"


class RobotPosition 
{
private:
	RobotCoordinate coordinate_;
	RobotDirection direction_;

public:

	RobotPosition() :
		coordinate_(), direction_()
	{ }

	RobotPosition(RobotCoordinate &coordinate, RobotDirection& direction) :
		coordinate_(coordinate), direction_(direction)
	{ }

	RobotCoordinate GetRobotCoordinates() const
	{
		return coordinate_;
	}
	
	RobotDirection GetRobotDirection() const
	{
		return direction_;
	}

	void SetRobotDirection(RobotDirection& RobotDirection)
	{
		direction_ = RobotDirection;
	}

};

#endif // ROBOT_POSITION_H