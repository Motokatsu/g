/*
 * GraphLabel.h
 *
 *  Created on: 2013/02/04
 *      Author: moto
 */

#ifndef GRAPHLABEL_H_
#define GRAPHLABEL_H_

#include <QWidget>

class QVBoxLayout;
class QLabel;
class GraphLine;
class GraphLabel : public QWidget {
public:
    GraphLabel(QWidget* aParent, const QRect& aAxisRect);
    virtual ~GraphLabel();

    void addLine(const GraphLine& aLine);
private:
    QRect mAxisRect_;
    QVBoxLayout* mLayout_;
    QMap<const GraphLine*, QLabel*> mLineMap_;
};

#endif /* GRAPHLABEL_H_ */
