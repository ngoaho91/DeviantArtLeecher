#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtdeviantleecher.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QtDeviantLeecher* leecher;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_btnLeechNow_clicked();
    void artDetected(QString url);
    void imageDetected(QString url);
    void imageDownloaded(QString filename);
    void leechFinished();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
