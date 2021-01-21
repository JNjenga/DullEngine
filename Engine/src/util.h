/*
 * This file handles stuff like io, serialization etc
 */
#pragma once

#include "dull_engine.h"
#include <string>

namespace DE
{
	void read_file(const char * path, std::string & data);
	// void write_file(const char * path, const char * data);
	// void read_texture(const char * path, char *data);
}
