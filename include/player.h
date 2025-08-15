#pragma once
#include <easyx.h>
#include <graphics.h>
#include <xlocnum>
#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "kid.h"
#include "car.h"
#pragma warning(disable : 4996)
#ifdef UNICODE
#undef UNICODE
#endif
extern vector<class Kids> kid_v;

/**
 * @class玩家类
 * @brief 1.数据设计
 *			玩家横坐标 player_x
 *			玩家起始位置player_x0
 *			玩家动作 player_flag ;stand 0 (站立) go 1 （指挥走）:stop 2 （指挥停）；left 3（向左走）;right 4 (向右走)
 *								be_hit_left 5 (被撞到左边) be_hit_right 6 (被撞到右边)
 *
 *		 2.函数设计
 *			角色展示 player_view：展示玩家和动作
 *			判断是否被撞，被撞了就改变x坐标 player_crashed
 *			move_command
 *			stop_command
 */
class Player
{

public:
	Player(int player_x, int player_flag, int player_speed);

	void player_stand();
	/*
	 * @brief	功能：遍历小孩kid_v,指挥（player_x - width , player_x + width ）范围内的小孩，修改其flag为move 1
	 */
	void move_command(vector<Kids> &kid_v, Player joe);

	/*
	* @brief	功能：遍历小孩kid_v,指挥（player_x - width , player_x + width ）范围内的小孩，修改其flag为stop 2
				若小孩本来就是wait ，重置对应(kid_timer)
	*/
	void stop_command(vector<Kids> &kid_v, Player joe);

	/*
	 * @brief	功能：被车撞了，玩家的x坐标发生变化   怎么变？
	 */
	void player_be_hit();

	/*
	 * @brief	功能：当玩家player_flag 为left 3的时候 ，单位时间内玩家向左移player_speed 的距离，若player_flag为right 4的时候， 单位时间向右移动player_speed的距离
	 */
	void player_moving();

	void makeflag();

	/*
	 * @brief	功能：结合 玩家player_x 根据对应flag展示对应动作
	 */
	void player_view();

public:
	int player_x;
	int player_flag;
	int player_speed;
	int player_width;
	IMAGE stand_image[2];

	IMAGE move_left_image[9];
	IMAGE move_left_image_y[9];
	int move_left_num;
	IMAGE move_right_image[9];
	IMAGE move_right_image_y[9];
	int move_right_num;
	IMAGE move_command_image;
	IMAGE move_command_image_y;

	IMAGE stop_command_image;
	IMAGE stop_command_image_y;

	IMAGE be_hit_left_image[4];
	IMAGE be_hit_left_image_y[4];
	int be_hit_left_num;

	IMAGE be_hit_right_image[4];
	IMAGE be_hit_right_image_y[4];
	int be_hit_right_num;
};