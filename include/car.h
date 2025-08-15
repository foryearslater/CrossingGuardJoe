#pragma once
#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>
#include "player.h"
#include "kid.h"
#include "vector"
#include "game.h"
using namespace std;

#ifdef UNICODE
#undef UNICODE
#endif

/**
 * @class Car汽车类
 * @brief 	1.数据设计
 *	汽车横坐标 car_x
 *	汽车纵坐标 car_y
 *	汽车所在车道 car_lane :left -1 ; mid 0; right 1
 *	汽车颜色 car_color
 *	汽车速度 car_speed
 *	汽车初始位置car_y0
 *				car_x1
 *				car_x2
 *				car_x3
 *	汽车一级位置car_y1
 *				car_r1
 *				car_r2
 *				car_r3
 *	汽车宽度 car_width(WIDTH * 3)
 *	汽车长度 car_heigth
 * @brief    2.函数设计 （7个）
 * 	判断是否碰撞 iscrashing
 * 	匀速向前 CarMove
 * 	计算汽车路径（传入y坐标和车道） CarRoute
 * 	显示汽车 CarView
 * 	生成汽车 car_generator
 * 	判断是否达到路口,到达时开始执行（函数iscrashing） IsArriving
 * 	汽车生成计时器，记录汽车生成时间，一定时间之后 同一道路上能够接着生成汽车 car_timer
 */

extern const int car_speed;
extern const int car_y0;
extern const int car_x1;
extern const int car_x2;
extern const int car_x3;
extern const int car_y1;
extern const int car_r1;
extern const int car_r2;
extern const int car_r3;
// extern const int car_width;
extern const int car_height;
extern const int car_end;
extern const int car_timemax;
extern const int car_timemin;
extern int deadnum;
extern class Player joe;

/**
 * @brief 功能：每个车道的生成汽车Car(-1) Car(0) Car(1)  {有三个计时器，针对每个车道，记录然后
 * 			   生成介于car_timemin car_timemax之间的时间,到达这个时间就生成下一辆汽车}
 * 			   {	CarRoute
 * 					CarMove
 * 					CarView
 * 					if(IsArriving){
 * 						iscrashing_play
 * 						IsCrashingKid
 * 					}
 * 					到达car_end 清除这辆汽车。
 * 			}
 */

bool Timer1();
bool Timer2();
bool Timer3();

class Cars
{
public:
	//---------------------------------------

	//----------------service----------------------------

	Cars(int a);
	~Cars();

	/**
	 * @brief 计算汽车路径
	 * @detail 根据汽车当前坐标和车道计算行驶路径
	 *
	 * 功能说明：
	 * 1. 基于汽车的y坐标(car_y)和车道(car_lane)动态调整x坐标(car_x)
	 * 2. 实现路径计算逻辑：
	 * -左侧车道：从(x1, y0)沿直线到(r1, y1)，然后从y1开始直线向下运行
	 * -中间车道：从(x2, y0)沿直线到(r2, y1)，然后从y1开始直线向下运行
	 * -右侧车道：从(x3, y0)沿直线到(r3, y1)，然后从y1开始直线向下运行
	 */
	void CarRoute();

	/**
	 * @brief 判断汽车是否到达路口
	 * @return bool - 如果到达路口返回true，否则false
	 *
	 * 功能说明：
	 * 1. 基于汽车的y坐标(car_y)判断是否进入路口区域
	 * 2. 路口区域定义为：roadtop ≤ car_y ≤ (roadbot + car_height)
	 * 3. 在此区间内返回true，区间外返回false
	 */
	bool IsArriving();

	/**
	 * @brief 检测与小孩的碰撞
	 *
	 * 功能说明：
	 * 1. 仅当IsArriving()返回true时触发检测
	 * 2. 根据汽车的车道(car_lane)和宽度(car_width)计算碰撞区域
	 * 3. 遍历所有小孩对象(kid_v)，检测小孩坐标(kid_x)是否在汽车碰撞区域内
	 * 4. 返回被撞小孩的类指针（若发生碰撞）
	 */
	void IsCrashingKid();

	/**
	 * @brief 检测与玩家的碰撞
	 *
	 * 功能说明：
	 * 1. 仅当IsArriving()返回true时触发检测
	 * 2. 根据玩家坐标判断是否发生碰撞
	 * 3. 若发生碰撞，修改玩家状态标志为5 (player.flag = 5)
	 */
	void IsCrashPlayer();

	/**
	 * @brief 移动汽车
	 *
	 * 功能说明：
	 * 1. 定时更新汽车的y坐标(car_y)
	 * 2. 每次更新增量：car_y += car_speed
	 * 3. 调用周期由系统定时器控制
	 */
	void CarMove();

	/**
	 * @brief 渲染汽车图形
	 *
	 * 功能说明：
	 * 1. 根据汽车的坐标(car_x, car_y)计算屏幕位置
	 * 2. 使用汽车颜色(car_color)绘制图形
	 * 3. 实现细节：
	 *    - 绘制汽车主体（矩形）
	 *    - 添加车窗等细节元素
	 *    - 处理不同车道的渲染差异
	 */
	void CarView();

public:
	int car_x;
	int car_y;
	int car_lane;
	int car_state;
	int car_width = 93;
};

/**
 * @brief 汽车生成与生命周期管理
 *
 * 功能说明：
 * 1. 调用car_timer获取时间随机值作为生成间隔
 * 2. 基于随机间隔生成新车：
 *    - 为新车分配初始位置和属性
 *    - 加入汽车管理队列
 * 3. 实时更新每个汽车状态：
 *    - 调用CarRoute计算路径
 *    - 调用CarMove更新位置
 *    - 调用CarView渲染显示
 * 4. 车道管理：
 *    - 三个车道(left/mid/right)独立管理
 *    - 每个车道根据car_timer决定下一次生成时间
 */

void CarsView();
