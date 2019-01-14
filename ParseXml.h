#ifndef PARSE_XML_H
#define PARSE_XML_H
#include <QString>
#include "AssemblyLineHandle.h"
#include <QList>

class ParseXml
{
public:
    ParseXml(QString xml_name);

    QList<AssemblyLineHandle*>assembly_line_handle_list;
};

#endif // PARSE_XML_H
