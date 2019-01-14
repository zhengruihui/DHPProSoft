#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->parse_xml = new ParseXml("C:/Users/zhegruihui/Documents/GitHub/process.xml");
    qDebug() << "helloworld";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startPushButton_clicked()
{
    for(int i=0; i<this->parse_xml->assembly_line_handle_list.length(); i++)
    {
        this->parse_xml->assembly_line_handle_list.at(i)->start();
    }
}

void MainWindow::on_label_linkActivated(const QString &link)
{
    int state = link.toInt();
    this->parse_xml->assembly_line_handle_list.at(0)->set_state(state);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    int state = arg1.toInt();
    this->parse_xml->assembly_line_handle_list.at(0)->set_state(state);
}
