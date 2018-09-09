#ifndef GRAPHIE_THEME_H
#define GRAPHIE_THEME_H

#include "../Game.h"

class Theme {
public:
    static inline float getPaddingLarge() {
        return getStage()->getWidth()/30;
    }

    static inline float getPaddingMedium() {
        return getStage()->getWidth()/60;
    }

    static inline float getPaddingSmall() {
        return getStage()->getWidth()/100;
    }

    static inline void centerVerically(const spSprite &sprite, const spSprite &target = nullptr) {
        float height = getStage()->getHeight()/2;
        if(target.get() != nullptr) {
            height = target->getHeight()/2;
        }

        sprite->setPosition(sprite->getX(), height - sprite->getHeight()/2);
    }
};


#endif //GRAPHIE_THEME_H
