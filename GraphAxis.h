/*
 * GraphAxis.h
 *
 *  Created on: 2013/01/28
 *      Author: moto
 */

#ifndef GRAPHAXIS_H_
#define GRAPHAXIS_H_

#include <QRect>
#include <QVector>
#include <QFont>

#include "AbstractLayerable.h"
#include "GraphRange.h"

class GraphAxis : public AbstractLayerable {
public:
    enum AxisType {
        AT_LEFT,
        AT_RIGHT,
        AT_TOP,
        AT_BOTTOM
    };
    GraphAxis(const QRect& aAxisRect, AxisType aAxisType, int aPosOffset = 0);
    virtual ~GraphAxis();

    void setAxisRect(const QRect& aAxisRect);
    void setLabel(const QString& aLabel);
    void setRange(double aLower, double aUpper);

    const GraphRange& origRange() const { return mOrigRange_;}
    const GraphRange& range() const { return mRange_;}
    const QRect& rect() const { return mRect_;}
    const QRect& axisRect() const { return mAxisRect_;}
    const QVector<double>& tickVector() const { return mTickVector_;}
    int lowTick() const { return mLowTick_;}
    int highTick() const { return mHighTick_;}
    const QVector<double>& subTickVector() const { return mSubTickVector_;}
    double subTickStep() const { return mTickStep_ / (double)(mSubTickCount_ + 1 + 1e-10);}

    void setupToDraw();
    void draw(QPainter& aPainter);
    double coordToPixel(double aValue) const;
    double pixelToCoord(double aValue) const;
    void scaleRange(double aFactor, double aCenter);
    void transRange(double aCoordDiff);
    Qt::Orientation orientation() const;
private:
    QPoint originPoint() const;
    void drawBaseLine(QPainter& aPainter);
    void drawTickLine(QPainter& aPainter);
    void drawTickLabel(QPainter& aPainter);
private:
    QRect mAxisRect_;
    const AxisType mAxisType_;
    int mPosOffset_;
    GraphRange mOrigRange_;
    GraphRange mRange_;
    const int mTickCount_;
    const int mSubTickCount_;
    QPoint mOrigin_;
    int mLowTick_;
    int mHighTick_;
    QVector<double> mTickVector_;
    QVector<double> mSubTickVector_;
    QVector<QString> mTickVectorLabels_;
    double mTickStep_;
    QString mLabel_;
    QRect mRect_;
    QFont mFont_;
    int mTickLabelPadding_;
    int mTickLabelMargin_;
    int mLabelMargin_;
};

#endif /* GRAPHAXIS_H_ */
