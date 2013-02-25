/*
 * GraphAxis.cpp
 *
 *  Created on: 2013/01/28
 *      Author: moto
 */
#include <qmath.h>
#include <QLineF>
#include "GraphAxis.h"

GraphAxis::GraphAxis(const QRect& aAxisRect, AxisType aAxisType, int aPosOffset)
: AbstractLayerable()
, mAxisRect_()
, mAxisType_(aAxisType)
, mPosOffset_(aPosOffset)
, mOrigRange_(0, 1)
, mRange_(mOrigRange_)
, mTickCount_(4)
, mSubTickCount_(3)
, mOrigin_()
, mLowTick_(0)
, mHighTick_(-1)
, mTickVector_()
, mSubTickVector_()
, mTickVectorLabels_()
, mTickStep_(0.0)
, mLabel_()
, mFont_()
, mTickLabelPadding_(5)
, mTickLabelMargin_(0)
, mLabelMargin_(0)
{
    setAxisRect(aAxisRect);
}

GraphAxis::~GraphAxis() {
    // TODO Auto-generated destructor stub
}

void GraphAxis::setAxisRect(const QRect& aAxisRect)
{
    mAxisRect_ = (Qt::Horizontal == orientation()) ? aAxisRect.adjusted(5, 0, -5, 0) : aAxisRect.adjusted(0, 5, 0, -5);
    mOrigin_ = originPoint();
}

void GraphAxis::setLabel(const QString& aLabel)
{
    mLabel_ = aLabel;
}

void GraphAxis::setRange(double aUpper, double aLower)
{
    mOrigRange_ = GraphRange(aUpper, aLower);
    mRange_ = mOrigRange_;
}

void GraphAxis::draw(QPainter& aPainter)
{
    aPainter.setPen(Qt::black);
    drawBaseLine(aPainter);

    mTickStep_ = mRange_.size() / (double)(mTickCount_ + 1e-10);
    double magnitudeFactor = qPow(10.0, qFloor(qLn(mTickStep_)/qLn(10.0)));
    double tickStepMantissa = mTickStep_ / magnitudeFactor;
    if (tickStepMantissa < 5)
    {
        // round digit after decimal point to 0.5
        mTickStep_ = (int)(tickStepMantissa*2)/2.0*magnitudeFactor;
    }
    else
    {
        // round to first digit in multiples of 2
        mTickStep_ = (int)((tickStepMantissa/10.0)*5)/5.0*10*magnitudeFactor;
    }
    int firstStep = floor(mRange_.lower()/mTickStep_);
    int lastStep = ceil((mRange_.upper())/mTickStep_);
    int tickcount = lastStep - firstStep+1;
    if (tickcount < 0) tickcount = 0;
    mTickVector_.resize(tickcount);
    for (int i = 0; i < tickcount; ++i)
    {
        mTickVector_[i] = (firstStep+i)*mTickStep_;
    }

    mLowTick_ = 0;
    for (int i = 0; i < mTickVector_.size(); i++)
    {
        mLowTick_ = i;
        if (mTickVector_.at(i) >= mRange_.lower())
        {
            break;
        }
    }
    mHighTick_ = -1;
    for (int i = mTickVector_.size()-1; i >= 0; i--)
    {
        mHighTick_ = i;
        if (mTickVector_.at(i) <= mRange_.upper())
        {
            break;
        }
    }

    mSubTickVector_.resize((mTickVector_.size()-1)*mSubTickCount_);
    int subTickIndex = 0;
    bool done = false;
    for (int i = 1; i < mTickVector_.size(); i++)
    {
        double subTickStep = (mTickVector_.at(i) - mTickVector_.at(i-1)) / (double)(mSubTickCount_+1);
        for (int k=1; k<=mSubTickCount_; ++k)
        {
            double subTickPosition = mTickVector_.at(i-1) + k*subTickStep;
            if (subTickPosition < mRange_.lower())
                continue;
            if (subTickPosition > mRange_.upper())
            {
                done = true;
                break;
            }
            mSubTickVector_[subTickIndex] = subTickPosition;
            subTickIndex++;
        }
        if (done) break;
    }
    mSubTickVector_.resize(subTickIndex);

    drawTickLine(aPainter);

    mTickVectorLabels_.resize(mTickVector_.size());
    for (int i = 0; i < mTickVector_.size(); i++)
    {
        mTickVectorLabels_[i] = QString::number(mTickVector_.at(i), 'g', 6);
    }
    drawTickLabel(aPainter);
}

