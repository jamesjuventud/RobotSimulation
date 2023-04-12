#ifndef ROBOT_STRING_HELPER_H
#define ROBOT_STRING_HELPER_H

#include <iostream>

typedef std::string RobotString;
typedef uint8_t ROBOT_RESULT;

void MakeUpper(RobotString& str);
int  Compare(RobotString& Str1, RobotString& Str2);

std::size_t ContainsDelim(RobotString& command, const char delim);
static const char delim_comma = ',';

RobotString& TrimLeft(RobotString& s, const char* t = (" \t\n\r\f\v"));
RobotString& TrimRight(RobotString& s, const char* t = (" \t\n\r\f\v"));
RobotString& Trim(RobotString& s, const char* t = (" \t\n\r\f\v"));

#endif // ROBOT_STRING_HELPER_H