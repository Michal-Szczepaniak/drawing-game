/*
 * MusicPlayer.h
 *
 *  Created on: 9 Feb 2018
 *      Author: foidbgen
 */

#ifndef MUSICPLAYER_H_
#define MUSICPLAYER_H_

#include "oxygine-framework.h"
#include "sound/SoundPlayer.h"

using namespace oxygine;

class MusicPlayer {
public:
	MusicPlayer();
	~MusicPlayer();

	void update();
	void setMuted(bool muted);

	void musicDone(Event* ev);

private:
	SoundPlayer musicPlayer;
};

#endif /* MUSICPLAYER_H_ */
