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

void SignalWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect upperRect = rect();
    painter.setRenderHint(QPainter::Antialiasing, true);



    int time = 0;
    int xOffset = 10;
    int yOffset = 200;
    int dataSize = cycleData_.size();

    upperRect.setHeight(yOffset + 100);

    upperRect.setWidth(upperRect.width()+dataSize*timestep);

    painter.fillRect(upperRect, Qt::black);

    painter.setPen(Qt::green);

    //int dataWidth = width() - 2 * xOffset;
    //int dataHeight = height() - 2 * yOffset;
    int x1 = xOffset,x2=xOffset,y1 = 0,y2 = 0;
    if (dataSize > 1) {
        double timeStep = timestep; // Use the provided time step value
        painter.drawLine(xOffset,yOffset-200,xOffset + 100,yOffset-200);
        for (int i = 0; i < dataSize; ++i) {
            painter.setPen(Qt::green);
            x1 = x2;
            x2 = x1 + timeStep;

            if(cycleData_[i] == 1){
                y1 = yOffset;
                y2 = yOffset - 100;

                //painter.drawLine(x1, y1, x1 , y2 );
                painter.drawLine(x1, y2, x2 , y2 );
                if((i < dataSize && i>0) && (cycleData_[i-1] == 0)){
                    painter.drawLine(x1,y1,x1,y2);
                }
                painter.setPen(Qt::white);
                painter.drawText(x1,y1+20,QString::number(time) + timeUnit);

            }
            else if(cycleData_[i] == 0){
                y1 = yOffset;
                y2 = yOffset;

                if((i < dataSize && i>0) && (cycleData_[i-1] == 1)){
                    painter.drawLine(x1,y2-100,x1,y1);
                }
                painter.drawLine(x1, y1, x2 , y2 );
                painter.setPen(Qt::white);

                painter.drawText(x1,y1+20,QString::number(time) + timeUnit);

            }
            time = time + timestep;




        }
    }
}
