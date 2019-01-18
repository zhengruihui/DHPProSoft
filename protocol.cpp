#include <QByteArray>
#include "protocol.h"
#include <QDebug>

Protocol::Protocol()
{
    udpSocket = new QUdpSocket;
    udpSocket->bind(QHostAddress("192.168.1.89"), 12345);

    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
}

void Protocol::write()
{
    udpSocket->writeDatagram((char *)&(this->upload), sizeof(struct Upload), QHostAddress("192.168.1.222"), 56789);
}

void Protocol::start_print(int id)
{
    this->upload.command = 0x01;
    this->upload.FDM_ID = (unsigned char)id;
    this->write();
}

void Protocol::motion(int id, float distance)
{
    this->upload.command = 0x02;
    this->upload.MOTOR_ID = id;
    this->upload.distance = distance;
    this->motion_state[0] = false;
    this->write();
}

bool Protocol::get_fdm_state(int id)
{
    QMutexLocker locker(&this->mutex);
    return this->state[id];
}

bool Protocol::get_motion_state(int id)
{
    QMutexLocker locker(&this->mutex);
    return this->motion_state[0];
}


void Protocol::readPendingDatagrams()
{
    QByteArray ba;
    while (udpSocket->hasPendingDatagrams())
    {
        ba.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(ba.data(), ba.size());
        memcpy(&download, ba.data(), sizeof(struct Download));
        this->mutex.lock();
        if(this->download.command == 0x00)
        {
            for(int i=0; i<3;i++)
            {
                this->state[i] = (bool)(this->download.status[i]);
            }
            this->motion_state[0] = this->download.motor_flg;
        }

        if(this->download.command == 0x04)
        {
            this->motion_state[0] = this->download.motor_flg;
        }

        if(this->download.command == 0x01)
        {
            qDebug() << "start assembly line";
        }


        if(this->download.command == 0x02)
        {
            qDebug() << "pause assembly line";
        }

        if(this->download.command == 0x03)
        {
            qDebug() << "stop assembly line";
        }

        this->mutex.unlock();
    }
}


