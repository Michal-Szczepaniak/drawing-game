/*
 * Configuration.h
 *
 *  Created on: 3 Feb 2018
 *      Author: foidbgen
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "oxygine-framework.h"
#include "json/json.h"
#include "../Entities/Chapter.h"
#include <vector>

class Configuration
{
public:
	static Configuration& getInstance()
		{
			static Configuration instance; // Guaranteed to be destroyed.
								  // Instantiated on first use.
			return instance;
		}
	Configuration(Configuration const&) = delete;
    void operator=(Configuration const&) = delete;

	std::vector<Chapter> getLevels();
	Json::Value* getTranslations();
	Json::Value* getLanguages();
	Json::Value* getSettings();
	Json::Value* getResolutions();
	Json::Value* getSongs();

	void save();

	Json::Value* getResolution();
	void setResolutions(int resolution);

private:
	Configuration();

	Json::Value levels;
	Json::Value translations;
	Json::Value languages;
	Json::Value settings;
	Json::Value resolutions;
	Json::Value songs;
	int resolution = 0;

};

#endif /* CONFIGURATION_H_ */
