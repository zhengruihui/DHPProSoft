#include "AssemblyLineHandle.h"
#include <QDebug>


QMutex assembly_line_mutex;

AssemblyLineHandle::AssemblyLineHandle(QDomElement assembly_line)
{
    this->assembly_line = assembly_line;
}

void AssemblyLineHandle::run()
{
    while(true)
    {
        switch(this->get_state())
        {
            case 0:

            break;

            case 1:

            break;

            case 2:
                this->sleep(1);
                qDebug("hello!");
            break;

            default:
            break;

        }

    }
    for(QDomElement process = this->assembly_line.firstChildElement(); !process.isNull(); process = process.nextSiblingElement())
    {
        if(process.tagName() == "lock")
        {
            if(process.attribute("action") == "acquire")
            {
                assembly_line_mutex.lock();
                qDebug() << "acquire" << this->assembly_line.attribute("id");
            }
            if(process.attribute("action") == "release")
            {
                assembly_line_mutex.unlock();
                qDebug() << "release"<< this->assembly_line.attribute("id");
            }
        }
        if(process.tagName() == "claw")
        {
            if(process.attribute("action") == "open")
            {
                qDebug() << "claw" <<"open" << this->assembly_line.attribute("id");
            }
            if(process.attribute("action") == "close")
            {
                qDebug() << "claw" <<"close" <<this->assembly_line.attribute("id");
            }
        }
        if(process.tagName() == "cnc")
        {
            if(process.attribute("action") == "open")
            {
                qDebug() << "cnc" <<"open" << this->assembly_line.attribute("id");
            }
            if(process.attribute("action") == "close")
            {
                qDebug() << "cnc" <<"open" << this->assembly_line.attribute("id");
            }
        }


        if(process.tagName() == "motion")
        {

        }
        if(process.tagName() == "robot")
        {

        }
        if(process.tagName() == "move_line")
        {

        }
        if(process.tagName() == "fdm")
        {

        }

    }
}

void AssemblyLineHandle::set_state(int state)
{
    QMutexLocker m_locker(&this->mutex);
    this->assembly_line_state = state;
}

int AssemblyLineHandle::get_state()
{
    QMutexLocker m_locker(&this->mutex);
    return this->assembly_line_state;
}

