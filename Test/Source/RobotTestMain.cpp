
#define CATCH_CONFIG_RUNNER // This defines a main() as defaulted by Catch2. If needed, you can change this CATCH_CONFIG_RUNNER and supply your own main() as long as it calls 'Catch::Session().run( argc, argv )' to run Catch2 Test

#include <iostream>
#include <string>
#include "Robot.h"
#include "RobotStringHelper.h"
#include "catch2.hpp"

int main(int argc, const char * argv[])
{
	
	Catch::Session().run(argc, argv);

	return 0;
}