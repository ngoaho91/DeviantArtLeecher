#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtdeviantleecher.h"
#include <QMessageBox>
#include <QListView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    leecher = new QtDeviantLeecher();
    connect(leecher, SIGNAL(artDetected(QString)),
            this,SLOT(artDetected(QString)));
    connect(leecher, SIGNAL(imageDetected(QString)),
            this,SLOT(imageDetected(QString)));
    connect(leecher, SIGNAL(imageDownloaded(QString)),
            this,SLOT(imageDownloaded(QString)));
    connect(leecher, SIGNAL(leechFinished()),
            this,SLOT(leechFinished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLeechNow_clicked()
{
    leecher->leech(this->ui->txtUsername->text());
    leecher->setSaveFolder(this->ui->txtSaveTo->text());
    this->ui->btnLeechNow->setDisabled(true);
}
void MainWindow::artDetected(QString url)
{
    this->ui->txtArtURL->setText(url);
    this->ui->txtLog->appendPlainText("art detected "+url+"\n");
}

void MainWindow::imageDetected(QString url)
{
    this->ui->txtDownload->setText(url);
    this->ui->txtLog->appendPlainText("image detected "+url+"\n");
}

void MainWindow::imageDownloaded(QString filename)
{
    this->ui->lblImagePreview->setPixmap(QPixmap::fromImage(QImage(filename)));
    this->ui->txtLog->appendPlainText("image downloaded "+filename+"\n");
}

void MainWindow::leechFinished()
{
    this->ui->txtLog->appendPlainText("leech finished\n");
    //QMessageBox::information(this,"Infomation","leech finished",QMessageBox::Ok);
    this->ui->btnLeechNow->setDisabled(false);
}
