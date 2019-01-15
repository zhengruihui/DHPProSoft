#include "robot.h"
#include "rsdef.h"
#include "QDebug"
#include "example.h"


#define ROBOT_ADDR "192.168.1.14"
#define ROBOT_PORT 8899


Robot::Robot(QList<AssemblyLine*> assembly_line)
{
    this->assembly_line_list = assembly_line;


//    //登录服务器
//    if (example_login(this->g_rshd, ROBOT_ADDR, ROBOT_PORT))
//    {
//        //启动机械臂(必须连接真实机械臂）
//        example_robotStartup(this->g_rshd);
//        this->start();

//    }
     this->start();

}

//void Robot::move_joint(float joint[])
//{

//}

//void Robot::move_line(float axis[])
//{

//}

void Robot::run()
{
    //登录服务器
    if (example_login(this->g_rshd, ROBOT_ADDR, ROBOT_PORT))
    {
        //启动机械臂(必须连接真实机械臂）
        example_robotStartup(this->g_rshd);

    }
    while(true)
    {
        for(int i=0; i<this->assembly_line_list.length(); i++)
        {
            this->assembly_line_list.at(i)->acquire();
            if(this->assembly_line_list.at(i)->share_memory.IPC == SET)
            {
                if(this->assembly_line_list.at(i)->share_memory.device == "robot")
                {
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_joint")
                    {
                       qDebug() << "robot: move_joint" << i;
                       rs_move_joint(this->g_rshd, this->assembly_line_list.at(i)->share_memory.joint);
                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_line")
                    {
                       qDebug() << "robot: move_line" << i;
                       move_line(this->g_rshd, &this->assembly_line_list.at(i)->share_memory.pos, this->assembly_line_list.at(i)->share_memory.joint[5]);
                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_pos")
                    {
                       qDebug() << "robot: move_pos" << i;
                       move_pos(this->g_rshd, &this->assembly_line_list.at(i)->share_memory.pos);
                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_arc")
                    {
                       qDebug() << "robot: move_arc" << i;
                       move_arc(this->g_rshd, &this->assembly_line_list.at(i)->share_memory.pos, this->assembly_line_list.at(i)->share_memory.r, this->assembly_line_list.at(i)->share_memory.times);
                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "set_speed")
                    {
                       qDebug() << "robot: set_speed" << i;
                       set_speed(this->g_rshd, this->assembly_line_list.at(i)->share_memory.speed);
                    }
                }
                this->assembly_line_list.at(i)->share_memory.IPC = CLEAR;

            }

            this->assembly_line_list.at(i)->release();
        }
    }
}
