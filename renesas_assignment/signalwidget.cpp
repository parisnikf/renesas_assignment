#include "signalwidget.h"
#include <QPainter>
#include <QWheelEvent>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qscrollbar.h>


SignalWidget::SignalWidget(QWidget* parent) : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    zoomFactor = 1.0;
    isDragging = false;
    dragStartX = 0;

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
    painter.scale(zoomFactor,zoomFactor);
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

void SignalWidget::wheelEvent(QWheelEvent* event)
{    zoom(event->angleDelta().y() / 120); // Adjust the zoom step as desired
}


void SignalWidget::zoom(int delta)
{
    const qreal zoomInFactor = 1.1;
    const qreal zoomOutFactor = -1 / zoomInFactor;
    const qreal zoomStep = 0.05; // Adjust the zooming step as desired

    qreal zoomChange = 0.0;
    if (delta > 0) {
        // Zoom in
        zoomChange = zoomInFactor;
    } else {
        // Zoom out
        zoomChange = zoomOutFactor;
    }

    // Calculate the incremental zoom factor
    qreal zoomFactorIncremental = zoomFactor * (1.0 + zoomChange * zoomStep);

    // Ensure zoom factor stays within a reasonable range
    const qreal minZoomFactor = 0.1;
    const qreal maxZoomFactor = 10.0;
    zoomFactor = qBound(minZoomFactor, zoomFactorIncremental, maxZoomFactor);

    // Trigger a repaint to apply the zoom
    update();
}


void SignalWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        dragStartX = event->pos().x();
    }
}

void SignalWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (isDragging) {
        int deltaX = event->pos().x() - dragStartX;
        dragStartX = event->pos().x();
        scrollArea->horizontalScrollBar()->setValue(scrollArea->horizontalScrollBar()->value() - deltaX);
    }
}

void SignalWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
}



