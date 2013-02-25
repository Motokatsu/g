/*
 * KLine.cpp
 *
 *  Created on: 2013/02/17
 *      Author: moto
 */

#include "KLine.h"

KLine::KLine() {
    // TODO Auto-generated constructor stub

}

KLine::KLine(const QVector<double>& aData, double aConvert, double aMax, double aMin, const QString& aLabel, const QString& aUnit)
: mData_(aData)
, mConvert_(aConvert)
, mMax_(aMax)
, mMin_(aMin)
, mLabel_(aLabel)
, mUnit_(aUnit)
{
}

KLine::~KLine() {
    // TODO Auto-generated destructor stub
}

