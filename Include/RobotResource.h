#ifndef ROBOT_RESOURCE_TABLE_H
#define ROBOT_RESOURCE_TABLE_H

#include <iostream>
#include "RobotStringHelper.h"
#include "RobotResource.h"
#include "RobotErrorCodes.h"

RobotString ConvertErrorCodeToString(uint8_t &error_code)
{
	RobotString error_str = "Unknown error code";
	switch (error_code)
	{
	case ROBOT_CODE_SUCCESS:	
		error_str = "Success";
		break;
	case ROBOT_CODE_FAILED:		
		error_str = "Failed";
		break;
	case ROBOT_CODE_INVALID_COMMAND: 
		error_str = "Invalid Command";
		break;
	case ROBOT_CODE_INVALID_INPUT:
		error_str = "Invalid input";
		break; 
	case ROBOT_CODE_INVALID_COORDINATES:
		error_str = "Invalid coordinates. Expecting a positive number.";
		break;
	case ROBOT_CODE_IS_NOT_ON_TABLE:
		error_str = "Robot is not on the table. Try <PLACE X,Y,Direction> command first.";
		break;
	case ROBOT_CODE_WILL_FALL:
		error_str = "Robot will fall";
		break;
	case ROBOT_CODE_ERROR_SET_FAILED:
		error_str = "Failed to set error code";
		break;
	case ROBOT_CODE_INVALID_DELIMETER:
		error_str = "Place command delimeter is wrong. Expecting a comma.";
		break;
	case ROBOT_CODE_INVALID_DIRECTION:
		error_str = "Invalid direction. Valid directions: e.g. NORTH,EAST,SOUTH,WEST";
		break;
	case ROBOT_CODE_BEYOND_X_AXIS_COORDINATE:
		error_str = "Beyond x-axis coordinate maximum limit";
		break;
	case ROBOT_CODE_BEYOND_Y_AXIS_COORDINATE:
		error_str = "Beyond y-axis coordinate maximum limit";
		break;
	default: break;
	}

	return error_str;
}

#endif // ROBOT_RESOURCE_TABLE_H
