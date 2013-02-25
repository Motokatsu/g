/*
 * KGraph.cpp
 *
 *  Created on: 2013/02/10
 *      Author: moto
 */

#include "KLine.h"
#include "KGraph.h"

KGraph::KGraph(QWidget *parent)
: QWidget(parent)
, mGraph_(this)
, mTimer_()
{
    connect(&mTimer_, SIGNAL(timeout()), this, SLOT(updateGraph()));
//    mTimer_.start(1000);
    QVector<double> data;
    data << 10 << 20 << 30 << 40 << 50 << 60 << 70 << 80 << 90;
    KLine line(data, 1, 100, 1, QString("pres"), QString("pres"));
    mGraph_.setLine(line);

    QVector<double> data2;
    data2 << 50 << 40 << 30 << 20 << 10;
    KLine line2(data2, 1, 70, 1, QString("pres2"), QString("pres2"));
    mGraph_.setLine(line2);
}

KGraph::~KGraph() {
}

void KGraph::updateGraph()
{
    qDebug("KGraph::updateGraph()");
}

QSize KGraph::sizeHint()
{
    return QSize(500, 300);
}
