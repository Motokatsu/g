#ifndef GRAPH_H
#define GRAPH_H

#include <QList>
#include <QtGui/QWidget>
#include <QPixmap>
#include "ui_graph.h"

class QPainter;
class QPaintEvent;
class QFrame;
class GraphBar;
class GraphLayer;
class GraphAxis;
class GraphGrid;
class GraphLine;
class GraphMarker;
class GraphLabel;
class KLine;

class Graph : public QWidget
{
    Q_OBJECT

public:
    Graph(QWidget *parent = 0);
    ~Graph();

    void setLine(const KLine& aLine);
    void replot();

protected:
    void paintEvent(QPaintEvent* aEvent);
    void resizeEvent(QResizeEvent *aEvent);
    void mouseDoubleClickEvent(QMouseEvent *aEvent);
    void mousePressEvent(QMouseEvent *aEvent);
    void mouseMoveEvent(QMouseEvent *aEvent);
    void mouseReleaseEvent(QMouseEvent *aEvent);
private slots:
    void hBarValueChanged(int aValue);
    void vBarValueChanged(int aValue);
private:
    void draw(QPainter& aPainter);
    QRect axisRect() const;

private:
    Ui::GraphClass ui;
    QFrame* mPlotArea_;
    GraphBar* mHBar_;
    GraphBar* mVBar_;
    QPixmap mPaintBuffer_;
    QString mTitle_;
    QList<GraphLayer*> mLayers_;
    QList<GraphAxis*> mAxisXs_;
    QList<GraphAxis*> mAxisYs_;
    GraphGrid* mGridX_;
    GraphGrid* mGridY_;
    QList<GraphLine*> mLines_;
    QPoint mDragStart_;
    bool mDragging_;
    GraphMarker* mMarker_;
    GraphLabel* mLabel_;
};

#endif // GRAPH_H
