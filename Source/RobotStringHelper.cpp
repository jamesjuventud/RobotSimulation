#include "RobotStringHelper.h"


// Convert string to uppercase.
void MakeUpper(RobotString& str)
{
	for (auto & c : str) c = (char)toupper(c);
}

// Trim from left.
RobotString& TrimLeft(RobotString& s, const char* t )
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// Trim from right.
RobotString& TrimRight(RobotString& s, const char* t )
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// Trim both left and right.
RobotString& Trim(RobotString& s, const char* t )
{
	return TrimLeft(TrimRight(s, t), t);
}

// Return:
//		0	They compare equal
//		<0	Either the value of the first character that does not match is lower in the compared string, or all compared characters match but the compared string is shorter.
//		>0	Either the value of the first character that does not match is greater in the compared string, or all compared characters match but the compared string is longer.
int Compare(RobotString& Str1, RobotString& Str2)
{
	return Str1.compare(Str2);
}

// Return:
//		0	They compare equal
//		<0	Either the value of the first character that does not match is lower in the compared string, or all compared characters match but the compared string is shorter.
//		>0	Either the value of the first character that does not match is greater in the compared string, or all compared characters match but the compared string is longer.
/*int Compare(RobotString& Str1, const RobotString& Str2)
{
	return Str1.compare(Str2);
}
*/

// Return:
//		The position of the first character that does not match.
//		If no such characters are found, the function returns string::npos.
std::size_t ContainsDelim(RobotString& command, const char delim)
{
	return command.find(delim);
}
