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
	��Ϸҳ������
		1.�������
			����score
			ͨ��Ҫ�� goal
			���»�Ҫ����С������ waitnum
			//�ڳ�С������ kidnum (sizeof kid_v)
			ͨ��С������ passnum
			����С������ deadnum
			��·�ϱ߽�λ�� roadtop
			������ߵ�y���� player_y
			С�����ߵ�y���� kid_y
			��·�±߽�λ�� roadbot
			��������ʱ������Χ
								car_timemin
								car_timemax
			С������ kid_v
			��ǰʱ�� t
			��������� ��������ʱ�� t1
			�в������� ��������ʱ�� t2
			�Ҳ������� ��������ʱ�� t3
			����ﳵ�� �������ɼ�� TL
			�в������� �������ɼ�� TM
			�Ҳ������� �������ɼ�� TR
			������· lane_left -1��lane_mid 0��lane_right 1��


		2.�������
			game_init:��ʼ��

			game_view����Ϸҳ��չʾ
			game_lose_view:ʧ��չʾ
			game_win_view:ʤ��չʾ
			game_pause_view����ͣҳ��չʾ

			iswin���ж�����С��������������ʧ��
					���ڳ�С��ʱ���޼������ɵ�С��ʱ����Ƿ��ʤ

			�Ӽ��̶�ȡ���� play_controller: ��a ��d ��j ͣk �޸Ķ�Ӧflag
*/

//--------------------------�������---------------------------


extern vector<class Kids> kid_v;



extern int waitnum;
extern int kidnum;//�ڳ�С��
extern int passnum;
extern int deadnum;



//--------------------------�������---------------------------



//-------------------------service-----------------------------

/*
	���ܣ���ʼ����Ϸ����
*/
void game_init();

/*
	���ܣ��ж�����Ƿ��ʤ������С����Ŀdeadnum ����������������deadnum_max �޸� flag Ϊ MY_LOSE,����true
			��waitnum��kid_v ���涼û��С��ʱ�жϻ����Ƿ�ﵽ���ޣ����ﵽ���ޣ�����޸�flagΪ MY_WIN,����true
			�����������false

	-------------------------------�ο�λ��guomalu.h�е�
														#define MY_MENU 0
														#define MY_SETTING 1
														#define MY_GAME 2
														#define MY_LOSE 3
														#define MY_WIN 4
														#define MY_PAUSE 5
														#define MY_OVER -1


	����ֵ��
*/
bool iswin();
bool islost();

//-------------------------service-----------------------------

//---------------------------view------------------------------

/*
	���ܣ�ʵʱչʾ��ҷ�����չʾscore�ڶ�Ӧλ��
*/
void game_score_view();

/*
	���ܣ�ʵʱչʾ����С������չʾdeadnum�ڶ�Ӧλ��
*/
void game_death_view();

/*
	���ܣ�չʾ��û�ϳ�С������չʾkidnum�ڶ�Ӧλ��
*/
//void game_wait_view();

/*
	���ܣ�չʾͨ��С������passnum����Ӧλ��
*/
void game_pass_view();


void game_score_total_view();


void game_view();

void win_view();

void lose_view();

void pause_view();
