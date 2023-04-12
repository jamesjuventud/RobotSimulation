
#include "Robot.h"
#include "RobotStringHelper.h"
#include "RobotErrorCodes.h"
#include "catch2.hpp"


TEST_CASE("Test Case 1: Testing LEFT COMMAND user errors.", "[.LEFT][.left][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	GIVEN("A ROBOT is not on a table.")
	{
		//--------------------------------------------------------------------------------------------
		RobotString cmd = "LEFT";
		uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_IS_NOT_ON_TABLE);

		//--------------------------------------------------------------------------------------------
		cmd = "left";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_IS_NOT_ON_TABLE);

		//--------------------------------------------------------------------------------------------
		cmd = "i left";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "LEFTX";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "xLEFT";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "LEFT ONCE";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "YOU LEFT ME";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "LEF";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "LEFTS";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);
	}
}



