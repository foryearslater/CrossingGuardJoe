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
 * @class Car	孩子类
 * @brief 注意：每生成一个小孩都会加入队列 kid_v（参见game.h）
 *		1.数据设计
 *			孩子的横坐标 kid_x
 *			孩子状态 kid_flag : 动move 1    停stop 2   闹fuss 3  死亡dead 4
 *			孩子生死 kid_state : live 0     dead 1    arrived 2
 *			孩子等待时间上限 kid_time
 *			kid_speed
 *			小孩出发位置 kid_start
 *			小孩目标位置 kid_end
 *			每个小孩通过可得分数 kid_score
 *			小孩颜色 kid_color:用于给小孩加上不同颜色
 *
 *		2.函数设计
 *			小孩展示 KidView
 *			小孩死亡展示 KidDeadView
 *			小孩计时 kid_timer :用于计算小孩等待时间，超时返回true
 *			小孩闹腾 KidTrouble : 闹腾小孩
 *			小孩到达 KidArrive : 到达的小孩给score加分
 *			小孩被撞 KidCrash : 根据汽车iscrashing 函数判断是否被撞， 被撞就修改state
 *			小孩是否遇到前面的人 KidWait: 小孩在行走时遇到前面的等待小孩时自己的状态也改变成等待
 *			小孩移动 KidMove
 *			生成小孩 KidGenerator:初始化小孩坐标，随机生成可选择的几种颜色中的一种
 *			检测前方是否有小孩 isobstacle：检测前方 kid_x - width 的位置是否有小孩
 */

class Kids
{
public:
	Kids(int kid_x, int kid_flag, int kid_state, int kid_time);

	~Kids();
	/**
	 * @brief	功能：当孩子的状态（kid_state）变为stop 2时，计时开始，达到时间上限kid_time变为true;
	 *			（玩家指挥停止时重新计时）
	 */
	bool KidTimer1(/*Player player*/);

	bool KidTimer2(/*Player player*/);
	/*
	 * @brief	功能： 当孩子状态kid_flag 为stop时 调用（kid_timer) ，函数为true时，小孩开始起哄，修改kid_flag 为fuss
	 *			调用（KidIsobstacle()）若为true，4S后前方小孩（队列kid_v 位于该小孩前一个）也变为闹腾状态
	 *									若为false，4s后小孩kid_flag 改为move
	 */
	void KidTrouble(int i);

	/*
	 * @brief 功能：检测小孩横坐标（kid_x）是否到达目的地（kid_end），若到达，score 加上 kid_score, kid_state 改为 arrived 2，队列中去掉这个小孩
	 */
	bool KidArrive();

	/*
	 * @brief	功能：当小孩kid_flag 为 move时 小孩kid_x减小 ，单位时间减少量为 kid_speed
	 */
	void KidMove();

	/*
	 * @brief	功能：现在小孩被车撞了，修改对应kid_state, 死亡小孩数目（deadnum） + 1, 从队列kid_v 去掉对应的小孩
	 */
	void KidCrash();

	/*
	 * @brief	功能：检测前方 kid_x - width 的位置是否有小孩，若有，判断前方小孩状态kid_flag是否为stop， 是则返回true
	 */
	bool KidIsobstacle(int i);

	/*
	 * @brief	功能：如果小孩的状态 kid_flag 为move则不断调用（KidIsobstacle()），返回true时修改小孩的状态kid_flag
	 */
	void KidWait();

	/*
	 * @brief	功能：生成小孩，初始化小孩横坐标 kid_xstart,随机一种颜色kid_color，将这个小孩加入队列kid_q里面，waitnum - 1
	 */

	/*
	 * @brief	功能：根据小孩坐标（kid_x , kid_y）检测kid_state(是否为live) 小孩颜色，小孩状态（kid_flag）展示小孩和动作（移动动作 停止动作 起哄动作）
	 */
	void KidDeadView();

	/*
	 * @brief	功能：展示所有小孩
	 */
	void KidScreamView();

	/*
	 * @brief	功能：小孩死亡时，展示躺在地上的死亡画面
	 */
	void KidView();

	/*
	 * @brief	死亡后的定时器
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
	 * @brief		功能：当前是否被强制停止   被强制停止变为 true 加一个定时器，过了时间自动变成
	 */
	bool kid_ob;
	/*
	 * @brief		功能：孩子被撞时间
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
 * @brief		功能：展示所有小孩
 */
void KidsView();

void KidMovelog();

void KidGenerator();
