#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    multi_process.parse_xml("E:/workstation/GitHub/process.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startPushButton_clicked()
{
//    for(int i=0; i<this->parse_xml->assembly_line_handle_list.length(); i++)
//    {
//        this->parse_xml->assembly_line_handle_list.at(i)->start();
//    }
     RSHD rshd = -1;
     Pos pos;
     pos.x = -118.96865240727046;
     pos.y = -200.5580682043296;
     pos.z = 388.84898008734875;

//         //登录服务器
//         if (example_login(rshd, "192.168.1.14", 8899))
//         {
//             //启动机械臂(必须连接真实机械臂）
//             example_robotStartup(rshd);

//         }

    //首先获取当前路点信息
    aubo_robot_namespace::wayPoint_S wayPoint;

    //逆解位置信息
    aubo_robot_namespace::wayPoint_S targetPoint;


//    if (RS_SUCC == rs_get_current_waypoint(rshd, &wayPoint))
//    {
        //参考当前姿态逆解得到六个关节角
        if (RS_SUCC == rs_inverse_kin(rshd, wayPoint.jointpos, &pos, &wayPoint.orientation, &targetPoint))
        {

            for(int i=0; i<6; i++)
            {
                qDebug() << "joint:" << i << "--"<< targetPoint.jointpos[i];
            }

        }


//    }

}

void MainWindow::on_label_linkActivated(const QString &link)
{
//    int state = link.toInt();
//    this->parse_xml->assembly_line_handle_list.at(0)->set_state(state);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
//    int state = arg1.toInt();
//    this->parse_xml->assembly_line_handle_list.at(0)->set_state(state);
}
