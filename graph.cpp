#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
#include "GraphLayer.h"
#include "GraphAxis.h"
#include "GraphGrid.h"
#include "GraphLine.h"
#include "GraphBar.h"
#include "GraphMarker.h"
#include "GraphLabel.h"
#include "KLine.h"
#include "graph.h"

Graph::Graph(QWidget *parent)
: QWidget(parent)
, mPlotArea_(0)
, mHBar_(0)
, mVBar_(0)
, mTitle_("Title")
, mGridX_(0)
, mGridY_(0)
, mDragging_(false)
, mMarker_(0)
, mLabel_(0)
{
    ui.setupUi(this);
    mPaintBuffer_ = QPixmap(size());
    mPlotArea_ = new QFrame(this);
    mPlotArea_->setGeometry(axisRect().adjusted(3, 0, 0, -3));
    mPlotArea_->setFrameStyle(QFrame::Sunken);
    mPlotArea_->setFrameShape(QFrame::Panel);
    mPlotArea_->setLineWidth(2);

    GraphLayer* axisLayer = new GraphLayer();
    GraphAxis* axisX = new GraphAxis(axisRect(), GraphAxis::AT_BOTTOM);
    axisX->setLabel("sec");
    GraphAxis* axisY = new GraphAxis(axisRect(), GraphAxis::AT_LEFT);
    axisY->setLabel("pressure");
    axisX->setLayer(axisLayer);
    axisY->setLayer(axisLayer);
    mAxisXs_.append(axisX);
    mAxisYs_.append(axisY);
    mLayers_.append(axisLayer);

    GraphLayer* gridLayer = new GraphLayer();
    mGridX_ = new GraphGrid(mAxisXs_);
    mGridY_ = new GraphGrid(mAxisYs_);
    mGridX_->setLayer(gridLayer);
    mGridY_->setLayer(gridLayer);
    mLayers_.append(gridLayer);

    GraphLayer* markerLayer = new GraphLayer();
    mMarker_ = new GraphMarker(axisRect());
    mMarker_->setLayer(markerLayer);
    mLayers_.append(markerLayer);

    mHBar_ = new GraphBar(this, *mAxisXs_.first());
    connect(mHBar_, SIGNAL(valueChanged(int)), this, SLOT(hBarValueChanged(int)));

    mVBar_ = new GraphBar(this, *mAxisYs_.first());
    connect(mVBar_, SIGNAL(valueChanged(int)), this, SLOT(vBarValueChanged(int)));

    mLabel_ = new GraphLabel(this, axisRect());
}

Graph::~Graph()
{
    foreach (GraphLayer* layer, mLayers_)
    {
        delete layer;
    }
    delete mLabel_;
    delete mVBar_;
    delete mHBar_;
    delete mMarker_;
    delete mGridX_;
    delete mGridY_;
    foreach (GraphAxis* axisX, mAxisXs_)
    {
        delete axisX;
    }
    foreach (GraphAxis* axisY, mAxisYs_)
    {
        delete axisY;
    }
    foreach (GraphLine* line, mLines_)
    {
        delete line;
    }
}

void Graph::setLine(const KLine& aLine)
{
    if (mLines_.isEmpty())
    {
        GraphLayer* lineLayer = new GraphLayer();
        mAxisYs_.first()->setRange(aLine.max(), aLine.min());
        mAxisYs_.first()->setLabel(aLine.label());
        mAxisXs_.first()->setRange(aLine.data().size()-1, 0);
        mAxisYs_.first()->setupToDraw();
        mAxisXs_.first()->setupToDraw();
        GraphLine* line = new GraphLine(*mAxisXs_.first(), *mAxisYs_.first());
        line->setLine(aLine);
        line->setLayer(lineLayer);
        mLayers_.append(lineLayer);
        mLines_.append(line);
        mLabel_->addLine(*line);
        return;
    }

    foreach (GraphLine* line, mLines_)
    {
        if (line->isSameCategory(aLine))
        {
            // TODO
            return;
        }
    }

    int offset = 0;
    foreach (GraphAxis* axis, mAxisYs_)
    {
        offset += axis->rect().width();
    }
    GraphAxis* axisY = new GraphAxis(axisRect(), GraphAxis::AT_LEFT, offset);
    axisY->setLayer(mAxisYs_.first()->layer());
    GraphLayer* lineLayer = new GraphLayer();
    axisY->setRange(aLine.max(), aLine.min());
    axisY->setLabel(aLine.label());
    axisY->setupToDraw();
    mAxisYs_.append(axisY);
//    mAxisXs_.first()->setRange(aLine.data().size()-1, 0);
    GraphLine* line = new GraphLine(*mAxisXs_.first(), *axisY);
    line->setLine(aLine);
    line->setLayer(lineLayer);
    mLayers_.append(lineLayer);
    mLines_.append(line);
    mLabel_->addLine(*line);
}

