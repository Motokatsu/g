/*
 * GraphBar.h
 *
 *  Created on: 2013/02/17
 *      Author: moto
 */

#ifndef GRAPHBAR_H_
#define GRAPHBAR_H_

#include <QScrollBar>

class GraphAxis;

class GraphBar : public QScrollBar
{
public:
    GraphBar(QWidget* aParent, const GraphAxis& aAxis);
    virtual ~GraphBar();

    void refresh();
    double diffCoord() const;

private:
    const GraphAxis& mAxis_;
    bool mRefreshing_;
};

#endif /* GRAPHBAR_H_ */
