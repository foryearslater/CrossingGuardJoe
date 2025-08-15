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
// extern vector<class Kids>kid_v;
/**
 * @class Car	������
 * @brief ע�⣺ÿ����һ��С������������ kid_v���μ�game.h��
 *		1.�������
 *			���ӵĺ����� kid_x
 *			����״̬ kid_flag : ��move 1    ͣstop 2   ��fuss 3  ����dead 4
 *			�������� kid_state : live 0     dead 1    arrived 2
 *			���ӵȴ�ʱ������ kid_time
 *			kid_speed
 *			С������λ�� kid_start
 *			С��Ŀ��λ�� kid_end
 *			ÿ��С��ͨ���ɵ÷��� kid_score
 *			С����ɫ kid_color:���ڸ�С�����ϲ�ͬ��ɫ
 *
 *		2.�������
 *			С��չʾ KidView
 *			С������չʾ KidDeadView
 *			С����ʱ kid_timer :���ڼ���С���ȴ�ʱ�䣬��ʱ����true
 *			С������ KidTrouble : ����С��
 *			С������ KidArrive : �����С����score�ӷ�
 *			С����ײ KidCrash : ��������iscrashing �����ж��Ƿ�ײ�� ��ײ���޸�state
 *			С���Ƿ�����ǰ����� KidWait: С��������ʱ����ǰ��ĵȴ�С��ʱ�Լ���״̬Ҳ�ı�ɵȴ�
 *			С���ƶ� KidMove
 *			����С�� KidGenerator:��ʼ��С�����꣬������ɿ�ѡ��ļ�����ɫ�е�һ��
 *			���ǰ���Ƿ���С�� isobstacle�����ǰ�� kid_x - width ��λ���Ƿ���С��
 */

class Kids
{
public:
	Kids(int kid_x, int kid_flag, int kid_state, int kid_time);

	~Kids();
	/**
	 * @brief	���ܣ������ӵ�״̬��kid_state����Ϊstop 2ʱ����ʱ��ʼ���ﵽʱ������kid_time��Ϊtrue;
	 *			�����ָ��ֹͣʱ���¼�ʱ��
	 */
	bool KidTimer1(/*Player player*/);

	bool KidTimer2(/*Player player*/);
	/*
	 * @brief	���ܣ� ������״̬kid_flag Ϊstopʱ ���ã�kid_timer) ������Ϊtrueʱ��С����ʼ��壬�޸�kid_flag Ϊfuss
	 *			���ã�KidIsobstacle()����Ϊtrue��4S��ǰ��С��������kid_v λ�ڸ�С��ǰһ����Ҳ��Ϊ����״̬
	 *									��Ϊfalse��4s��С��kid_flag ��Ϊmove
	 */
	void KidTrouble(int i);

	/*
	 * @brief ���ܣ����С�������꣨kid_x���Ƿ񵽴�Ŀ�ĵأ�kid_end���������score ���� kid_score, kid_state ��Ϊ arrived 2��������ȥ�����С��
	 */
	bool KidArrive();

	/*
	 * @brief	���ܣ���С��kid_flag Ϊ moveʱ С��kid_x��С ����λʱ�������Ϊ kid_speed
	 */
	void KidMove();

	/*
	 * @brief	���ܣ�����С������ײ�ˣ��޸Ķ�Ӧkid_state, ����С����Ŀ��deadnum�� + 1, �Ӷ���kid_v ȥ����Ӧ��С��
	 */
	void KidCrash();

	/*
	 * @brief	���ܣ����ǰ�� kid_x - width ��λ���Ƿ���С�������У��ж�ǰ��С��״̬kid_flag�Ƿ�Ϊstop�� ���򷵻�true
	 */
	bool KidIsobstacle(int i);

	/*
	 * @brief	���ܣ����С����״̬ kid_flag Ϊmove�򲻶ϵ��ã�KidIsobstacle()��������trueʱ�޸�С����״̬kid_flag
	 */
	void KidWait();

	/*
	 * @brief	���ܣ�����С������ʼ��С�������� kid_xstart,���һ����ɫkid_color�������С���������kid_q���棬waitnum - 1
	 */

	/*
	 * @brief	���ܣ�����С�����꣨kid_x , kid_y�����kid_state(�Ƿ�Ϊlive) С����ɫ��С��״̬��kid_flag��չʾС���Ͷ������ƶ����� ֹͣ���� ��嶯����
	 */
	void KidDeadView();

	/*
	 * @brief	���ܣ�չʾ����С��
	 */
	void KidScreamView();

	/*
	 * @brief	���ܣ�С������ʱ��չʾ���ڵ��ϵ���������
	 */
	void KidView();

	/*
	 * @brief	������Ķ�ʱ��
	 */
	int Timerx(int f);

	int KidSelect(vector<Kids> &kid_v, Player joe);

public:
	float y;
	int kid_x;
	int kid_flag;
	int kid_state;
	int kid_time;
	int be_select;
	/*int kid_speed;*/
	/*
	 * @brief		���ܣ���ǰ�Ƿ�ǿ��ֹͣ   ��ǿ��ֹͣ��Ϊ true ��һ����ʱ��������ʱ���Զ����
	 */
	bool kid_ob;
	/*
	 * @brief		���ܣ����ӱ�ײʱ��
	 */
	long long oldTime;
	long long old_time1;
	long long old_time2;
	IMAGE stand_image[3];

	IMAGE move_image[4];
	IMAGE move_image_y[2];
	int move_image_num;

	IMAGE scream[3];

	IMAGE death_image[2];
	// char kid_color;
};

/*
 * @brief		���ܣ�չʾ����С��
 */
void KidsView();

void KidMovelog();

void KidGenerator();
