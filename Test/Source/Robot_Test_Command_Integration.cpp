
#include <sstream>
#include "Robot.h"
#include "RobotStringHelper.h"
#include "RobotResource.h"
#include "catch2.hpp"


TEST_CASE("Test Case 1: User input variations.", "[.INTEGRATION][.Integration][.integration][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	//--------------------------------------------------------------------------------------------
	RobotString cmd = "PLACE	  2		,			3    ,			NORTH";
	uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	//--------------------------------------------------------------------------------------------
	cmd = "		PLACE	  2		,			3    ,			NORTH";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	//--------------------------------------------------------------------------------------------
	cmd = "		PLACE	  x		,			3    ,			NORTH";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_CODE_INVALID_COORDINATES);

	//--------------------------------------------------------------------------------------------
	cmd = "		PLACE	  2		,			3    ,			NORTHs";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_CODE_INVALID_DIRECTION);

	//--------------------------------------------------------------------------------------------
	cmd = "		PLACE	  6		,			3    ,			NORTHs";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_CODE_BEYOND_X_AXIS_COORDINATE);

	//--------------------------------------------------------------------------------------------
	cmd = "		PLACE	  2		,			8    ,			NORTH";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_CODE_BEYOND_Y_AXIS_COORDINATE);

	//--------------------------------------------------------------------------------------------
	cmd = "		PLACE	  2		-			8    ^			NORTH";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_CODE_INVALID_DELIMETER);

	//--------------------------------------------------------------------------------------------
	cmd = "		PLACE 2,3";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_CODE_INVALID_DELIMETER);

}


TEST_CASE("Test Case 2: Integration", "[.INTEGRATION][.Integration][.integration][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;
	
	//--------------------------------------------------------------------------------------------
	RobotString cmd = "PLACE 0,0,NORTH";
	uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	//--------------------------------------------------------------------------------------------
	cmd = "MOVE";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	//--------------------------------------------------------------------------------------------
    cmd = "REPORT";
	return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);
	REQUIRE(pos_request.coordinate_X == 0);
	REQUIRE(pos_request.coordinate_Y == 1);
	REQUIRE(pos_request.direction == "NORTH");

}

TEST_CASE("Test Case 3: Robot will fall.", "[.INTEGRATION][.Integration][.integration][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	//--------------------------------------------------------------------------------------------
	RobotString cmd = "PLACE 1,2,EAST";
	uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	GIVEN("A PLACE command is successfull")
	{
		CHECKED_IF(return_code == ROBOT_SUCCESS)
		{
			//--------------------------------------------------------------------------------------------
			cmd = "MOVE";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "MOVE";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "MOVE";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "MOVE";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_CODE_WILL_FALL);
		}
	}
}

TEST_CASE("Test Case 4: Robot rotation.", "[.INTEGRATION][.Integration][.integration][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	//--------------------------------------------------------------------------------------------
	RobotString cmd = "PLACE 3,3,NORTH";
	uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	GIVEN("A PLACE command is successfull")
	{
		CHECKED_IF(return_code == ROBOT_SUCCESS)
		{
			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "RIGHT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "RIGHT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "RIGHT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "RIGHT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "RIGHT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "REPORT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);
			REQUIRE(pos_request.coordinate_X == 3);
			REQUIRE(pos_request.coordinate_Y == 3);
			REQUIRE(pos_request.direction == "EAST");
		}
	}
}

TEST_CASE("Test Case 5: Robot edge movements.", "[.INTEGRATION][.Integration][.integration][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	//--------------------------------------------------------------------------------------------
	RobotString cmd = "PLACE 0,0,EAST";
	uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	GIVEN("A PLACE command is successfull")
	{
		CHECKED_IF(return_code == ROBOT_SUCCESS)
		{
			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "move";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "REPORT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);
			REQUIRE(pos_request.coordinate_X == 0);
			REQUIRE(pos_request.coordinate_Y == 0);
			REQUIRE(pos_request.direction == "SOUTH");
		}
	}
}

TEST_CASE("Test Case 6: Give PDF example.", "[.INTEGRATION][.Integration][.integration][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;


	//--------------------------------------------------------------------------------------------
	RobotString cmd = "PLACE 1,2,EAST";
	uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	GIVEN("A PLACE command is successfull")
	{
		CHECKED_IF(return_code == ROBOT_SUCCESS)
		{
			//--------------------------------------------------------------------------------------------
			cmd = "MOVE";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "MOVE";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "MOVE";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "REPORT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);
			REQUIRE(pos_request.coordinate_X == 3);
			REQUIRE(pos_request.coordinate_Y == 3);
			REQUIRE(pos_request.direction == "NORTH");
		}

	}
}


TEST_CASE("Test Case 7: Succesfull Place command twice.", "[.INTEGRATION][.Integration][.integration][.ALL] [.all]")
{
	TableRobot roblox;
	RobotCommandRequest cmd_request;
	RobotRequestPosition pos_request;
	uint8_t ROBOT_SUCCESS = 0;

	//--------------------------------------------------------------------------------------------
	RobotString cmd = "PLACE 1,2,EAST";
	uint8_t return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
	REQUIRE(return_code == ROBOT_SUCCESS);

	GIVEN("A PLACE command is successfull")
	{
		CHECKED_IF(return_code == ROBOT_SUCCESS)
		{
			//--------------------------------------------------------------------------------------------
			cmd = "REPORT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);
			REQUIRE(pos_request.coordinate_X == 1);
			REQUIRE(pos_request.coordinate_Y == 2);
			REQUIRE(pos_request.direction == "EAST");

			//--------------------------------------------------------------------------------------------
			cmd = "PLACE 3,1,SOUTH";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "REPORT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);
			REQUIRE(pos_request.coordinate_X == 3);
			REQUIRE(pos_request.coordinate_Y == 1);
			REQUIRE(pos_request.direction == "SOUTH");

			//--------------------------------------------------------------------------------------------
			cmd = "MOVE";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "LEFT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);

			//--------------------------------------------------------------------------------------------
			cmd = "REPORT";
			return_code = roblox.SendCommandAndReceive(cmd, cmd_request, pos_request);
			REQUIRE(return_code == ROBOT_SUCCESS);
			REQUIRE(pos_request.coordinate_X == 3);
			REQUIRE(pos_request.coordinate_Y == 0);
			REQUIRE(pos_request.direction == "EAST");

		}	
	}
}