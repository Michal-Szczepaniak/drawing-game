/*
 * Configuration.cpp
 *
 *  Created on: 3 Feb 2018
 *      Author: foidbgen
 */

#include "Configuration.h"

using namespace oxygine;

Configuration::Configuration() {
	file::buffer bf;
	Json::Reader reader;

	file::read("levels.json", bf);
	reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), levels, false);

	file::read("languages.json", bf);
	reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), languages, false);

	file::read("settings.json", bf);
	reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), settings, false);

	file::read("resolutions.json", bf);
	reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), resolutions, false);

	file::read("songs.json", bf);
	reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), songs, false);
}

void Configuration::save() {
	Json::FastWriter writer;
	std::string s;

	s = writer.write(settings);
	file::write("settings.json", s.c_str(), s.size());
}

std::vector<Chapter> Configuration::getLevels() {
    std::vector<Chapter> levels;
    for (const Json::Value &level: this->levels) {
        Chapter l;
        l.name = level["name"].asCString();
        for (const auto &image: level["images"])
            l.images.emplace_back(image.asCString());
    }
	return levels;
}

Json::Value* Configuration::getLanguages() {
	return &languages;
}

Json::Value* Configuration::getTranslations() {
	file::buffer bf;
	Json::Reader reader;

	if(!settings.isMember("language")) settings["langugage"] = "en";

	file::read("translations/" + settings["language"].asString() + ".json", bf);
	reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), translations, false);

	return &translations;
}

Json::Value* Configuration::getSettings() {
	return &settings;
}

Json::Value* Configuration::getResolutions() {
	return &resolutions;
}

Json::Value* Configuration::getSongs() {
	return &songs;
}

Json::Value* Configuration::getResolution() {
	return &resolutions[resolution];
}
void Configuration::setResolutions(int resolution) {
	this->resolution = resolution;
}
