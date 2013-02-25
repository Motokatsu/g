/*
 * GraphMarker.h
 *
 *  Created on: 2013/02/04
 *      Author: moto
 */

#ifndef GRAPHMARKER_H_
#define GRAPHMARKER_H_

#include <QRect>
#include <QPointF>
#include "AbstractLayerable.h"

class GraphMarker : public AbstractLayerable {
public:
    GraphMarker(const QRect& aAxisRect);
    virtual ~GraphMarker();

    void setPoint(const QPointF aPoint);
    void draw(QPainter& aPainter);
private:
    const QRect mAxisRect_;
    QPointF mPoint_;
};

#endif /* GRAPHMARKER_H_ */
