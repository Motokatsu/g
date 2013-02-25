/*
 * GraphMarker.cpp
 *
 *  Created on: 2013/02/04
 *      Author: moto
 */

#include "GraphMarker.h"

GraphMarker::GraphMarker(const QRect& aAxisRect)
: AbstractLayerable()
, mAxisRect_(aAxisRect)
{
}

GraphMarker::~GraphMarker()
{
}

void GraphMarker::setPoint(const QPointF aPoint)
{
    mPoint_ = aPoint;
}

void GraphMarker::draw(QPainter& aPainter)
{
    aPainter.setPen(QPen(Qt::blue, 0, Qt::DashDotLine));
    aPainter.drawLine(QLineF(mAxisRect_.left(), mPoint_.y(), mAxisRect_.right(), mPoint_.y()));
    aPainter.setPen(QPen(Qt::red, 0, Qt::DashDotLine));
    aPainter.drawLine(QLineF(mPoint_.x(), mAxisRect_.top(), mPoint_.x(), mAxisRect_.bottom()));
}
