// Robot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include "Robot.h"
#include "RobotStringHelper.h"
#include "RobotErrorCodes.h"

// Our grid dimension.
uint8_t PlaneMatrixDimension_X = 4;
uint8_t PlaneMatrixDimension_Y = 4;


// TableRobot default constructor.
TableRobot::TableRobot() : isOnTable(false)
{ 
	direction = new RobotDirection();
}


// TableRobot class constructor.
TableRobot::TableRobot(uint8_t x, uint8_t y) : isOnTable(false)
{
	direction = new RobotDirection();
}


// TableRobot class destructor.
TableRobot::~TableRobot() 
{
	if (direction)
	{
		delete direction;
		direction = nullptr;
	}
}


uint8_t TableRobot::ParseInputCoordinates_XY(RobotString &command, int& x_coordinate, int& y_coordinate)
{
	ROBOT_RESULT execute_result = ROBOT_CODE_SUCCESS;
	execute_result = GetFirstNumberOccurence(command, x_coordinate);

	if (execute_result == ROBOT_CODE_SUCCESS)
	{
		// Check the first char if it's comma.
		if (command[0] != delim_comma)
		{
			execute_result = ROBOT_CODE_INVALID_DELIMETER;
		}
		else {
			// Remove the comma and left whitespaces.
			command = command.erase(0, 1);
			TrimLeft(command);

			execute_result = GetFirstNumberOccurence(command, y_coordinate);

		}
	}
	
	return execute_result;
}


int TableRobot::GetFirstNumberOccurence(RobotString & remove_place_str, int & number)
{
	number = -1;
	ROBOT_RESULT result = ROBOT_CODE_SUCCESS;
	RobotString temp = "";
	bool found_X = false;

	for (uint8_t i = 0; i < remove_place_str.size(); i++)
	{
		if (isdigit(remove_place_str[i]))
		{
			temp.push_back(remove_place_str[i]);
			found_X = true;
		}
		else if (!isdigit(remove_place_str[i]) && found_X == false)
		{
			result = ROBOT_CODE_INVALID_COORDINATES;
			break;
		}
		else
		{
			// Remove the index occurence of the first number.
			remove_place_str = remove_place_str.substr(i, remove_place_str.size());
			
			// Remove left whitespaces.
			TrimLeft(remove_place_str);
			
			break;
		}
	}

	if (result != ROBOT_CODE_SUCCESS)
	{
		return result;
	}

	// Convert string to integer in base 10;
	if (!temp.empty()) {
		number = std::stoi(temp.c_str());		
	}
	else {
		result = ROBOT_CODE_INVALID_COORDINATES;
	}

	return result;
}


