#include "mutilprocess.h"
#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QDebug>


MultiProcess::MultiProcess()
{
    this->mutex = new QMutex();
}

void MultiProcess::parse_xml(QString name)
{
    QFile file(name);
    if(!file.open(QFile::ReadOnly))
       return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
       file.close();
       return;
    }
    file.close();

    QDomElement multi_process = doc.documentElement();
    qDebug() << multi_process.nodeName();

    for(QDomElement assembly_line_element = multi_process.firstChildElement(); !assembly_line_element.isNull(); assembly_line_element = assembly_line_element.nextSiblingElement())
    {
        AssemblyLine *assembly_line = new AssemblyLine(assembly_line_element);
        this->assembly_line_list.append(assembly_line);
    }
    this->robot = new Robot(this->assembly_line_list);
}
