#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "signalwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FileLoaderThread : public QThread
{
    Q_OBJECT

public:
    explicit FileLoaderThread(const QString& filePath, QObject* parent = nullptr);

signals:
    void dataLoaded(const QVector<int>& data, int step, const QString& timeUnits);

protected:
    void run() override;

private:
    QString filePath_;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    void importData();
    void handleDataLoaded(const QVector<int>& data, int step, const QString& timeUnits);
private:
    Ui::MainWindow* ui;
    SignalWidget* signalWidget_;
};

#endif // MAINWINDOW_H
