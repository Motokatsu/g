/*
 * GraphLine.cpp
 *
 *  Created on: 2013/02/04
 *      Author: moto
 */
#include <qmath.h>
#include "GraphAxis.h"
#include "GraphLine.h"

GraphLine::GraphLine(const GraphAxis& aAxisX, const GraphAxis& aAxisY)
: AbstractLayerable()
, mAxisX_(aAxisX)
, mAxisY_(aAxisY)
, mLine_()
{
//    for (int i = 0; i < 10; i++)
//    {
//        mData_.insert(i, i);
//    }
}

GraphLine::~GraphLine()
{
}

void GraphLine::setLine(const KLine& aLine)
{
    mLine_ = aLine;
}

void GraphLine::draw(QPainter& aPainter)
{
    /*
    QMap<double, double>::const_iterator lower = mData_.lowerBound(mAxisX_.range().lower());
    QMap<double, double>::const_iterator upper = mData_.lowerBound(mAxisX_.range().upper());
    lower = (lower != mData_.constBegin()) ? lower - 1 : lower;
    upper = (upper == mData_.constEnd()) ? upper - 1 : upper;

    int count = 1;
    QMap<double, double>::const_iterator it = lower;
    while (it != upper)
    {
        ++count;
        ++it;
    }
    */
    if (mLine_.data().size()-1 < mAxisX_.range().lower())
    {
        return;
    }
    int lower = (mAxisX_.range().lower() < 1) ? 0 : qFloor(mAxisX_.range().lower());
    int upper = (mLine_.data().size()-1 < mAxisX_.range().upper()) ? mLine_.data().size()-1: qCeil(mAxisX_.range().upper());
    int count = upper - lower + 1;
    qDebug("lower=%d upper=%d count=%d", lower, upper, count);
    QVector<QPointF> lineData(count);
    /*
    QMap<double, double>::const_iterator upperEnd = upper + 1;
    it = lower;
    int i = 0;
    while (it != upperEnd)
    {
        lineData[i].setX(mAxisX_.coordToPixel(it.key()));
        lineData[i].setY(mAxisY_.coordToPixel(it.value()));
        ++i;
        ++it;
    }
    */
    for (int i = 0, k = lower; k <= upper; i++, k++)
    {
        lineData[i].setX(mAxisX_.coordToPixel(k));
        lineData[i].setY(mAxisY_.coordToPixel(mLine_.data()[k]));
    }

//    if (upper != mData_.begin())
//    {
//        QMap<double, double>::const_iterator end = upper - 1;
//        lineData[i].setX(mAxisX_.coordToPixel(mAxisX_.range().upper()));
//        lineData[i].setY(mAxisY_.coordToPixel(end.value()));
//        i++;
//    }
//    lineData.resize(i);

    aPainter.setClipRect(mAxisX_.axisRect() | mAxisY_.axisRect());
    aPainter.setPen(QPen(Qt::blue));
    aPainter.setBrush(Qt::NoBrush);
//    aPainter.drawPolygon(QPolygonF(lineData));
    for (int i = 1; i < lineData.size(); i++)
    {
        qDebug("x=%f y=%f", lineData[i].x(), lineData[i].y());
        aPainter.drawLine(lineData[i-1], lineData[i]);
    }
}

bool GraphLine::isSameCategory(const KLine& /*aLine*/) const
{
    return false;
}