uint8_t TableRobot::CommandParser(RobotString& command, RobotCommandRequest& cmd_request, RobotRequestPosition& position_request)
{
	std::istringstream data(command);
	RobotString token;
	bool is_parse_success = true;
	ROBOT_RESULT execute_result = ROBOT_CODE_SUCCESS;
	MakeUpper(command);
	Trim(command);

	if (Compare(command, const_cast<RobotString&>(scMOVE)) == 0)
	{
		// Set the current command.
		cmd_request.command = ROBOT_MOVE_COMMAND;

		// Real send and receive command.
		execute_result = ExecuteCmd(cmd_request, position_request);
		
	}
	else if (Compare(command, const_cast<RobotString&>(scLEFT)) == 0)
	{
		// Set the current command.
		cmd_request.command = ROBOT_LEFT_COMMAND;

		// Real send and receive command.
		execute_result = ExecuteCmd(cmd_request, position_request);
	}
	else if (Compare(command, const_cast<RobotString&>(scRIGHT)) == 0)
	{
		// Set the current command.
		cmd_request.command = ROBOT_RIGHT_COMMAND;

		// Real send and receive command.
		execute_result = ExecuteCmd(cmd_request, position_request);
	}
	else if (Compare(command, const_cast<RobotString&>(scREPORT)) == 0)
	{
		// Set the current command.
		cmd_request.command = ROBOT_REPORT_COMMAND;

		// Real send and receive command.
		execute_result = ExecuteCmd(cmd_request, position_request);
	}
	else 
	{
		// Extract the first token.
		data >> token;
		MakeUpper(token);

		// Remove left and right whitespaces.
		Trim(token);
		
		if (Compare(token, const_cast<RobotString&>(scPLACE)) != 0) 
		{
			execute_result = ROBOT_CODE_INVALID_COMMAND;
			return execute_result;
		}
		else 
		{
			// Copy the characters after the PLACE string.
			command = command.substr(5, command.size());

			// Remove left whitespaces.
			TrimLeft(command);

			// Get the X and Y coordinates.
			int x_coordinate = -1, y_coordinate = -1;
			execute_result = ParseInputCoordinates_XY(command, x_coordinate, y_coordinate);
			
			if (execute_result == ROBOT_CODE_SUCCESS)
			{
				// Check if the x and y coordinates are valid.
				bool is_coordinate_valid = robot_coordinate.CheckCoordinateValidity_X(x_coordinate);
				if (is_coordinate_valid)
				{
					is_coordinate_valid = robot_coordinate.CheckCoordinateValidity_Y(y_coordinate);
					if (!is_coordinate_valid)
					{
						execute_result = ROBOT_CODE_BEYOND_Y_AXIS_COORDINATE;
						return execute_result;
					}
				}
				else {
					execute_result = ROBOT_CODE_BEYOND_X_AXIS_COORDINATE;
					return execute_result;
				}

				// Check the first character if it's comma.
				if (command[0] != delim_comma)
				{
					execute_result = ROBOT_CODE_INVALID_DELIMETER;
					return execute_result;
				}
				else {
					// Remove the comma and left whitespaces.
					command = command.erase(0, 1);
					TrimLeft(command);
				}

				// Get the integer equivalent of the string direction.
				uint8_t direction_value = direction->ConvertRobotDirectionToInteger(command);

				// Check the direction string input.
				if (!direction->IsDirectionValid(direction_value))
				{
					execute_result = ROBOT_CODE_INVALID_DIRECTION;
					return execute_result;
				}
				else {

					// Set the current command.
					cmd_request.command = ROBOT_PLACE_COMMAND;
					cmd_request.position.coordinate_X = x_coordinate;
					cmd_request.position.coordinate_Y = y_coordinate;
					cmd_request.position.direction = command;

					// Real send and receive command.
					execute_result = ExecuteCmd(cmd_request, position_request);

				}
			}
		}
	}

	return execute_result;
}


uint8_t TableRobot::RobotPlaceCommand(RobotCommandRequest & command_request, RobotRequestPosition &position)
{
	ROBOT_RESULT place_result = ROBOT_CODE_SUCCESS;

	// Set the direction.
	bool is_valid_direction = direction->SetRobotDirection(command_request.position.direction);

	if (is_valid_direction)
	{
		// If true, then set also the x and y coordinates.
		robot_coordinate.SetRobotCoordinate_XY(command_request.position.coordinate_X, command_request.position.coordinate_Y);

		// Set the new values.
		uint8_t direction_value = direction->GetRobotDirection();

		// Update the position referenced data.
		position.direction = direction->ConvertRobotDirectionToString(direction_value);
		position.coordinate_X = robot_coordinate.GetRobotCoordinate_X();
		position.coordinate_Y = robot_coordinate.GetRobotCoordinate_Y();

		// Set to true as PLACE command is successfull.
		isOnTable = true;
	}
	else {
		place_result = ROBOT_CODE_INVALID_DIRECTION;
	}

	return place_result;
}


