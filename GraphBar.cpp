/*
 * GraphBar.cpp
 *
 *  Created on: 2013/02/17
 *      Author: moto
 */

#include "GraphAxis.h"
#include "GraphBar.h"

GraphBar::GraphBar(QWidget* aParent, const GraphAxis& aAxis)
: QScrollBar(aAxis.orientation(), aParent)
, mAxis_(aAxis)
, mRefreshing_(false)
{
    if (Qt::Horizontal == mAxis_.orientation())
    {
        setGeometry(mAxis_.axisRect().left(), mAxis_.axisRect().bottom()+40, mAxis_.axisRect().width(), 15);
    }
    else
    {
        setGeometry(mAxis_.axisRect().right()+10, mAxis_.axisRect().top(), 15, mAxis_.axisRect().height());
    }
}

GraphBar::~GraphBar() {
    // TODO Auto-generated destructor stub
}

void GraphBar::refresh()
{
    int max = qRound(mAxis_.origRange().size()/mAxis_.subTickStep());
    int min = qRound(mAxis_.range().size()/mAxis_.subTickStep());
    setVisible((max != min));
    if (!isVisible())
    {
        return;
    }

    int value = qRound((mAxis_.range().upper()-mAxis_.origRange().lower())/mAxis_.subTickStep());
    if (Qt::Horizontal != mAxis_.orientation())
    {
        value = max - value + min;
    }
    blockSignals(true);
    setMaximum(max);
    setMinimum(min);
    setValue(value);
    blockSignals(false);
}

double GraphBar::diffCoord() const
{
    double preValue = (mAxis_.range().upper()-mAxis_.origRange().lower())/mAxis_.subTickStep();
    if (Qt::Horizontal == mAxis_.orientation())
    {
        return ((double)value() - preValue)*mAxis_.subTickStep();
    }
    else
    {
        preValue = maximum() - preValue + minimum();
        return (preValue - (double)value())*mAxis_.subTickStep();
    }
}
