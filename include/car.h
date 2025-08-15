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
 * @class Car������
 * @brief 	1.�������
 *	���������� car_x
 *	���������� car_y
 *	�������ڳ��� car_lane :left -1 ; mid 0; right 1
 *	������ɫ car_color
 *	�����ٶ� car_speed
 *	������ʼλ��car_y0
 *				car_x1
 *				car_x2
 *				car_x3
 *	����һ��λ��car_y1
 *				car_r1
 *				car_r2
 *				car_r3
 *	������� car_width(WIDTH * 3)
 *	�������� car_heigth
 * @brief    2.������� ��7����
 * 	�ж��Ƿ���ײ iscrashing
 * 	������ǰ CarMove
 * 	��������·��������y����ͳ����� CarRoute
 * 	��ʾ���� CarView
 * 	�������� car_generator
 * 	�ж��Ƿ�ﵽ·��,����ʱ��ʼִ�У�����iscrashing�� IsArriving
 * 	�������ɼ�ʱ������¼��������ʱ�䣬һ��ʱ��֮�� ͬһ��·���ܹ������������� car_timer
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
 * @brief ���ܣ�ÿ����������������Car(-1) Car(0) Car(1)  {��������ʱ�������ÿ����������¼Ȼ��
 * 			   ���ɽ���car_timemin car_timemax֮���ʱ��,�������ʱ���������һ������}
 * 			   {	CarRoute
 * 					CarMove
 * 					CarView
 * 					if(IsArriving){
 * 						iscrashing_play
 * 						IsCrashingKid
 * 					}
 * 					����car_end �������������
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
	 * @brief ��������·��
	 * @detail ����������ǰ����ͳ���������ʻ·��
	 *
	 * ����˵����
	 * 1. ����������y����(car_y)�ͳ���(car_lane)��̬����x����(car_x)
	 * 2. ʵ��·�������߼���
	 * -��೵������(x1, y0)��ֱ�ߵ�(r1, y1)��Ȼ���y1��ʼֱ����������
	 * -�м䳵������(x2, y0)��ֱ�ߵ�(r2, y1)��Ȼ���y1��ʼֱ����������
	 * -�Ҳ೵������(x3, y0)��ֱ�ߵ�(r3, y1)��Ȼ���y1��ʼֱ����������
	 */
	void CarRoute();

	/**
	 * @brief �ж������Ƿ񵽴�·��
	 * @return bool - �������·�ڷ���true������false
	 *
	 * ����˵����
	 * 1. ����������y����(car_y)�ж��Ƿ����·������
	 * 2. ·��������Ϊ��roadtop �� car_y �� (roadbot + car_height)
	 * 3. �ڴ������ڷ���true�������ⷵ��false
	 */
	bool IsArriving();

	/**
	 * @brief �����С������ײ
	 *
	 * ����˵����
	 * 1. ����IsArriving()����trueʱ�������
	 * 2. ���������ĳ���(car_lane)�Ϳ��(car_width)������ײ����
	 * 3. ��������С������(kid_v)�����С������(kid_x)�Ƿ���������ײ������
	 * 4. ���ر�ײС������ָ�루��������ײ��
	 */
	void IsCrashingKid();

	/**
	 * @brief �������ҵ���ײ
	 *
	 * ����˵����
	 * 1. ����IsArriving()����trueʱ�������
	 * 2. ������������ж��Ƿ�����ײ
	 * 3. ��������ײ���޸����״̬��־Ϊ5 (player.flag = 5)
	 */
	void IsCrashPlayer();

	/**
	 * @brief �ƶ�����
	 *
	 * ����˵����
	 * 1. ��ʱ����������y����(car_y)
	 * 2. ÿ�θ���������car_y += car_speed
	 * 3. ����������ϵͳ��ʱ������
	 */
	void CarMove();

	/**
	 * @brief ��Ⱦ����ͼ��
	 *
	 * ����˵����
	 * 1. ��������������(car_x, car_y)������Ļλ��
	 * 2. ʹ��������ɫ(car_color)����ͼ��
	 * 3. ʵ��ϸ�ڣ�
	 *    - �����������壨���Σ�
	 *    - ��ӳ�����ϸ��Ԫ��
	 *    - ����ͬ��������Ⱦ����
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
 * @brief �����������������ڹ���
 *
 * ����˵����
 * 1. ����car_timer��ȡʱ�����ֵ��Ϊ���ɼ��
 * 2. ���������������³���
 *    - Ϊ�³������ʼλ�ú�����
 *    - ���������������
 * 3. ʵʱ����ÿ������״̬��
 *    - ����CarRoute����·��
 *    - ����CarMove����λ��
 *    - ����CarView��Ⱦ��ʾ
 * 4. ��������
 *    - ��������(left/mid/right)��������
 *    - ÿ����������car_timer������һ������ʱ��
 */

void CarsView();
