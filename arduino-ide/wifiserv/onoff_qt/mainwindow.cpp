#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtNetwork/QNetworkRequest"
#include "QtNetwork/QNetworkReply"
#include "QtNetwork/QNetworkAccessManager"

bool on = true;
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

void MainWindow::on_off_button_clicked()
{
    QNetworkRequest req;
    url = ui->address->text();
    if (on)
        req = QNetworkRequest(QString("http://"+url+"/gpio/0"));
    else
        req = QNetworkRequest(QString("http://"+url+"/gpio/1"));
    on = !on;
    QNetworkReply *reply = manager.get(req);
}

void MainWindow::on_timer_button_clicked()
{
    url = ui->address->text();
    QString tms = ui->timeout->text();
    int tm = tms.toInt();
    QNetworkRequest req(QString("http://%1/timer/%2&").arg(url).arg(tm));
    QNetworkReply *reply = manager.get(req);

}