double GraphAxis::coordToPixel(double aValue) const
{
    if (Qt::Horizontal == orientation())
    {
        return (aValue-mRange_.lower())/mRange_.size()*mAxisRect_.width()+mAxisRect_.left();
    }
    else
    {
        return (mRange_.lower()-aValue)/mRange_.size()*mAxisRect_.height()+mAxisRect_.bottom();
    }
}

double GraphAxis::pixelToCoord(double aValue) const
{
    if (Qt::Horizontal == orientation())
    {
        return (aValue-mAxisRect_.left())/(double)mAxisRect_.width()*mRange_.size()+mRange_.lower();
    }
    else
    {
        return (mAxisRect_.bottom()-aValue)/(double)mAxisRect_.height()*mRange_.size()+mRange_.lower();
    }
}

void GraphAxis::scaleRange(double aFactor, double aCenter)
{
    static const double MIN_RANGE = 1e-280;
    static const double MAX_RANGE = 1e280;
    double lower = (mRange_.lower()-aCenter)*aFactor + aCenter;
    double upper = (mRange_.upper()-aCenter)*aFactor + aCenter;
    if (!(lower > -MAX_RANGE && upper < MAX_RANGE && qAbs(lower-upper) > MIN_RANGE && qAbs(lower-upper) < MAX_RANGE))
    {
        return;
    }
    GraphRange newRange(lower, upper);
    mRange_ = newRange;
}

void GraphAxis::transRange(double aDiff)
{
    mRange_.trans(aDiff);
}

QPoint GraphAxis::originPoint() const
{
    switch (mAxisType_)
    {
    case AT_BOTTOM: return mAxisRect_.bottomLeft() + QPoint(0, mPosOffset_);
    case AT_LEFT: return mAxisRect_.bottomLeft() + QPoint(-mPosOffset_, 0);
    default:
        qDebug("GraphAxis::origin() error");
        return QPoint();
    }
}

