
#include "Robot.h"
#include "RobotStringHelper.h"
#include "RobotErrorCodes.h"
#include "catch2.hpp"


TEST_CASE("Test Case 1: Testing RIGHT COMMAND user errors.", "[.RIGHT] [.right] [.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	GIVEN("A ROBOT is not on a table.")
	{
		//--------------------------------------------------------------------------------------------
		RobotString cmd = "RIGHT";
		uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_IS_NOT_ON_TABLE);

		//--------------------------------------------------------------------------------------------
		cmd = "right";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_IS_NOT_ON_TABLE);

		//--------------------------------------------------------------------------------------------
		cmd = "i right";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "RIGHTX";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "xRIGHT";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "RIGHT ONCE";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "YOU are RIGHT";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "RIGH";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "RIGHTS";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);
	}
}



