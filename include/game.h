#pragma once

#include <conio.h>
#pragma comment(lib,"Winmm.lib")

#include "kid.h"
#include "player.h"
#include "car.h"
#include <graphics.h>
#include <easyx.h>
#include <string>
#include <vector>
#include<iostream>
#include "button.h"
using namespace std;

#define window_width 1200
#define window_height 750

#define total_score_x 275
#define total_score_y 20
#define score_x 50
#define score_y 20
#define wait_x 850
#define wait_y 452
#define death_x 550
#define death_y 20
#define pass_x 320
#define pass_y 452
#define pause_x 900
#define pause_y 400
#define goal 800
#define left 360
#define right 825

#define kid_xstart  1250
#define kid_xend  150
#define kid_score  200
#define kid_speed  30
#define WIDTH  45
#define roadtop  590
#define roadbot  640
#define player_y  610
#define kid_y  560
#define deadnum_max  5
#define kid_xstart  1250

#define four_text_w 200
#define two_text_w 100
#define default_height 50

#define MY_OVER -1
#define MY_MENU 0
#define MY_SETTING 1
#define MY_GAME 2
#define MY_LOSE 3
#define MY_WIN 4
#define MY_PAUSE 5
#define MY_HELP 6
#define MY_ABOUT 7

#ifdef UNICODE
#undef UNICODE
#endif



/*
	游戏页面整合
		1.数据设计
			分数score
			通关要求 goal
			场下还要生成小孩数量 waitnum
			//在场小孩数量 kidnum (sizeof kid_v)
			通过小孩数量 passnum
			死亡小孩数量 deadnum
			马路上边界位置 roadtop
			玩家行走的y坐标 player_y
			小孩行走的y坐标 kid_y
			马路下边界位置 roadbot
			汽车生成时间间隔范围
								car_timemin
								car_timemax
			小孩队列 kid_v
			当前时间 t
			左侧汽车道 汽车生成时间 t1
			中侧汽车道 汽车生成时间 t2
			右侧汽车道 汽车生成时间 t3
			左侧骑车到 汽车生成间隔 TL
			中侧汽车道 汽车生成间隔 TM
			右侧汽车道 汽车生成间隔 TR
			三条道路 lane_left -1、lane_mid 0、lane_right 1。


		2.函数设计
			game_init:初始化

			game_view：游戏页面展示
			game_lose_view:失败展示
			game_win_view:胜利展示
			game_pause_view：暂停页面展示

			iswin：判断死亡小孩数量，超过就失败
					无在场小孩时，无继续生成的小孩时检查是否获胜

			从键盘读取输入 play_controller: 左a 右d 走j 停k 修改对应flag
*/

//--------------------------数据设计---------------------------


extern vector<class Kids> kid_v;



extern int waitnum;
extern int kidnum;//在场小孩
extern int passnum;
extern int deadnum;



//--------------------------数据设计---------------------------



//-------------------------service-----------------------------

/*
	功能：初始化游戏数据
*/
void game_init();

/*
	功能：判断玩家是否获胜，死亡小孩数目deadnum 超过死亡人数上限deadnum_max 修改 flag 为 MY_LOSE,返回true
			当waitnum和kid_v 里面都没有小孩时判断积分是否达到上限，若达到上限，则就修改flag为 MY_WIN,返回true
			其余情况返回false

	-------------------------------参考位于guomalu.h中的
														#define MY_MENU 0
														#define MY_SETTING 1
														#define MY_GAME 2
														#define MY_LOSE 3
														#define MY_WIN 4
														#define MY_PAUSE 5
														#define MY_OVER -1


	返回值：
*/
bool iswin();
bool islost();

//-------------------------service-----------------------------

//---------------------------view------------------------------

/*
	功能：实时展示玩家分数，展示score在对应位置
*/
void game_score_view();

/*
	功能：实时展示死亡小孩数，展示deadnum在对应位置
*/
void game_death_view();

/*
	功能：展示还没上场小孩数，展示kidnum在对应位置
*/
//void game_wait_view();

/*
	功能：展示通过小孩数量passnum到对应位置
*/
void game_pass_view();


void game_score_total_view();


void game_view();

void win_view();

void lose_view();

void pause_view();
