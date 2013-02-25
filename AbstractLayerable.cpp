/*
 * AbstractLayerable.cpp
 *
 *  Created on: 2013/01/28
 *      Author: moto
 */

#include "GraphLayer.h"
#include "AbstractLayerable.h"

AbstractLayerable::AbstractLayerable()
: mLayer_(0)
{
}

AbstractLayerable::~AbstractLayerable()
{
}

void AbstractLayerable::setLayer(GraphLayer* aLayer)
{
    if (mLayer_)
    {
        mLayer_->removeLayerable(this);
    }
    mLayer_ = aLayer;
    if (mLayer_)
    {
        mLayer_->addLayerable(this);
    }
}

