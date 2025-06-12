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


/*
	汽车类
		1.数据设计
			汽车横坐标 car_x
			汽车纵坐标 car_y
			汽车所在车道 car_lane :left -1 ; mid 0; right 1
			汽车颜色 car_color
			汽车速度 car_speed
			汽车初始位置car_y0
						car_x1
						car_x2
						car_x3
			汽车一级位置car_y1
						car_r1
						car_r2
						car_r3
			汽车宽度 car_width(WIDTH * 3)
			汽车长度 car_heigth

		2.函数设计 （7个）
			判断是否碰撞 iscrashing
			匀速向前 car_move
			计算汽车路径（传入y坐标和车道） car_route
			显示汽车 car_view
			生成汽车 car_generator
			判断是否达到路口,到达时开始执行（函数iscrashing） isarriving
			汽车生成计时器，记录汽车生成时间，一定时间之后 同一道路上能够接着生成汽车 car_timer


*/

//

extern const int car_speed;
extern const int car_y0;
extern const int car_x1;
extern const int car_x2;
extern const int car_x3;
extern const int car_y1;
extern const int car_r1;
extern const int car_r2;
extern const int car_r3;
//extern const int car_width;
extern const int car_height;
extern const int car_end;
extern const int car_timemax;
extern const int car_timemin;
extern int deadnum;
extern class Player joe;

/*

	功能：每个车道的生成汽车Car(-1) Car(0) Car(1)  {有三个计时器，针对每个车道，记录然后
		生成介于car_timemin car_timemax之间的时间,到达这个时间就生成下一辆汽车}
				{	car_route
					car_move
					car_view
					if(isarriving){
						iscrashing_play
						iscrashing_kid
					}
					到达car_end 清除这辆汽车。
				}

*/


bool Timer1();
bool Timer2();
bool Timer3();

class Cars {
	//---------------数据设计----------------
public:
	int car_x;
	int car_y;
	int car_lane;
	int car_state;
	int car_width = 93;


	//---------------------------------------

	//----------------service----------------------------

	
	Cars(int a);  
	~Cars();


	/*
		功能：根据车的y坐标（car_y）和车的车道（car_lane）修改对应的x坐标(car_x) **** 参考示意图，以左侧车道为例：汽车从(x1,y0)沿直线到（r1,y1）
																				 **** 然后从y1开始直线向下运行
	*/
	void car_route();

	/*
		功能：根据汽车的y坐标（car_y)判断是否到达路口（（roadtop）直到 (roadbot + car_height)为止都是true ）这个区间外为false
	*/
	bool isarriving();

	/*
		功能：isarriving为true时触发检测，注意（车道，车宽），遍历kid_v中所有小孩的x坐标（kid_x）判断是否撞上小孩 返回被撞小孩的类指针
	*/
	void iscrashing_kid();

	/*
		功能：isarriving 为 true时触发检测， 根据玩家坐标判断是否撞上玩家，撞上(修改玩家flag = 5)
	*/
	/*void iscrashing_play(Player player);*/
	void is_crash_player();

	/*
		功能：定时修改汽车的y坐标（car_y），单位时间增加值为car_speed.
	*/
	void car_move();

	//----------------service----------------------------


	//--------------view--------------------------------

		/*
			功能：根据汽车的横纵坐标car_x,car_y 和 汽车颜色car_color展示对应的汽车
		*/
	void car_view();

	/*
		功能：调用car_timer函数生成的时间随机值，生成一个随机值之后能够接着生成下一个随机值，调用car_route实时修改car_x，调用 car_move 修改car_y函数并实时调用car_view展示汽车，
		三个车道的汽车都基于生成的car_timer决定下一次生成汽车的时间

	*/


	//--------------view--------------------------------
};
void cars_view();
