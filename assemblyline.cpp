#include "assemblyline.h"
#include <QDebug>

#define M_PI 3.14159265358979323846

static QMutex assembly_line_mutex;

AssemblyLine::AssemblyLine(QDomElement assembly_line)
{
    this->assembly_line = assembly_line;
    this->state = 1;
    this->sub_state = sub_state0;
    this->count = 0;
    this->start();
}

void AssemblyLine::run()
{
    while(true)
    {
        switch(this->get_state())
        {
            case 0:
            break;

            case 1:
                this->do_work();
            break;

            case 2:

            break;

            default:
            break;

        }

    }
}

void AssemblyLine::do_work()
{
    switch(this->sub_state)
    {
        case sub_state0:
            if(this->count < this->assembly_line.attribute("times").toShort())
            {
                this->count ++;
                this->sub_state = sub_state1;
                this->process = this->assembly_line.firstChildElement();
            }
            else
            {
               this->set_state(0);
            }
        break;

        case sub_state1:
            if(this->process.tagName() == "robot")
            {
                this->acquire();
                this->share_memory.device = "robot";

                if(this->process.attribute("action") == "move_joint")
                {
                    this->share_memory.action = "move_joint";
                    this->share_memory.joint[0] = this->process.attribute("joint0").toDouble()*M_PI / 180;
                    this->share_memory.joint[1] = this->process.attribute("joint1").toDouble()*M_PI / 180;
                    this->share_memory.joint[2] = this->process.attribute("joint2").toDouble()*M_PI / 180;
                    this->share_memory.joint[3] = this->process.attribute("joint3").toDouble()*M_PI / 180;
                    this->share_memory.joint[4] = this->process.attribute("joint4").toDouble()*M_PI / 180;
                    this->share_memory.joint[5] = this->process.attribute("joint5").toDouble()*M_PI / 180;
                }

                if(this->process.attribute("action") == "move_line")
                {
                    this->share_memory.action = "move_line";
                    this->share_memory.pos.x = this->process.attribute("x").toDouble() / 1000;
                    this->share_memory.pos.y = this->process.attribute("y").toDouble() / 1000;
                    this->share_memory.pos.z = this->process.attribute("z").toDouble() / 1000;
                    this->share_memory.joint[5] = this->process.attribute("joint5").toDouble()*M_PI / 180;
                }

                if(this->process.attribute("action") == "move_pos")
                {
                    this->share_memory.action = "move_pos";
                    this->share_memory.pos.x = this->process.attribute("x").toDouble() / 1000;
                    this->share_memory.pos.y = this->process.attribute("y").toDouble() / 1000;
                    this->share_memory.pos.z = this->process.attribute("z").toDouble() / 1000;
                }

                if(this->process.attribute("action") == "move_arc")
                {
                    this->share_memory.action = "move_arc";
                    this->share_memory.pos.x = this->process.attribute("x").toDouble() / 1000;
                    this->share_memory.pos.y = this->process.attribute("y").toDouble() / 1000;
                    this->share_memory.pos.z = this->process.attribute("z").toDouble() / 1000;
                    this->share_memory.r = this->process.attribute("r").toDouble() / 1000;
                    this->share_memory.times = this->process.attribute("times").toInt();
                }

                if(this->process.attribute("action") == "set_speed")
                {
                    this->share_memory.action = "set_speed";
                    this->share_memory.speed.lineacc = this->process.attribute("lineacc").toDouble() / 1000;
                    this->share_memory.speed.linevelc = this->process.attribute("linevelc").toDouble() / 1000;

                    this->share_memory.speed.jointacc = this->process.attribute("jointacc").toDouble()*M_PI / 180;
                    this->share_memory.speed.jointvelc = this->process.attribute("jointvelc").toDouble()*M_PI / 180;

                    this->share_memory.speed.angleacc = this->process.attribute("angleacc").toDouble()*M_PI / 180;
                    this->share_memory.speed.anglevelc = this->process.attribute("anglevelc").toDouble()*M_PI / 180;
                }

                this->share_memory.IPC = SET;
                this->release();
            }
            if(this->process.tagName() == "lock")
            {
                if(this->process.attribute("action") == "acquire")
                {
                    assembly_line_mutex.lock();
                    qDebug() << "lock: acquire" << this->assembly_line.attribute("id");
                }

                if(this->process.attribute("action") == "release")
                {
                    assembly_line_mutex.unlock();
                    qDebug() << "lock: release" << this->assembly_line.attribute("id");
                }

            }
            this->sub_state = sub_state2;
        break;
        case sub_state2:
            this->acquire();
            if(this->share_memory.IPC == CLEAR)
            {

                this->process = this->process.nextSiblingElement();
                if(this->process.isNull())
                {
                    this->sub_state = sub_state0;
                }
                else
                {
                    this->sub_state = sub_state1;
                }

            }
            this->release();
        break;

        default:
        break;
    }
}

void AssemblyLine::set_state(int state)
{
    QMutexLocker m_locker(&this->mutex);
    this->state = state;
}

int AssemblyLine::get_state()
{
    QMutexLocker m_locker(&this->mutex);
    return this->state;
}

void AssemblyLine::acquire()
{
    this->share_memory_mutex.lock();
}

void AssemblyLine::release()
{
    this->share_memory_mutex.unlock();
}
