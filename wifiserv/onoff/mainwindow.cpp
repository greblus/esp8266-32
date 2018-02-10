#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtNetwork/QNetworkRequest"
#include "QtNetwork/QNetworkReply"
#include "QtNetwork/QNetworkAccessManager"

bool on = false;
QNetworkAccessManager manager;
QString url;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    url = ui->lineEdit->text();
    if (on) {
        QNetworkRequest req(QString("http://"+url+"/gpio/1"));
        QNetworkReply *reply = manager.get(req);
        ui->pushButton->setText(QString("Włącz"));
    } else {
        QNetworkRequest req(QString("http://"+url+"/gpio/0"));
        QNetworkReply *reply = manager.get(req);
        ui->pushButton->setText(QString("Wyłącz"));
    }
    on = !on;
}
