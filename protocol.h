#ifndef UDP_CLINT_H
#define UDP_CLINT_H

#include <QObject>
#include <QUdpSocket>
#include <QMutex>
#include <QMutexLocker>

struct Download
{
  unsigned char  command;   //0x00:数据传输，  0x01:开始打印，   0x02：暂停打印，   0x03：结束打印  0x04：电机移动
  unsigned char  status[3];   //command为0x00时的数据， DF3的打印状态，第0台status[0]  第1台status[1]  第2台status[2]
  bool motor_flg;//电机是否移动完成
};

struct Upload
{
  unsigned char  command;   //0x00:数据传输，  0x01:开始打印， 0x02:电机运动
  unsigned char  FDM_ID;   //command为0x01时的数据，DF3的ID
  unsigned char  MOTOR_ID;  //command为0x02时，电机移动的编号
  float distance;//command为0x02时，电机移动的距离
  //一下为当command为0x00时的数据
  float joint[6];  //机械臂关节弧度值
  float pos[3];  //位置
  float ori[4];  //姿态
};


class Protocol : public QObject
{
    Q_OBJECT
public:
    Protocol();

    QUdpSocket *udpSocket;
    struct Download download;
    struct Upload upload;
    QMutex mutex;

    void write();
    void start_print(int id);
    void motion(int id, float distance);
    bool get_fdm_state(int id);
    bool get_motion_state(int id);
    bool state[3] = {false, false, false};
    bool motion_state[2] = {false, false};



public slots:
    void readPendingDatagrams();

};

#endif // UDP_CLINT_H
