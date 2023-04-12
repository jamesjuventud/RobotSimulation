#ifndef ROBOT_H
#define ROBOT_H

#include "RobotStringHelper.h"
#include "RobotDirection.h"
#include "RobotCoordinate.h"
#include "RobotPosition.h"
#include "RobotCommand.h"

extern uint8_t PlaneMatrixDimension_X;
extern uint8_t PlaneMatrixDimension_Y;


class TableRobot : public Command
{
public:
	TableRobot(uint8_t matrixPos_X, uint8_t matrixPos_Y);
	~TableRobot();
	TableRobot();

	// Pure virtual function from the inherited class.
	uint8_t ExecuteCmd(RobotCommandRequest & command_request, RobotRequestPosition &position) override;

	RobotDirection *direction;
	RobotCoordinate robot_coordinate;

	uint8_t RobotPlaceCommand(RobotCommandRequest & command_request, RobotRequestPosition &position);
	uint8_t RobotMoveCommand(RobotRequestPosition &position);
	void RobotRotationCommand(const uint8_t &rotate)const;
	void RobotReportCommand(RobotRequestPosition & position);

	int GetFirstNumberOccurence(RobotString & remove_place_str, int& number);
	uint8_t ParseInputCoordinates_XY(RobotString &command, int &x_coordinate, int& y_coordinate);

	uint8_t CommandParser(RobotString &command, RobotCommandRequest& cmd_request, RobotRequestPosition& position_request);
	uint8_t SendCommandAndReceive(RobotString &command, RobotCommandRequest &cmd_request, RobotRequestPosition& position_request);
	bool IsRobotOnTable() { return isOnTable; }

private:
	bool isOnTable;
protected:
	
};



#endif // ROBOT_H