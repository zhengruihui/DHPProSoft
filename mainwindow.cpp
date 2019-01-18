#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    multi_process.parse_xml("E:/workstation/GitHub/DHPProSoft/process.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startPushButton_clicked()
{


}

void MainWindow::on_label_linkActivated(const QString &link)
{

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

}
