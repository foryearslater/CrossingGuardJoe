#pragma once
#include "player.h"
#include "game.h"
#include <graphics.h>	
#include <conio.h>

#ifdef UNICODE
#undef UNICODE
#endif
using namespace std;
extern class Player joe;
extern int waitnunm;
extern int score;
//extern vector<class Kids>kid_v;
/*
		************ע�⣺ÿ����һ��С������������ kid_v���μ�game.h��**************
	������
		1.�������
			���ӵĺ����� kid_x
			����״̬ kid_flag : ��move 1    ͣstop 2   ��fuss 3  ����dead 4
			�������� kid_state : live 0     dead 1    arrived 2
			���ӵȴ�ʱ������ kid_time
			kid_speed
			С������λ�� kid_start
			С��Ŀ��λ�� kid_end
			ÿ��С��ͨ���ɵ÷��� kid_score
			С����ɫ kid_color:���ڸ�С�����ϲ�ͬ��ɫ

		2.�������
			С��չʾ kid_view
			С������չʾ kid_dead_view
			С����ʱ kid_timer :���ڼ���С���ȴ�ʱ�䣬��ʱ����true
			С������ kid_trouble : ����С��
			С������ kid_arrive : �����С����score�ӷ�
			С����ײ kid_crash : ��������iscrashing �����ж��Ƿ�ײ�� ��ײ���޸�state
			С���Ƿ�����ǰ����� kid_wait: С��������ʱ����ǰ��ĵȴ�С��ʱ�Լ���״̬Ҳ�ı�ɵȴ�
			С���ƶ� kid_move
			����С�� kid_generator:��ʼ��С�����꣬������ɿ�ѡ��ļ�����ɫ�е�һ��
			���ǰ���Ƿ���С�� isobstacle�����ǰ�� kid_x - width ��λ���Ƿ���С��
*/

class Kids {
	//----------------�������-----------------------------
public:
	float y;
	int kid_x;
	int kid_flag;
	int kid_state;
	int kid_time;
	int be_select;
	/*int kid_speed;*/
	bool kid_ob; // ��ǰ�Ƿ�ǿ��ֹͣ   ��ǿ��ֹͣ��Ϊ true ��һ����ʱ��������ʱ���Զ����
	long long oldTime; // ���ӱ�ײʱ��                                             
	long long old_time1, old_time2;
	
	IMAGE stand_image[3];

	IMAGE move_image[4];
	IMAGE move_image_y[2];
	int move_image_num;

	IMAGE scream[3];

	IMAGE death_image[2];
	//char kid_color;

	Kids(int kid_x, int kid_flag, int kid_state, int kid_time);

	//----------------�������-----------------------------

	//--------------service--------------------------------
	~Kids();
	/*
		���ܣ������ӵ�״̬��kid_state����Ϊstop 2ʱ����ʱ��ʼ���ﵽʱ������kid_time��Ϊtrue;
				�����ָ��ֹͣʱ���¼�ʱ��
	*/
	bool kid_timer1(/*Player player*/);

	bool kid_timer2(/*Player player*/);
	/*
		���ܣ� ������״̬kid_flag Ϊstopʱ ���ã�kid_timer) ������Ϊtrueʱ��С����ʼ��壬�޸�kid_flag Ϊfuss
				���ã�kid_isobstacle()����Ϊtrue��4S��ǰ��С��������kid_v λ�ڸ�С��ǰһ����Ҳ��Ϊ����״̬
										��Ϊfalse��4s��С��kid_flag ��Ϊmove
	*/
	void kid_trouble(int i);

	/*

		���ܣ����С�������꣨kid_x���Ƿ񵽴�Ŀ�ĵأ�kid_end���������score ���� kid_score, kid_state ��Ϊ arrived 2��������ȥ�����С��
	*/
	bool kid_arrive();

	/*

		���ܣ���С��kid_flag Ϊ moveʱ С��kid_x��С ����λʱ�������Ϊ kid_speed
	*/
	void kid_move();

	/*

		���ܣ�����С������ײ�ˣ��޸Ķ�Ӧkid_state, ����С����Ŀ��deadnum�� + 1, �Ӷ���kid_v ȥ����Ӧ��С��
	*/
	void kid_crash();

	/*
		���ܣ����ǰ�� kid_x - width ��λ���Ƿ���С�������У��ж�ǰ��С��״̬kid_flag�Ƿ�Ϊstop�� ���򷵻�true
	*/
	bool kid_isobstacle(int i);

	/*
		���ܣ����С����״̬ kid_flag Ϊmove�򲻶ϵ��ã�kid_isobstacle()��������trueʱ�޸�С����״̬kid_flag
	*/
	void kid_wait();

	/*
		���ܣ�����С������ʼ��С�������� kid_xstart,���һ����ɫkid_color�������С���������kid_q���棬waitnum - 1
	*/
	

	//-----------------------service--------------------------------


	//--------------------view--------------------------------------

		/*
			���ܣ�����С�����꣨kid_x , kid_y�����kid_state(�Ƿ�Ϊlive) С����ɫ��С��״̬��kid_flag��չʾС���Ͷ������ƶ����� ֹͣ���� ��嶯����
		*/
   void kid_dead_view();

	/*
		���ܣ�չʾ����С��
	*/
   void kid_scream_view();


	void kid_view();

	/*
		���ܣ�С������ʱ��չʾ���ڵ��ϵ���������
	*/
	


	/*
		������Ķ�ʱ��
	*/
	int timerx(int f);

	int kid_select(vector<Kids>& kid_v, Player joe);

	//---------------------view--------------------------------
};

/*
		���ܣ�չʾ����С��
*/
void kids_view();

void kid_movelog();

void kid_generator();
