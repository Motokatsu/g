/*
 * GraphGrid.h
 *
 *  Created on: 2013/02/04
 *      Author: moto
 */

#ifndef GRAPHGRID_H_
#define GRAPHGRID_H_

#include <QList>
#include "AbstractLayerable.h"

class GraphAxis;
class GraphGrid : public AbstractLayerable {
public:
    GraphGrid(const QList<GraphAxis*>& aAxisList);
    virtual ~GraphGrid();

    void draw(QPainter& aPainter);
private:
    const QList<GraphAxis*>& mAxisList_;
};

#endif /* GRAPHGRID_H_ */