void Graph::replot()
{
    qDebug("Graph::replot()");
    mPaintBuffer_.fill(Qt::white);
    QPainter painter;
    painter.begin(&mPaintBuffer_);
    if (!painter.isActive())
    {
        qDebug("Couldn't activate painter.");
        return;
    }
    draw(painter);
    update();
    painter.end();

    mHBar_->refresh();
    mVBar_->refresh();
}

void Graph::paintEvent(QPaintEvent* aEvent)
{
    Q_UNUSED(aEvent);
    QPainter painter(this);

//    painter.drawPixmap(0, 0, mPaintBuffer_);
    foreach (GraphAxis* axisX, mAxisXs_)
    {
        painter.drawPixmap(axisX->rect(), mPaintBuffer_, axisX->rect());
    }
    foreach (GraphAxis* axisY, mAxisYs_)
    {
        painter.drawPixmap(axisY->rect(), mPaintBuffer_, axisY->rect());
    }
    QRect rect = axisRect().adjusted(5, 0, 0, -5);
    painter.drawPixmap(rect, mPaintBuffer_, rect);
//    QPainter plotPainter(mPlotArea_);
//    QRect rect = axisRect().adjusted(5, 0, 0, -5);
//    plotPainter.drawPixmap(rect, mPaintBuffer_, rect);

}

void Graph::resizeEvent(QResizeEvent *aEvent)
{
    qDebug("Graph::resizeEvent()");
    mPaintBuffer_ = QPixmap(aEvent->size());
    foreach (GraphAxis* axisX, mAxisXs_)
    {
        axisX->setAxisRect(axisRect());
    }
    foreach (GraphAxis* axisY, mAxisYs_)
    {
        axisY->setAxisRect(axisRect());
    }
    replot();
}

void Graph::mouseDoubleClickEvent(QMouseEvent* aEvent)
{
    QWidget::mouseDoubleClickEvent(aEvent);
    qDebug("Graph::mouseDoubleClickEvent()");
    double factor = 0.85;
    foreach (GraphAxis* axisX, mAxisXs_)
    {
        axisX->scaleRange(factor, axisX->pixelToCoord(aEvent->pos().x()));
    }
    foreach (GraphAxis* axisY, mAxisYs_)
    {
        axisY->scaleRange(factor, axisY->pixelToCoord(aEvent->pos().y()));
    }
    replot();
}

void Graph::mousePressEvent(QMouseEvent *aEvent)
{
    mDragStart_ = aEvent->pos();
    mDragging_ = true;
    mMarker_->setPoint(aEvent->posF());
    replot();
    QWidget::mouseMoveEvent(aEvent);
}

void Graph::mouseMoveEvent(QMouseEvent *aEvent)
{
    qDebug("Graph::mouseMoveEvent()");
    if (mDragging_)
    {
        foreach (GraphAxis* axisX, mAxisXs_)
        {
            double diffX = axisX->pixelToCoord(mDragStart_.x()) - axisX->pixelToCoord(aEvent->pos().x());
            axisX->transRange(diffX);
        }
        foreach (GraphAxis* axisY, mAxisYs_)
        {
            double diffY = axisY->pixelToCoord(mDragStart_.y()) - axisY->pixelToCoord(aEvent->pos().y());
            axisY->transRange(diffY);
        }
        mMarker_->setPoint(aEvent->posF());
        replot();
        mDragStart_ = aEvent->pos();
    }
    QWidget::mouseMoveEvent(aEvent);
}

void Graph::mouseReleaseEvent(QMouseEvent *aEvent)
{
    mDragging_ = false;
    QWidget::mouseReleaseEvent(aEvent);
}

void Graph::hBarValueChanged(int /*aValue*/)
{
//    double diff = mHBar_->diffCoord();
//    mAxisX_->transRange(diff);
    replot();
}

void Graph::vBarValueChanged(int /*aValue*/)
{
//    double diff = mVBar_->diffCoord();
//    mAxisY_->transRange(diff);
    replot();
}

void Graph::draw(QPainter& aPainter)
{
    foreach (GraphLayer* layer, mLayers_)
    {
        layer->draw(aPainter);
    }

    // draw title:
    if (!mTitle_.isEmpty())
    {
        aPainter.setFont(QFont(font().family(), 14, QFont::Bold));
        aPainter.setPen(Qt::black);
        aPainter.drawText(rect(), Qt::TextDontClip | Qt::AlignHCenter, mTitle_);
      }
}

QRect Graph::axisRect() const
{
    return rect().adjusted(100, 20, -60, -60);
}
