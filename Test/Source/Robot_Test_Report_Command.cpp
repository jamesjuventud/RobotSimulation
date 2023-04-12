
#include "Robot.h"
#include "RobotStringHelper.h"
#include "RobotErrorCodes.h"
#include "catch2.hpp"


TEST_CASE("Test Case 1: Testing REPORT COMMAND user errors.", "[.REPORT][.report][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	GIVEN("A ROBOT is not on a table.")
	{
		//--------------------------------------------------------------------------------------------
		RobotString cmd = "REPORT";
		uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_IS_NOT_ON_TABLE);

		//--------------------------------------------------------------------------------------------
		cmd = "report";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_IS_NOT_ON_TABLE);

		//--------------------------------------------------------------------------------------------
		cmd = "i report";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "REPORTX";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "xREPORT";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "REPORT ONCE";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "REPOR";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);

		//--------------------------------------------------------------------------------------------
		cmd = "REPORTS";
		return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
		REQUIRE(return_code == ROBOT_CODE_INVALID_COMMAND);
	}
}



