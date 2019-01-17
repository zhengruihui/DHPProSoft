#ifndef ASSEMBLY_LINE_H
#define ASSEMBLY_LINE_H
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QDomDocument>
#include "assemblyline.h"
#include <QList>
#include "robot.h"

class MultiProcess
{
public:
    MultiProcess();
    void parse_xml(QString name);


    QList<AssemblyLine*> assembly_line_list;
    Robot *robot;
    QMutex *mutex;
};

#endif // ASSEMBLY_LINE_H
