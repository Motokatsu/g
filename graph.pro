TEMPLATE = app
TARGET = Graph
QT += core \
    gui
HEADERS += GraphLabel.h \
    GraphMarker.h \
    KLine.h \
    KGraph.h \
    GraphLine.h \
    GraphGrid.h \
    GraphRange.h \
    GraphLayer.h \
    GraphAxis.h \
    GraphBar.h \
    AbstractLayerable.h \
    graph.h
SOURCES += GraphLabel.cpp \
    GraphMarker.cpp \
    KLine.cpp \
    KGraph.cpp \
    GraphLine.cpp \
    GraphGrid.cpp \
    GraphRange.cpp \
    GraphLayer.cpp \
    GraphAxis.cpp \
    GraphBar.cpp \
    AbstractLayerable.cpp \
    main.cpp \
    graph.cpp
FORMS += graph.ui
RESOURCES += 
