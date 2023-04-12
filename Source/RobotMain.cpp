#include <iostream>
#include <string>
#include <sstream>
#include "Robot.h"
#include "RobotStringHelper.h"
#include "RobotResource.h"


int main(int argc, const char * argv[])
{
	std::string input = "";
	TableRobot robot;

	std::cout << "Welcome to Robot Simulation!" << std::endl;
	std::cout << "Supported Commands: <PLACE X,Y,Direction> , MOVE , LEFT , RIGHT, REPORT, EXIT" << std::endl;
	std::cout << "Enter a command: ";

	while (true)
	{
		std::getline(std::cin, input);
		MakeUpper(input);

		if (input.compare("EXIT") == 0)
		{
			break;
		}
		else {
			RobotCommandRequest cmd_request;
			RobotRequestPosition pos_request;

			uint8_t return_code = robot.SendCommandAndReceive(input, cmd_request, pos_request);
			if (return_code != 0) 
			{
				std::cout << "Return Code = " << (uint16_t)return_code << " (" << ConvertErrorCodeToString(return_code) << ")" << std::endl;
			}
		}
	}

	return 0;
}