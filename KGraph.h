/*
 * KGraph.h
 *
 *  Created on: 2013/02/10
 *      Author: moto
 */

#ifndef KGRAPH_H_
#define KGRAPH_H_

#include <QWidget>
#include <QTimer>
#include "graph.h"

class KGraph : public QWidget {
    Q_OBJECT
public:
    KGraph(QWidget *parent = 0);
    virtual ~KGraph();

    QSize sizeHint();
private slots:
    void updateGraph();
private:
    Graph mGraph_;
    QTimer mTimer_;
};

#endif /* KGRAPH_H_ */