uint8_t TableRobot::RobotMoveCommand(RobotRequestPosition &position)
{
	RobotDirection robot_direction;
	ROBOT_RESULT result = ROBOT_CODE_SUCCESS;

	bool is_valid = false;
	int robot_coordinate_X = robot_coordinate.GetRobotCoordinate_X();
	int robot_coordinate_Y = robot_coordinate.GetRobotCoordinate_Y();
	uint8_t robot_facing = direction->GetRobotDirection();

	switch (robot_facing)
	{
	case robot_direction.NORTH:
		robot_coordinate_Y = robot_coordinate_Y + 1;
		break;
	case robot_direction.EAST:
		robot_coordinate_X = robot_coordinate_X + 1;
		break;
	case robot_direction.SOUTH:
		robot_coordinate_Y = robot_coordinate_Y - 1;
		break;
	case robot_direction.WEST:
		robot_coordinate_X = robot_coordinate_X - 1;
		break;
	default: 
		result = ROBOT_CODE_INVALID_DIRECTION;
		break;
	}

	// Check if X and Y coordinates are not beyond the maximum grid.
	is_valid = robot_coordinate.CheckCoordinateValidity_XY(robot_coordinate_X, robot_coordinate_Y);
	if (is_valid)
	{
		// Update the X and Y coordinate.
		RobotString direction_str = direction->ConvertRobotDirectionToString(robot_facing);
		robot_coordinate.SetRobotCoordinate_XY(robot_coordinate_X, robot_coordinate_Y);

		// Update the position referenced data.
		position.coordinate_X = robot_coordinate_X;
		position.coordinate_Y = robot_coordinate_Y;
		position.direction = direction_str;
	}
	else {
		result = ROBOT_CODE_WILL_FALL;
	}

	return result;
}


void TableRobot::RobotRotationCommand(const uint8_t& rotate) const
{
	if (rotate == ROBOT_LEFT_COMMAND)
	{
		direction->TurnLeft();
	}
	else if (rotate == ROBOT_RIGHT_COMMAND)
	{
		direction->TurnRight();
	}
	else {}
	
	uint8_t robot_facing = direction->GetRobotDirection();
}


void TableRobot::RobotReportCommand(RobotRequestPosition & position)
{
	uint8_t direction_value = direction->GetRobotDirection();

	// Update the position referenced data.
	position.direction = direction->ConvertRobotDirectionToString(direction_value);
	position.coordinate_X = robot_coordinate.GetRobotCoordinate_X();
	position.coordinate_Y = robot_coordinate.GetRobotCoordinate_Y();

	std::cout << "Output: " << position.coordinate_X << "," << position.coordinate_Y << "," << position.direction << std::endl;
}


uint8_t TableRobot::ExecuteCmd(RobotCommandRequest & command_request, RobotRequestPosition &position)
{
	ROBOT_RESULT execute_result = ROBOT_CODE_SUCCESS;

	// Do command checking.
	// Only PLACE command is valid if robot is not on the table yet.
	if (command_request.command != ROBOT_PLACE_COMMAND && !isOnTable)
	{
		execute_result = ROBOT_CODE_IS_NOT_ON_TABLE;
	}
	else {
		switch (command_request.command)
		{
		case ROBOT_PLACE_COMMAND:
			execute_result = RobotPlaceCommand(command_request, position);
			break;
		case ROBOT_MOVE_COMMAND:
			execute_result = RobotMoveCommand(position);
				break;
		case ROBOT_LEFT_COMMAND:
			RobotRotationCommand(command_request.command);
			break;
		case ROBOT_RIGHT_COMMAND:
			RobotRotationCommand(command_request.command);
			break;
		case ROBOT_REPORT_COMMAND:
			RobotReportCommand(position);
			break;
		default:
			execute_result = ROBOT_CODE_INVALID_COMMAND;
			break;
		}
	}

	return execute_result;
}


uint8_t TableRobot::SendCommandAndReceive(RobotString &command, RobotCommandRequest& cmd_request, RobotRequestPosition& position_request)
{
	uint8_t parse = CommandParser(command, cmd_request, position_request);

	return parse;
}




