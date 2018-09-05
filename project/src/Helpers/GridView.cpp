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
    recalculateRowSize();
}

GridView *GridView::setRowsAndCols(unsigned int rows, unsigned int cols) {
    this->rows = rows;
    this->cols = cols;
    recalculateRowSize();
    return this;
}

GridView *GridView::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    recalculateRowSize();
    return this;
}

GridView *GridView::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    return this;
}

GridView *GridView::addActor(Actor *actor) {
    if(actor != nullptr) {
        unsigned long elements = actors.size();
        unsigned long insertCol = elements%cols;
        unsigned long insertRow = elements/cols;

        if (insertRow < rows) {
            actor->setX(insertCol * _cellWidth);
            actor->setY(insertRow * _cellHeight);

            actors.push_back(actor);
        }
    }
    return this;
}

unsigned int GridView::getRows() const {
    return rows;
}

GridView* GridView::setRows(unsigned int rows) {
    this->rows = rows;
    recalculateRowSize();
    return this;
}

unsigned int GridView::getCols() const {
    return cols;
}

GridView* GridView::setCols(unsigned int cols) {
    this->cols = cols;
    recalculateRowSize();
    return this;
}

float GridView::getWidth() const {
    return width;
}

GridView* GridView::setWidth(float width) {
    this->width = width;
    recalculateRowSize();
    return this;
}

float GridView::getHeight() const {
    return height;
}

GridView* GridView::setHeight(float height) {
    this->height = height;
    recalculateRowSize();
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

void GridView::recalculateRowSize() {
    _cellWidth = width/cols;
    _cellHeight = height/rows;
}
