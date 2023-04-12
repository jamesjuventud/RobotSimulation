# RobotSimulation
A simple robot simulation.

Getting the project    
git     
Clone the repository from one of the following locations:    

GitHub Original      
https://github.com/jamesjuventud/RobotSimulation.git     

# Dependecies
1. Python 3.9.6     
2. CMake 3.21.1   
3. MSVC 2017 C++ Compiler

# To build the code:    
1. Navigate to the directory file and open cmd.     
2. Run "python robot_build.py --clean".     
3. Binaries will be in ...\build_win_x86\bin\     

# To test robot_simulator.exe   
1. Run the program in the cmd and test it. It will ask user input.    

# To unit test and integration test of test_robotsimulator.exe    
1. Open the application in the cmd and the following:   
     a. Run "test_robotsimulator.exe [all]"           -  to run all the test cases.      
     b. Run "test_robotsimulator.exe [integration]"   -  to run all the integrated commands (combination of all the commands) cases.    
     c. Run "test_robotsimulator.exe [place]"         -  to run specific PLACE command test cases.    
     d. Run "test_robotsimulator.exe [move]"          -  to run specific MOVE command test cases.  
     e. Run "test_robotsimulator.exe [left]"          -  to run specific LEFT command test cases.     
     f. Run "test_robotsimulator.exe [right]"         -  to run specific RIGHT command test cases.     
     g. Run "test_robotsimulator.exe [report]"        -  to run specific REPORT command test cases.    
