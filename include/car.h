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
	������
		1.�������
			���������� car_x
			���������� car_y
			�������ڳ��� car_lane :left -1 ; mid 0; right 1
			������ɫ car_color
			�����ٶ� car_speed
			������ʼλ��car_y0
						car_x1
						car_x2
						car_x3
			����һ��λ��car_y1
						car_r1
						car_r2
						car_r3
			������� car_width(WIDTH * 3)
			�������� car_heigth

		2.������� ��7����
			�ж��Ƿ���ײ iscrashing
			������ǰ car_move
			��������·��������y����ͳ����� car_route
			��ʾ���� car_view
			�������� car_generator
			�ж��Ƿ�ﵽ·��,����ʱ��ʼִ�У�����iscrashing�� isarriving
			�������ɼ�ʱ������¼��������ʱ�䣬һ��ʱ��֮�� ͬһ��·���ܹ������������� car_timer


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

	���ܣ�ÿ����������������Car(-1) Car(0) Car(1)  {��������ʱ�������ÿ����������¼Ȼ��
		���ɽ���car_timemin car_timemax֮���ʱ��,�������ʱ���������һ������}
				{	car_route
					car_move
					car_view
					if(isarriving){
						iscrashing_play
						iscrashing_kid
					}
					����car_end �������������
				}

*/


bool Timer1();
bool Timer2();
bool Timer3();

class Cars {
	//---------------�������----------------
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
		���ܣ����ݳ���y���꣨car_y���ͳ��ĳ�����car_lane���޸Ķ�Ӧ��x����(car_x) **** �ο�ʾ��ͼ������೵��Ϊ����������(x1,y0)��ֱ�ߵ���r1,y1��
																				 **** Ȼ���y1��ʼֱ����������
	*/
	void car_route();

	/*
		���ܣ�����������y���꣨car_y)�ж��Ƿ񵽴�·�ڣ���roadtop��ֱ�� (roadbot + car_height)Ϊֹ����true �����������Ϊfalse
	*/
	bool isarriving();

	/*
		���ܣ�isarrivingΪtrueʱ������⣬ע�⣨����������������kid_v������С����x���꣨kid_x���ж��Ƿ�ײ��С�� ���ر�ײС������ָ��
	*/
	void iscrashing_kid();

	/*
		���ܣ�isarriving Ϊ trueʱ������⣬ ������������ж��Ƿ�ײ����ң�ײ��(�޸����flag = 5)
	*/
	/*void iscrashing_play(Player player);*/
	void is_crash_player();

	/*
		���ܣ���ʱ�޸�������y���꣨car_y������λʱ������ֵΪcar_speed.
	*/
	void car_move();

	//----------------service----------------------------


	//--------------view--------------------------------

		/*
			���ܣ����������ĺ�������car_x,car_y �� ������ɫcar_colorչʾ��Ӧ������
		*/
	void car_view();

	/*
		���ܣ�����car_timer�������ɵ�ʱ�����ֵ������һ�����ֵ֮���ܹ�����������һ�����ֵ������car_routeʵʱ�޸�car_x������ car_move �޸�car_y������ʵʱ����car_viewչʾ������
		�����������������������ɵ�car_timer������һ������������ʱ��

	*/


	//--------------view--------------------------------
};
void cars_view();
