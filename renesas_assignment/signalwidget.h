#ifndef SIGNALWIDGET_H
#define SIGNALWIDGET_H

#include <QWidget>
#include <qscrollarea.h>

class SignalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignalWidget(QWidget* parent = nullptr);
    void setData(const QVector<int>& data , int step,QString timeUnits);

private:
    QScrollArea* scrollArea;
    QVector<int> cycleData_;
    int timestep;
    QString timeUnit;
    qreal scaleFactor;
    QPoint lastMousePos;
    bool isMousePressed;
    qreal zoomFactor;
    void zoom(int delta);
    bool isDragging;
    int dragStartX;
    int dragX;

protected:
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif // SIGNALWIDGET_H
