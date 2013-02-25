/********************************************************************************
** Form generated from reading UI file 'graph.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPH_H
#define UI_GRAPH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphClass
{
public:

    void setupUi(QWidget *GraphClass)
    {
        if (GraphClass->objectName().isEmpty())
            GraphClass->setObjectName(QString::fromUtf8("GraphClass"));
        GraphClass->resize(519, 300);

        retranslateUi(GraphClass);

        QMetaObject::connectSlotsByName(GraphClass);
    } // setupUi

    void retranslateUi(QWidget *GraphClass)
    {
        GraphClass->setWindowTitle(QApplication::translate("GraphClass", "Graph", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GraphClass: public Ui_GraphClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_H
