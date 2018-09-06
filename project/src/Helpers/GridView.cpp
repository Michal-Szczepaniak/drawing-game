//
// Created by foidbgen on 9/2/18.
//

#include "GridView.h"

GridView::GridView(float width, float height, float x, float y, unsigned int rows,
                   unsigned int cols) {
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->rows = rows;
    this->cols = cols;
    recalculateRows();
}

GridView *GridView::setRowsAndCols(unsigned int rows, unsigned int cols) {
    this->rows = rows;
    this->cols = cols;
    recalculateRows();
    return this;
}

GridView *GridView::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    recalculateRows();
    return this;
}

GridView *GridView::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    return this;
}

GridView *GridView::addActor(spActor actor) {
    if(actor != NULL && actors.size() < getRows()*getCols()) {
        actors.push_back(actor);
        recalculateRows();
    }
    return this;
}

unsigned int GridView::getRows() const {
    return rows;
}

GridView* GridView::setRows(unsigned int rows) {
    this->rows = rows;
    recalculateRows();
    return this;
}

unsigned int GridView::getCols() const {
    return cols;
}

GridView* GridView::setCols(unsigned int cols) {
    this->cols = cols;
    recalculateRows();
    return this;
}

float GridView::getWidth() const {
    return width;
}

GridView* GridView::setWidth(float width) {
    this->width = width;
    recalculateRows();
    return this;
}

float GridView::getHeight() const {
    return height;
}

GridView* GridView::setHeight(float height) {
    this->height = height;
    recalculateRows();
    return this;
}

float GridView::getX() const {
    return x;
}

GridView* GridView::setX(float x) {
    this->x = x;
    return this;
}

float GridView::getY() const {
    return y;
}

GridView* GridView::setY(float y) {
    this->y = y;
    return this;
}

void GridView::recalculateRows() {
    _cellWidth = width/cols;
    _cellHeight = height/rows;

    unsigned long element = 0;
    for (const auto &actor : actors) {
        unsigned long insertCol = element%cols;
        unsigned long insertRow = element/cols;
        float paddingX = _cellWidth/2 - actor->getWidth()/2;
        float paddingY = _cellHeight/2 - actor->getHeight()/2;

        actor->setX(insertCol * _cellWidth + paddingX);
        actor->setY(insertRow * _cellHeight + paddingY);

        element++;
    }
}
