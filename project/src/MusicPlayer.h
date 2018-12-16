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
	MusicPlayer(std::shared_ptr<Resources> resources);
	~MusicPlayer();

	void update();
	void setMuted(bool muted);

	void musicDone(Event* ev);
	std::shared_ptr<Resources> resources;

private:
	SoundPlayer musicPlayer;
};
typedef std::shared_ptr<MusicPlayer> MusicPlayerPtr;

#endif /* MUSICPLAYER_H_ */
