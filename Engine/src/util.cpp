#include "dull_engine.h"
#include "util.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void DE::read_file(const char * path, std::string & data)
{
	std::ifstream file;
	std::string line;
	std::stringstream ss;

	file.open(path);
	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			data.append(line);
			data.append("\n");
		}
	}
}
