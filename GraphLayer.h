/*
 * Layer.h
 *
 *  Created on: 2013/01/28
 *      Author: moto
 */

#ifndef GRAPHLAYER_H_
#define GRAPHLAYER_H_

#include <QList>
#include <QPainter>

class AbstractLayerable;

class GraphLayer {
public:
    GraphLayer();
    virtual ~GraphLayer();

    void addLayerable(AbstractLayerable* aLayerable);
    void removeLayerable(AbstractLayerable* aLayerable);
    void draw(QPainter& aPainter);
private:
    QList<AbstractLayerable*> mLayerables_;
};

#endif /* GRAPHLAYER_H_ */
