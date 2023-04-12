cmake_minimum_required(VERSION 3.12)

project(ROBOT_SIMULATION)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL Windows)
  add_definitions( -D_CRT_SECURE_NO_WARNINGS)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

#set_target_properties(robotsimulation PROPERTIES CXX_STANDARD 17)
set_target_properties( PROPERTIES CXX_STANDARD 17)

#set (ROBOT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/Source)
set (ROBOT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(Include/ Test/Include/)


add_executable(robot_simulator

	Source/Robot.cpp
	Source/RobotDirection.cpp
	Source/RobotMain.cpp
	Source/RobotStringHelper.cpp
   
	Include/Robot.h
	Include/RobotCommand.h
	Include/RobotCoordinate.h
	Include/RobotDirection.h
	Include/RobotErrorCodes.h
	Include/RobotPosition.h
	Include/RobotResource.h
	Include/RobotStringHelper.h
	
)

add_executable(test_robotsimulator

	Source/Robot.cpp
	Source/RobotDirection.cpp
	Source/RobotStringHelper.cpp
	
	Test/Source/Robot_Test_Command_Integration.cpp
	Test/Source/Robot_Test_Left_Command.cpp
	Test/Source/Robot_Test_Move_Command.cpp
	Test/Source/Robot_Test_Place_Command.cpp
	Test/Source/Robot_Test_Report_Command.cpp
	Test/Source/Robot_Test_Right_Command.cpp
	Test/Source/RobotTestMain.cpp
   
    Test/Include/catch2.hpp
	Include/Robot.h
	Include/RobotCommand.h
	Include/RobotCoordinate.h
	Include/RobotDirection.h
	Include/RobotErrorCodes.h
	Include/RobotPosition.h
	Include/RobotResource.h
	Include/RobotStringHelper.h
  
)

 set_target_properties(robot_simulator PROPERTIES CXX_STANDARD 17)
target_include_directories(robot_simulator PUBLIC ${SCN_SOURCE_DIR})
