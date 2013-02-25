/*
 * GraphLine.h
 *
 *  Created on: 2013/02/04
 *      Author: moto
 */

#ifndef GRAPHLINE_H_
#define GRAPHLINE_H_

#include <QMap>
#include "AbstractLayerable.h"
#include "KLine.h"

class GraphAxis;
class GraphLine : public AbstractLayerable {
public:
    GraphLine(const GraphAxis& aAxisX, const GraphAxis& aAxisY);
    virtual ~GraphLine();

    void setLine(const KLine& aLine);
    void draw(QPainter& aPainter);
    bool isSameCategory(const KLine& aLine) const;
    QString label() const { return mLine_.label();}
private:
    const GraphAxis& mAxisX_;
    const GraphAxis& mAxisY_;
//    QMap<double, double> mData_;
    KLine mLine_;
};

#endif /* GRAPHLINE_H_ */
