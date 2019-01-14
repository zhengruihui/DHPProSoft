#include "ParseXml.h"
#include <QDomDocument>
#include <QFile>
#include <QDebug>


ParseXml::ParseXml(QString xml_name)
{
    QFile file(xml_name);
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



    for(QDomElement assembly_line = multi_process.firstChildElement(); !assembly_line.isNull(); assembly_line = assembly_line.nextSiblingElement())
    {
        AssemblyLineHandle *assembly_line_handle = new AssemblyLineHandle(assembly_line);
        this->assembly_line_handle_list.append(assembly_line_handle);

    }
}
