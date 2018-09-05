//
// Created by foidbgen on 9/2/18.
//

#include "GridView.h"

GridView *GridView::setRowsAndCols(unsigned int rows, unsigned int cols) {
    this->rows = rows;
    this->cols = cols;
    return this;
}

GridView *GridView::setSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    return this;
}

GridView *GridView::setPosition(unsigned int x, unsigned int y) {
    this->x = x;
    this->y = y;
    return this;
}

GridView *GridView::addActor(Actor *actor) {
    if(actor != nullptr)
        actors.push_back(actor);
    return this;
}

unsigned int GridView::getRows() const {
    return rows;
}

GridView* GridView::setRows(unsigned int rows) {
    this->rows = rows;
    return this;
}

unsigned int GridView::getCols() const {
    return cols;
}

GridView* GridView::setCols(unsigned int cols) {
    this->cols = cols;
    return this;
}

unsigned int GridView::getWidth() const {
    return width;
}

GridView* GridView::setWidth(unsigned int width) {
    this->width = width;
    return this;
}

unsigned int GridView::getHeight() const {
    return height;
}

GridView* GridView::setHeight(unsigned int height) {
    this->height = height;
    return this;
}

unsigned int GridView::getX() const {
    return x;
}

GridView* GridView::setX(unsigned int x) {
    this->x = x;
    return this;
}

unsigned int GridView::getY() const {
    return y;
}

GridView* GridView::setY(unsigned int y) {
    this->y = y;
    return this;
}