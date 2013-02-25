/*
 * GraphRange.cpp
 *
 *  Created on: 2013/01/31
 *      Author: moto
 */
#include <qglobal.h>
#include "GraphRange.h"

GraphRange::GraphRange()
: mLower_(0)
, mUpper_(0)
{
}

GraphRange::GraphRange(double aLower, double aUpper)
: mLower_(aLower)
, mUpper_(aUpper)
{
    normalize();
}

GraphRange::GraphRange(const GraphRange& aOther)
: mLower_(aOther.mLower_)
, mUpper_(aOther.mUpper_)
{
}

GraphRange::~GraphRange()
{
}

const GraphRange& GraphRange::operator=(const GraphRange& aOther)
{
    if (this == &aOther)
    {
        return *this;
    }
    mLower_ = aOther.mLower_;
    mUpper_ = aOther.mUpper_;
    return *this;
}

double GraphRange::center() const
{
    return (mUpper_ + mLower_) * 0.5;
}

void GraphRange::normalize()
{
    if (mLower_ > mUpper_)
    {
        qSwap(mLower_, mUpper_);
    }
}

void GraphRange::trans(double aDiff)
{
    mLower_ += aDiff;
    mUpper_ += aDiff;
}

