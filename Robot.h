#ifndef ROBOT_H
#define ROBOT_H
#include <QThread>
#include "assemblyline.h"
#include "example.h"
#include "protocol.h"

class Robot : public QThread
{
    Q_OBJECT
public:
    Robot(QList<AssemblyLine*> assembly_line_list);
//    void move_joint(float joint[6]);
//    void move_line(float axis[3]);
    void run();

    QList<AssemblyLine*> assembly_line_list;
    Protocol udp_clint;
    RSHD g_rshd = -1;

};

#endif // ROBOT_H
