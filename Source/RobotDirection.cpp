#include "Robot.h"

bool RobotDirection::SetRobotDirection(const RobotString &robot_direction)
{
	bool found_direction = true;

	if (robot_direction == "NORTH")
	{
		robot_facing = NORTH;
	}
	else if (robot_direction == "EAST")
	{
		robot_facing = EAST;
	}
	else if (robot_direction == "SOUTH")
	{
		robot_facing = SOUTH;
	}
	else if (robot_direction == "WEST")
	{
		robot_facing = WEST;
	}
	else {
		found_direction = false;
	}

	return found_direction;
}


uint8_t RobotDirection::ConvertRobotDirectionToInteger(const RobotString &robot_direction)
{
	if (robot_direction == "NORTH")
	{
		return NORTH;
	}
	else if (robot_direction == "EAST")
	{
		return EAST;
	}
	else if (robot_direction == "SOUTH")
	{
		return SOUTH;
	}
	else if (robot_direction == "WEST")
	{
		return WEST;
	}
	else {
		return UNSUPPORTED;
	}
}


bool RobotDirection::IsDirectionValid(const uint8_t &robot_direction) const
{
	bool is_valid = true;

	switch (robot_direction)
	{
	case NORTH: break;
	case EAST: break;
	case SOUTH: break;
	case WEST: break;
	default:
		is_valid = false;
		break;
	}

	return is_valid;
}


RobotString RobotDirection::ConvertRobotDirectionToString(const uint8_t &robot_direction) const
{
	RobotString direction_str = "UNKNOWN";

	switch (robot_direction)
	{
	case NORTH:
		direction_str = "NORTH"; break;
	case EAST:
		direction_str = "EAST"; break;
	case SOUTH:
		direction_str = "SOUTH"; break;
	case WEST:
		direction_str = "WEST"; break;
	default:
		break;
	}

	return direction_str;
}


void RobotDirection::TurnRight()
{
	if ( robot_facing == NORTH )
	{
		robot_facing = EAST;
	}
	else if (robot_facing == EAST)
	{
		robot_facing = SOUTH;
	}
	else if (robot_facing == SOUTH)
	{
		robot_facing = WEST;
	}
	else if (robot_facing == WEST)
	{
		robot_facing = NORTH;
	}
	else {	}
}


void RobotDirection::TurnLeft()
{
	if (robot_facing == NORTH)
	{
		robot_facing = WEST;
	}
	else if (robot_facing == EAST)
	{
		robot_facing = NORTH;
	}
	else if (robot_facing == SOUTH)
	{
		robot_facing = EAST;
	}
	else if (robot_facing == WEST)
	{
		robot_facing = SOUTH;
	}
	else {}
}

uint8_t RobotDirection::GetRobotDirection() const
{
	return robot_facing;
}




