#include <fstream>
#include "ConfigurationReader.h"

json ConfigurationReader::getData()
{
    static json data;

    if (data.empty())
    {
        std::ifstream configurationFile("config.json");

        data = json::parse(configurationFile);

        configurationFile.close();

    }

    return data;
}
