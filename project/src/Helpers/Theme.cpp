#include "Theme.h"
#include "../Game.h"

Theme::Theme() {
}

float Theme::getPaddingLarge() {
    return getStage()->getWidth()/6;
}

float Theme::getPaddingMedium() {
    return getStage()->getWidth()/8;
}

float Theme::getPaddingSmall() {
    return getStage()->getWidth()/10;
}