/*
 * Layer.cpp
 *
 *  Created on: 2013/01/28
 *      Author: moto
 */

#include "AbstractLayerable.h"
#include "GraphLayer.h"

GraphLayer::GraphLayer() {
    // TODO Auto-generated constructor stub

}

GraphLayer::~GraphLayer() {
    // TODO Auto-generated destructor stub
}

void GraphLayer::addLayerable(AbstractLayerable* aLayerable)
{
    if (aLayerable && !mLayerables_.contains(aLayerable))
    {
        mLayerables_.append(aLayerable);
    }
}

void GraphLayer::removeLayerable(AbstractLayerable* aLayerable)
{
    mLayerables_.removeOne(aLayerable);
}

void GraphLayer::draw(QPainter& aPainter)
{
    foreach (AbstractLayerable* layerable, mLayerables_)
    {
        aPainter.save();
        layerable->draw(aPainter);
        aPainter.restore();
    }
}
