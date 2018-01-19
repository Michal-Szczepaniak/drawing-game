/*
 * mainActor.h
 *
 *  Created on: 15 Jan 2018
 *      Author: foidbgen
 */

#ifndef MAINACTOR_H_
#define MAINACTOR_H_

#include "oxygine-framework.h"
#include <functional>

using namespace oxygine;

class MainActor: public Actor
{
public:
    spTextField _text;
    spSprite    _button;
    spNativeTexture texture;
	Color color;
	spSprite preview;

    MainActor();

    void buttonClicked(Event* event);
    void onDown(Event* ev);
    void onMove(Event* ev);
};
//declare spMainActor as intrusive_ptr holder of MainActor
typedef oxygine::intrusive_ptr<MainActor> spMainActor;
//you could use DECLARE_SMART preprocessor definition it does the same:
//DECLARE_SMART(MainActor, spMainActor)

#endif /* MAINACTOR_H_ */
