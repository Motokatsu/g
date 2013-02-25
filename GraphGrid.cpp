/*
 * GraphGrid.cpp
 *
 *  Created on: 2013/02/04
 *      Author: moto
 */

#include "GraphAxis.h"
#include "GraphGrid.h"

GraphGrid::GraphGrid(const QList<GraphAxis*>& aAxisList)
: AbstractLayerable()
, mAxisList_(aAxisList)
{
}

GraphGrid::~GraphGrid()
{
}

void GraphGrid::draw(QPainter& aPainter)
{
    aPainter.setPen(QPen(QColor(200,200,200), 0, Qt::DotLine));
    foreach (GraphAxis* axis, mAxisList_)
    {
        for (int i=axis->lowTick(); i<=axis->highTick(); ++i)
        {
            double t = axis->coordToPixel(axis->tickVector().at(i)); // x
            if (Qt::Horizontal == axis->orientation())
            {
                aPainter.drawLine(QLineF(t, axis->axisRect().bottom(), t, axis->axisRect().top()));
            }
            else
            {
                aPainter.drawLine(QLineF(axis->axisRect().left(), t, axis->axisRect().right(), t));
            }
        }
    }
}
