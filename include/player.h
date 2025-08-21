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
 * @class�����
 * @brief 1.�������
 *			��Һ����� player_x
 *			�����ʼλ��player_x0
 *			��Ҷ��� player_flag ;stand 0 (վ��) go 1 ��ָ���ߣ�:stop 2 ��ָ��ͣ����left 3�������ߣ�;right 4 (������)
 *								be_hit_left 5 (��ײ�����) be_hit_right 6 (��ײ���ұ�)
 *
 *		 2.�������
 *			��ɫչʾ player_view��չʾ��ҺͶ���
 *			�ж��Ƿ�ײ����ײ�˾͸ı�x���� player_crashed
 *			move_command
 *			stop_command
 */
class Player
{

public:
	Player(int player_x, int player_flag, int player_speed);

	void player_stand();
	/*
	 * @brief	���ܣ�����С��kid_v,ָ�ӣ�player_x - width , player_x + width ����Χ�ڵ�С�����޸���flagΪmove 1
	 */
	void move_command(vector<Kids> &kid_v, Player joe);

	/*
	* @brief	���ܣ�����С��kid_v,ָ�ӣ�player_x - width , player_x + width ����Χ�ڵ�С�����޸���flagΪstop 2
				��С����������wait �����ö�Ӧ(kid_timer)
	*/
	void stop_command(vector<Kids> &kid_v, Player joe);

	/*
	 * @brief	���ܣ�����ײ�ˣ���ҵ�x���귢���仯   ��ô�䣿
	 */
	void player_be_hit();

	/*
	 * @brief	���ܣ������player_flag Ϊleft 3��ʱ�� ����λʱ�������������player_speed �ľ��룬��player_flagΪright 4��ʱ�� ��λʱ�������ƶ�player_speed�ľ���
	 */
	void player_moving();

	void makeflag();

	/*
	 * @brief	���ܣ���� ���player_x ���ݶ�Ӧflagչʾ��Ӧ����
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