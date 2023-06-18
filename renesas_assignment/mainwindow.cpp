#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProgressDialog>
#include <QTextStream>
#include <QToolBar>



FileLoaderThread::FileLoaderThread(const QString& filePath, QObject* parent)
    : QThread(parent), filePath_(filePath)
{
}

/*
 * This is the thread that reads the Input file and provides the data in order to paint them in the widget.
 * This has been implemented to handle large files without interrupting the painter.
 * */
void FileLoaderThread::run()
{
    QVector<int> signalData;
    double timeStep = 0.0;
    QString timeUnits;

    QFile file(filePath_);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString line = in.readLine();
        int lineCount = 1;
        while (!line.isNull()) {
            line = line.trimmed();
            if (!line.isEmpty()) {
                QStringList parts = line.split(';');
                if (parts.size() >= 2) {
                    QString keyword = parts[0].trimmed();
                    QString value = parts[1].trimmed();
                    if (keyword == "TIMESTEP") {
                        timeStep = value.toDouble();
                    } else if (keyword == "UNITS") {
                        timeUnits = value;
                    } else if (keyword == "DATA") {
                        while (!in.atEnd()) {
                            line = in.readLine().trimmed();
                            lineCount++;
                            QStringList number;
                            if (line.isEmpty())
                                break;

                            number = line.split(';');        //Split the '0;' or '1;' into the number and the ';'.Then take the number and add it to the QVector signalData

                            signalData.append(number[0].toInt());

                            if (lineCount % 1000 == 0) {
                                emit dataLoaded(signalData, timeStep, timeUnits);       //This is used for the progress bar.Probably obsolete
                                signalData.clear();
                            }
                        }
                    }
                }
            }

            line = in.readLine();
            lineCount++;
        }

        emit dataLoaded(signalData, timeStep, timeUnits);
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    signalWidget_(new SignalWidget(this))
{
    ui->setupUi(this);

    setCentralWidget(signalWidget_);

    QToolBar* toolbar = addToolBar("File");
    QAction* actionImport = toolbar->addAction("Import");
    connect(actionImport, &QAction::triggered, this, &MainWindow::importData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Here we import the data and connect the loader thread with the handleDataLoaded in order to provide the data to the Widget
 *Also there is the progressDialog which its initial cause was to display a progress bar the whole time that the application reads the Input Data file.
 *Probably we do not need it now since we are executing the read and the painint simultaneously.
 * */
void MainWindow::importData()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Import Data File");
    if (!filePath.isEmpty()) {
        FileLoaderThread* loaderThread = new FileLoaderThread(filePath, this);
        connect(loaderThread, &FileLoaderThread::dataLoaded, this, &MainWindow::handleDataLoaded);

        QProgressDialog progressDialog("Loading File...", "Cancel", 0, 0, this);                       //This needs to be redesigned.The progressDialog currently does not work as expected.
        progressDialog.setWindowTitle("Importing Data");
        progressDialog.setWindowModality(Qt::WindowModal);
        progressDialog.setCancelButton(nullptr);
        progressDialog.show();

        connect(loaderThread, &QThread::finished, &progressDialog, &QProgressDialog::reset);
        connect(&progressDialog, &QProgressDialog::canceled, loaderThread, &QThread::requestInterruption);

        loaderThread->start();
    }
}


/*
 * This function takes the data that the thread read from the Input file and hand them over to the widget in order to paint the square waveform datagram
 * */
void MainWindow::handleDataLoaded(const QVector<int>& data, int step, const QString& timeUnits)
{
    signalWidget_->setData(data, step, timeUnits);
    //Here we should call the function that will paint inide the widget and will update accordingly the window-widget
}

