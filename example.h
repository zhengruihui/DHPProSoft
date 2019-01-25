#pragma once

#include <string>
#include "rsdef.h"

using namespace std;

struct Speed
{
    double jointacc;
    double jointvelc;
    double lineacc;
    double linevelc;
    double angleacc;
    double anglevelc;
};

//打印路点信息
void printRoadPoint(const aubo_robot_namespace::wayPoint_S  *wayPoint);

void callback_RealTimeRoadPoint(const aubo_robot_namespace::wayPoint_S  *wayPoint, void *arg);

//登陆机械臂
bool example_login(RSHD &rshd, const char * addr, int port);

//退出登陆
bool example_logout(RSHD rshd);

//启动机械臂(必须连接真实机械臂）
bool example_robotStartup(RSHD rshd);

//关闭机械臂（必须连接真实机械臂）
bool example_robotShutdown(RSHD rshd);

//机械臂轨迹运动测试
void example_moveP(RSHD rshd);

//机械臂正逆解测试
void example_ik_fk(RSHD rshd);

//机械臂控制柜IO测试(必须连接真实机械臂）
void example_boardIO(RSHD rshd);

//机械臂工具端IO测试(必须连接真实机械臂）
void example_ToolIO(RSHD rshd);

//相对姿态测试
void demo_relativeOri(RSHD rshd);

//实时路点信息回调函数测试
bool example_callbackRobotRoadPoint(RSHD rshd);

bool move_pos(RSHD rshd, const Pos *pos);
//机械臂保持当前姿态直线运动测试
bool move_line(RSHD rshd, const Pos *pos, double joint5);
bool move_arc(RSHD rshd, const Pos *center, double r, int times);
void set_speed(RSHD rshd, struct Speed);
void open_claw(RSHD rshd);
void clos_claw(RSHD rshd);
void open_cnc(RSHD rshd);
void clos_cnc(RSHD rshd);
