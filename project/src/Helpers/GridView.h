//
// Created by foidbgen on 9/2/18.
//

#ifndef GRAPHIE_GRIDVIEW_H
#define GRAPHIE_GRIDVIEW_H

#include "oxygine-framework.h"
#include <vector>

using namespace oxygine;

class GridView: public Object {

public:
    unsigned int getRows() const;
    GridView* setRows(unsigned int rows);
    unsigned int getCols() const;
    GridView* setCols(unsigned int cols);
    GridView* setRowsAndCols(unsigned int rows, unsigned int cols);

    unsigned int getWidth() const;
    GridView* setWidth(unsigned int width);
    unsigned int getHeight() const;
    GridView* setHeight(unsigned int height);
    GridView* setSize(unsigned int width, unsigned int height);

    unsigned int getX() const;
    GridView* setX(unsigned int x);
    unsigned int getY() const;
    GridView* setY(unsigned int y);
    GridView* setPosition(unsigned int x, unsigned int y);

    GridView* addActor(Actor* actor);
protected:
    unsigned int rows;
    unsigned int cols;
    unsigned int width;
    unsigned int height;
    unsigned int x;
    unsigned int y;

    std::vector<Actor*> actors;
};


#endif //GRAPHIE_GRIDVIEW_H
