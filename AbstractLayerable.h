/*
 * AbstractLayerable.h
 *
 *  Created on: 2013/01/28
 *      Author: moto
 */

#ifndef ABSTRACTLAYERABLE_H_
#define ABSTRACTLAYERABLE_H_

#include <QPainter>

class GraphLayer;

class AbstractLayerable {
public:
    AbstractLayerable();
    virtual ~AbstractLayerable();

    GraphLayer* layer() { return mLayer_;}
    void setLayer(GraphLayer* aLayer);
    virtual void draw(QPainter& aPainter) = 0;

private:
    GraphLayer* mLayer_;
};

#endif /* ABSTRACTLAYERABLE_H_ */
