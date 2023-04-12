
#include "Robot.h"
#include "RobotStringHelper.h"
#include "RobotErrorCodes.h"
#include "catch2.hpp"


TEST_CASE("Test Case 1: Testing PLACE COMMAND user errors.", "[.PLACE] [.place] [.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	GIVEN("A ROBOT is not on a table.")
	{
		//--------------------------------------------------------------------------------------------
		RobotString cmd = "PLACE";
		uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COORDINATES);

		//--------------------------------------------------------------------------------------------
		cmd = "place";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COORDINATES);

		//--------------------------------------------------------------------------------------------
		cmd = "PLACE_ONCE";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "i place";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "PLACEX";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "xPLACE";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "YOU are my PLACE";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "PLAC";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "PLACES";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);
	}
}