void GraphAxis::setupToDraw()
{
    if (Qt::Horizontal == orientation())
    {
        mRect_ = QRect(mOrigin_, mOrigin_ + QPoint(mAxisRect_.width(), 0));
    }
    else
    {
        mRect_ = QRect(mOrigin_ + QPoint(0, -mAxisRect_.height()), mOrigin_);
    }

    mTickStep_ = mRange_.size() / (double)(mTickCount_ + 1e-10);
    double magnitudeFactor = qPow(10.0, qFloor(qLn(mTickStep_)/qLn(10.0)));
    double tickStepMantissa = mTickStep_ / magnitudeFactor;
    if (tickStepMantissa < 5)
    {
        // round digit after decimal point to 0.5
        mTickStep_ = (int)(tickStepMantissa*2)/2.0*magnitudeFactor;
    }
    else
    {
        // round to first digit in multiples of 2
        mTickStep_ = (int)((tickStepMantissa/10.0)*5)/5.0*10*magnitudeFactor;
    }
    int firstStep = floor(mRange_.lower()/mTickStep_);
    int lastStep = ceil((mRange_.upper())/mTickStep_);
    int tickcount = lastStep - firstStep+1;
    if (tickcount < 0) tickcount = 0;
    mTickVector_.resize(tickcount);
    for (int i = 0; i < tickcount; ++i)
    {
        mTickVector_[i] = (firstStep+i)*mTickStep_;
    }

    mLowTick_ = 0;
    for (int i = 0; i < mTickVector_.size(); i++)
    {
        mLowTick_ = i;
        if (mTickVector_.at(i) >= mRange_.lower())
        {
            break;
        }
    }
    mHighTick_ = -1;
    for (int i = mTickVector_.size()-1; i >= 0; i--)
    {
        mHighTick_ = i;
        if (mTickVector_.at(i) <= mRange_.upper())
        {
            break;
        }
    }

    mSubTickVector_.resize((mTickVector_.size()-1)*mSubTickCount_);
    int subTickIndex = 0;
    bool done = false;
    for (int i = 1; i < mTickVector_.size(); i++)
    {
        double subTickStep = (mTickVector_.at(i) - mTickVector_.at(i-1)) / (double)(mSubTickCount_+1);
        for (int k=1; k<=mSubTickCount_; ++k)
        {
            double subTickPosition = mTickVector_.at(i-1) + k*subTickStep;
            if (subTickPosition < mRange_.lower())
                continue;
            if (subTickPosition > mRange_.upper())
            {
                done = true;
                break;
            }
            mSubTickVector_[subTickIndex] = subTickPosition;
            subTickIndex++;
        }
        if (done) break;
    }
    mSubTickVector_.resize(subTickIndex);

//    drawTickLine(aPainter);

    mTickVectorLabels_.resize(mTickVector_.size());
    for (int i = 0; i < mTickVector_.size(); i++)
    {
        mTickVectorLabels_[i] = QString::number(mTickVector_.at(i), 'g', 6);
    }

    //    drawTickLabel(aPainter);

    QFont bugFixFont(mFont_);
    bugFixFont.setPointSizeF(bugFixFont.pointSizeF()+0.05);

    mTickLabelMargin_ = 0;
    QRect tickMaxBounds;
    for (int i = mLowTick_; i <= mHighTick_; i++)
    {
        QString text = mTickVectorLabels_.at(i);
        QFontMetrics fontMetrics(bugFixFont);
        QRect tickBounds = fontMetrics.boundingRect(0, 0, 0, 0, Qt::TextDontClip | Qt::AlignCenter, text);
        if (Qt::Horizontal == orientation())
        {
            if (mTickLabelMargin_ < tickBounds.height())
            {
                mTickLabelMargin_ = tickBounds.height();
                tickMaxBounds = tickBounds;
            }
        }
        else
        {
            if (mTickLabelMargin_ < tickBounds.width())
            {
                mTickLabelMargin_ = tickBounds.width();
                tickMaxBounds = tickBounds;
            }
        }
    }

    mLabelMargin_ = 0;
    if (!mLabel_.isEmpty())
    {
        QFontMetrics fontMetrics(mFont_);
        QRect labelBounds = fontMetrics.boundingRect(0, 0, 0, 0, Qt::TextDontClip, mLabel_);
        mLabelMargin_ = labelBounds.height();
    }

    if (Qt::Horizontal == orientation())
    {
        mRect_.adjust(-tickMaxBounds.width()/2, 0, tickMaxBounds.width()/2, mTickLabelPadding_+mTickLabelMargin_+mLabelMargin_);
    }
    else
    {
        mRect_.adjust(-(mTickLabelPadding_+mTickLabelMargin_+mLabelMargin_), -tickMaxBounds.height()/2, 0, tickMaxBounds.height()/2);
    }

}

void GraphAxis::drawBaseLine(QPainter& aPainter)
{
    if (Qt::Horizontal == orientation())
    {
        mRect_ = QRect(mOrigin_, mOrigin_ + QPoint(mAxisRect_.width(), 0));
        aPainter.drawLine(QLineF(mOrigin_, mOrigin_ + QPointF(mAxisRect_.width(), 0)));
    }
    else
    {
        mRect_ = QRect(mOrigin_ + QPoint(0, -mAxisRect_.height()), mOrigin_);
        aPainter.drawLine(QLineF(mOrigin_, mOrigin_ + QPointF(0, -mAxisRect_.height())));
    }
}

