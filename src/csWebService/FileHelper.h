#ifndef _FILEHELPER_H
#define _FILEHELPER_H

#include <string>
#include <iostream>
#include <fstream>>

inline bool fileExist(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

#endif // !_FILEHELPER_H