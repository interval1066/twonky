#ifndef TWONKY_H_
#define TWONKY_H_

#include <string>

// Could run under windows, you never know
#ifdef __GNUC__
#define LINEND '\n'
#elif defined _WIN32
#define LINEND '\r\n'
#endif

char const Dir[] = { 'n', 's', 'e', 'w' };

// Help
void DisplayHelp(void);

// Check to see that a 'move' or 'shoot'
// command is passed a valid direction
static inline bool
chckDir(char d)
{
	for(int n = 0; n < 4; n++)
		if(d == Dir[n]) return true;

	return false;
}

// Provide a trim method for std::string
// (Thanks JTC1/SC22/WG21...)
static inline
std::string &trimAll(std::string &s)
{
	if(s.size() == 0)
		return s;

	int val = 0;
	for (unsigned int cur = 0; cur < s.size(); cur++) {
		if(s[cur] != ' ' &&
			s[cur] != LINEND &&
			isalnum(s[cur]))
				s[val] = s[cur]; val++;
	}
	s.resize(val);
	return s;
}

#endif

