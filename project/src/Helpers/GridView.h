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
    GridView(float width, float height, float x, float y, unsigned int rows = 1, unsigned int cols = 1);

    unsigned int getRows() const;
    GridView* setRows(unsigned int rows);
    unsigned int getCols() const;
    GridView* setCols(unsigned int cols);
    GridView* setRowsAndCols(unsigned int rows, unsigned int cols);

    float getWidth() const;
    GridView* setWidth(float width);
    float getHeight() const;
    GridView* setHeight(float height);
    GridView* setSize(float width, float height);

    float getX() const;
    GridView* setX(float x);
    float getY() const;
    GridView* setY(float y);
    GridView* setPosition(float x, float y);

    GridView* addActor(Actor* actor);
protected:
    unsigned int rows;
    unsigned int cols;
    float width;
    float height;
    float x;
    float y;

    float _cellWidth;
    float _cellHeight;

    std::vector<Actor*> actors;

    void recalculateRowSize();
};


#endif //GRAPHIE_GRIDVIEW_H
