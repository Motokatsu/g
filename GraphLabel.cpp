/*
 * GraphLabel.cpp
 *
 *  Created on: 2013/02/04
 *      Author: moto
 */
#include <QVBoxLayout>
#include <QLabel>
#include "GraphLine.h"
#include "GraphLabel.h"

GraphLabel::GraphLabel(QWidget* aParent, const QRect& aAxisRect)
: QWidget(aParent)
, mAxisRect_(aAxisRect)
, mLayout_(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mLayout_ = new QVBoxLayout(this);
    setLayout(mLayout_);
}

GraphLabel::~GraphLabel()
{
}

void GraphLabel::addLine(const GraphLine& aLine)
{
    QLabel* label = new QLabel();
    label->setText(aLine.label());
    mLayout_->addWidget(label);
    mLineMap_.insert(&aLine, label);

    move(mAxisRect_.right(), (mAxisRect_.top() + mAxisRect_.height()/2));
}
