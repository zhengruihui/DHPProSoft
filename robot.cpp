#include "robot.h"
#include "rsdef.h"
#include <QDebug>
#include "example.h"


#define ROBOT_ADDR "192.168.1.14"
#define ROBOT_PORT 8899


Robot::Robot(QList<AssemblyLine*> assembly_line)
{
    this->assembly_line_list = assembly_line;
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
                       qDebug() << "robot: move_joint:" << i;
                       rs_move_joint(this->g_rshd, this->assembly_line_list.at(i)->share_memory.joint);
                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_line")
                    {
                       qDebug() << "robot: move_line:" << i;
                       move_line(this->g_rshd, &this->assembly_line_list.at(i)->share_memory.pos);
                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_pos")
                    {
                       qDebug() << "robot: move_pos:" << i;
                       move_pos(this->g_rshd, &this->assembly_line_list.at(i)->share_memory.pos);
                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_arc")
                    {
                       qDebug() << "robot: move_arc:" << i;
                       move_arc(this->g_rshd, &this->assembly_line_list.at(i)->share_memory.pos, this->assembly_line_list.at(i)->share_memory.r, this->assembly_line_list.at(i)->share_memory.times);
                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "set_speed")
                    {
                       qDebug() << "robot: set_speed:" << i;
                       set_speed(this->g_rshd, this->assembly_line_list.at(i)->share_memory.speed);
                    }
                    this->assembly_line_list.at(i)->share_memory.IPC = CLEAR;
                }
                if(this->assembly_line_list.at(i)->share_memory.device == "claw")
                {
                    if(this->assembly_line_list.at(i)->share_memory.action == "open")
                    {
                        qDebug() << "robot: open claw:" << i;
                        open_claw(this->g_rshd);

                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "close")
                    {
                        qDebug() << "robot: close claw:" << i;
                        clos_claw(this->g_rshd);
                    }
                    this->assembly_line_list.at(i)->share_memory.IPC = CLEAR;
                }
                if(this->assembly_line_list.at(i)->share_memory.device == "cnc")
                {
                    if(this->assembly_line_list.at(i)->share_memory.action == "open")
                    {
                        qDebug() << "robot: open cnc:" << i;
                        open_cnc(this->g_rshd);

                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "close")
                    {
                        qDebug() << "robot: close cnc:" << i;
                        clos_cnc(this->g_rshd);
                    }
                    this->assembly_line_list.at(i)->share_memory.IPC = CLEAR;
                }

                if(this->assembly_line_list.at(i)->share_memory.device == "fdm")
                {
                    if(this->assembly_line_list.at(i)->share_memory.action == "start")
                    {
                        qDebug() << "fdm: start:" << i;
                        this->udp_clint.start_print(i);
                        this->assembly_line_list.at(i)->share_memory.action = "wait";

                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "wait")
                    {
                        if(this->udp_clint.get_fdm_state(i))
                        {
                            qDebug() << "fdm: done:" << i;
                            this->assembly_line_list.at(i)->share_memory.IPC = CLEAR;
                        }
                    }


                }
                if(this->assembly_line_list.at(i)->share_memory.device == "motion")
                {
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_x")
                    {
                        qDebug() << "motion: move_x:" << i;
                        this->udp_clint.motion(0, this->assembly_line_list.at(i)->share_memory.distance_x);
                        this->assembly_line_list.at(i)->share_memory.action = "wait_x";

                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "wait_x")
                    {
                        if(this->udp_clint.get_motion_state(0))
                        {
                            qDebug() << "motion: done:" << "0";
                            this->assembly_line_list.at(i)->share_memory.IPC = CLEAR;
                        }
                    }
                }
                if(this->assembly_line_list.at(i)->share_memory.device == "motion")
                {
                    if(this->assembly_line_list.at(i)->share_memory.action == "move_y")
                    {
                        qDebug() << "motion: move_y:" << i;
                        this->udp_clint.motion(1, this->assembly_line_list.at(i)->share_memory.distance_y);
                        this->assembly_line_list.at(i)->share_memory.action = "wait_y";

                    }
                    if(this->assembly_line_list.at(i)->share_memory.action == "wait_y")
                    {
                        if(this->udp_clint.get_motion_state(1))
                        {
                            qDebug() << "motion: done:" << "1";
                            this->assembly_line_list.at(i)->share_memory.IPC = CLEAR;
                        }
                    }
                }


            }

            this->assembly_line_list.at(i)->release();
        }
    }
}
