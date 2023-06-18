#include "signalwidget.h"
#include <QPainter>
#include <QWheelEvent>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qscrollbar.h>


SignalWidget::SignalWidget(QWidget* parent) : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);


    // Create a scroll area and set this widget as its child
    scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(this);

    // Create a layout and set the scroll area as its child
    //QVBoxLayout* layout = new QVBoxLayout(parent);
    //layout->addWidget(scrollArea);
    //setLayout(layout);
    scrollArea->setStyleSheet("background-color: transparent;");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}


void SignalWidget::setData(const QVector<int>& data , int step , QString unit)
{
    cycleData_ = data;
    timestep = step;
    timeUnit = unit;

    update();
}

