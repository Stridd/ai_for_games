#pragma once
#include "json.hpp"

using json = nlohmann::json;

class ConfigurationReader
{
public:
	static json getData();
};
