#ifndef ASSEMBLYLINE_H
#define ASSEMBLYLINE_H
#include <QThread>
#include <QMutex>
#include <QDomDocument>
#include "rsdef.h"
#define SET 1
#define CLEAR 0

class ShareMemory
{
public:
    quint8 IPC=CLEAR;
    QString device;
    QString action;
    double joint[6];
    struct Pos pos;

};

class AssemblyLine : public QThread
{
    Q_OBJECT
    enum SubState
    {
        sub_state0,
        sub_state1,
        sub_state2,
        sub_state3,
        sub_state4,
        sub_state5,
        sub_state6
    };
public:
    AssemblyLine(QDomElement assembly_line);
    void run();
    void do_work();
    void set_state(int state);
    int get_state();
    int state;

    QDomElement assembly_line;
    QDomElement process;
    QMutex mutex;
    SubState sub_state;
    quint16 count;

    ShareMemory share_memory;
    QMutex share_memory_mutex;
    void acquire();
    void release();



};

#endif // ASSEMBLYLINE_H