void GraphAxis::drawTickLine(QPainter& aPainter)
{
    int tickDir = (mAxisType_ == AT_BOTTOM || mAxisType_ == AT_RIGHT) ? 1 : -1;
    int tickLengthIn = 5;
    int tickLengthOut = 0;
    for (int i = mLowTick_; i <= mHighTick_; ++i)
    {
        double t = coordToPixel(mTickVector_.at(i));
        if (Qt::Horizontal == orientation())
        {
            aPainter.drawLine(QLineF(t, mOrigin_.y()-tickLengthOut*tickDir, t, mOrigin_.y()+tickLengthIn*tickDir));
        }
        else
        {
            aPainter.drawLine(QLineF(mOrigin_.x()-tickLengthOut*tickDir, t, mOrigin_.x()+tickLengthIn*tickDir, t));
        }
    }

    int subTickLengthIn = 2;
    int subTickLengthOut = 0;
    for (int i = 0; i < mSubTickVector_.size(); i++)
    {
        if (Qt::Horizontal == orientation())
        {
            double t = (mSubTickVector_.at(i)-mRange_.lower())/mRange_.size()*mAxisRect_.width()+mAxisRect_.left();
            aPainter.drawLine(QLineF(t, mOrigin_.y()-subTickLengthOut*tickDir, t, mOrigin_.y()+subTickLengthIn*tickDir));
        }
        else
        {
            double t = (mSubTickVector_.at(i)-mRange_.lower())/mRange_.size()*(-mAxisRect_.height())+mAxisRect_.bottom();
            aPainter.drawLine(QLineF(mOrigin_.x()-subTickLengthOut*tickDir, t, mOrigin_.x()+subTickLengthIn*tickDir, t));
        }
    }
}

void GraphAxis::drawTickLabel(QPainter& aPainter)
{
    int margin = 0;
    int tickLabelPadding = 5;
    QFont bugFixFont(mFont_);
    bugFixFont.setPointSizeF(bugFixFont.pointSizeF()+0.05);
    QRect tickMaxBounds;

    margin += tickLabelPadding;
    for (int i = mLowTick_; i <= mHighTick_; i++)
    {
        QString text = mTickVectorLabels_.at(i);
        QFontMetrics fontMetrics(bugFixFont);
        QRect tickBounds = fontMetrics.boundingRect(0, 0, 0, 0, Qt::TextDontClip | Qt::AlignCenter, text);
        if (Qt::Horizontal == orientation())
        {
            if (tickMaxBounds.height() < tickBounds.height())
            {
                tickMaxBounds = tickBounds;
            }
            double t = (mTickVector_.at(i)-mRange_.lower())/mRange_.size()*mAxisRect_.width()+mAxisRect_.left();
            aPainter.drawText(t, mOrigin_.y()+margin, 0, tickBounds.height(), Qt::TextDontClip | Qt::AlignCenter, text);
        }
        else
        {
            if (tickMaxBounds.width() < tickBounds.width())
            {
                tickMaxBounds = tickBounds;
            }
            double t = (mTickVector_.at(i)-mRange_.lower())/mRange_.size()*(-mAxisRect_.height())+mAxisRect_.bottom();
            aPainter.drawText(mOrigin_.x()-margin, t, -tickBounds.width(), 0, Qt::TextDontClip | Qt::AlignCenter, text);
        }
    }

    if (!mLabel_.isEmpty())
    {
        QRect labelBounds = aPainter.fontMetrics().boundingRect(0, 0, 0, 0, Qt::TextDontClip, mLabel_);
        if (Qt::Horizontal == orientation())
        {
            margin += tickMaxBounds.height();
            aPainter.drawText(mOrigin_.x(), mOrigin_.y()+margin, mAxisRect_.width(), labelBounds.height(), Qt::TextDontClip | Qt::AlignCenter, mLabel_);
        }
        else
        {
            margin += tickMaxBounds.width();
            QTransform oldTransform = aPainter.transform();
            aPainter.translate((mOrigin_.x()-margin-labelBounds.height()), mOrigin_.y());
            aPainter.rotate(-90);
            aPainter.drawText(0, 0, mAxisRect_.height(), labelBounds.height(), Qt::TextDontClip | Qt::AlignCenter, mLabel_);
            aPainter.setTransform(oldTransform);
        }
        margin += labelBounds.height();
    }

    if (Qt::Horizontal == orientation())
    {
        mRect_.adjust(-tickMaxBounds.width()/2, 0, tickMaxBounds.width()/2, margin);
    }
    else
    {
        mRect_.adjust(-margin, -tickMaxBounds.height()/2, 0, tickMaxBounds.height()/2);
    }
}

Qt::Orientation GraphAxis::orientation() const
{
    return (mAxisType_ == AT_BOTTOM || mAxisType_ == AT_TOP) ? Qt::Horizontal : Qt::Vertical;
}
