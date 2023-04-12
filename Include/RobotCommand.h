#ifndef ROBOT_COMMAND_H
#define ROBOT_COMMAND_H

#include "RobotStringHelper.h"

// Update this list when there is new command.
#define ROBOT_INVALID_COMMAND	0x0
#define ROBOT_PLACE_COMMAND		0x1
#define ROBOT_MOVE_COMMAND		0x2
#define ROBOT_LEFT_COMMAND		0x3
#define ROBOT_RIGHT_COMMAND		0x4
#define ROBOT_REPORT_COMMAND	0x5

// Static string command.
static const RobotString scPLACE = "PLACE";
static const RobotString scMOVE = "MOVE";
static const RobotString scLEFT = "LEFT";
static const RobotString scRIGHT = "RIGHT";
static const RobotString scREPORT = "REPORT";

// Position request structure.
typedef struct RobotCommandPosition_X
{
	int coordinate_X;
	int coordinate_Y;
	RobotString direction;
}RobotCommandPosition, RobotRequestPosition;

// Command structure.
typedef struct RobotCommandRequest_
{
	uint8_t command;
	RobotCommandPosition position;

	RobotCommandRequest_(uint8_t cmd = 0, int coordinate_X = -1, int coordinate_Y = -1, RobotString direction = "UNKNOWN") : command (cmd)
	{
		position.coordinate_X = coordinate_X;
		position.coordinate_Y = coordinate_Y;
		position.direction = direction;
	}

} RobotCommandRequest;


// Abstract Command class.
class Command
{
public:
	virtual ~Command() {}
	uint8_t virtual ExecuteCmd(RobotCommandRequest & command_request, RobotRequestPosition &position) = 0;
	
};


#endif // ROBOT_COMMAND_H