/*
 * MusicPlayer.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: foidbgen
 */

#include "MusicPlayer.h"
#include "Game.h"
#include "Helpers/Configuration.h"
#include "sound/SoundSystem.h"
#include "sound/SoundInstance.h"
#include <stdlib.h>
#include <time.h>

using namespace oxygine;

MusicPlayer::MusicPlayer() {
	srand (time(NULL));

	musicPlayer.setVolume(!((*Configuration::getInstance().getSettings())["muted"].asBool())*1.0f);
	int songId = rand() % (Configuration::getInstance().getSongs()->size());
	spSoundInstance music = musicPlayer.play(::getGameResources()->get((*Configuration::getInstance().getSongs())[songId].asString()), PlayOptions());
	music->setDoneCallback(CLOSURE(this, &MusicPlayer::musicDone));
}

MusicPlayer::~MusicPlayer() {

}

void MusicPlayer::update() {
	SoundSystem::get()->update();
	musicPlayer.update();
}

void MusicPlayer::setMuted(bool muted) {
	musicPlayer.setVolume(((int)!muted)*1.0f);
}

void MusicPlayer::musicDone(Event* ev) {
	int songId = rand() % (Configuration::getInstance().getSongs()->size());
	spSoundInstance music = musicPlayer.play(::getGameResources()->get((*Configuration::getInstance().getSongs())[songId].asString()), PlayOptions());
	music->setDoneCallback(CLOSURE(this, &MusicPlayer::musicDone));
}
