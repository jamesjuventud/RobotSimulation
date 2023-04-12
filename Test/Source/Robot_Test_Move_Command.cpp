
#include "Robot.h"
#include "RobotStringHelper.h"
#include "RobotErrorCodes.h"
#include "catch2.hpp"


TEST_CASE("Test Case 1: Testing MOVE COMMAND user errors.", "[.MOVE][.move][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	GIVEN("A ROBOT is not on a table.")
	{
		//--------------------------------------------------------------------------------------------
		RobotString cmd = "MOVE";
		uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_IS_NOT_ON_TABLE);

		//--------------------------------------------------------------------------------------------
		cmd = "move";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_IS_NOT_ON_TABLE);

		//--------------------------------------------------------------------------------------------
		cmd = "i move";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "MOVEX";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "xMOVE";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "MOVE LIKE A JAGGER";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "MOV";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);
	}
}



