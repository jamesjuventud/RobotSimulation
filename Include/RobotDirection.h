#ifndef ROBOT_DIRECTION_H
#define ROBOT_DIRECTION_H

#include <iostream>

class RobotDirection
{
public:

	enum DirectionEnum
	{
		NORTH = 1,
		EAST,
		SOUTH,
		WEST,
		UNSUPPORTED
	};

	RobotDirection() : robot_facing( UNSUPPORTED )
	{
		//std::cout << "RobotDirection object created!" << std::endl;
	}

	RobotDirection(const DirectionEnum direction) : robot_facing(direction)
	{ }

	~RobotDirection()
	{
		//std::cout << "RobotDirection object destroyed!!" << std::endl;
	}

	void TurnLeft();
	void TurnRight();

	bool SetRobotDirection(const RobotString &robot_direction);
	bool IsDirectionValid(const uint8_t &robot_direction) const;
	RobotString ConvertRobotDirectionToString(const uint8_t &robot_direction) const;
	uint8_t ConvertRobotDirectionToInteger(const RobotString &robot_direction);
	uint8_t GetRobotDirection() const;

	DirectionEnum enum_direction;

private:
	uint8_t robot_facing;

};



#endif // ROBOT_DIRECTION_H