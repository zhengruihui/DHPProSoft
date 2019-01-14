#ifndef ASSEMBLY_LINE_H
#define ASSEMBLY_LINE_H
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QDomDocument>

class AssemblyLineHandle : public QThread
{
    Q_OBJECT
public:
    AssemblyLineHandle(QDomElement assembly_line);
    void run();
    void set_state(int state);
    int get_state();
    int assembly_line_state;

    QDomElement assembly_line;
    QMutex mutex;

};

#endif // ASSEMBLY_LINE_H
