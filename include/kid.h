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
		************注意：每生成一个小孩都会加入队列 kid_v（参见game.h）**************
	孩子类
		1.数据设计
			孩子的横坐标 kid_x
			孩子状态 kid_flag : 动move 1    停stop 2   闹fuss 3  死亡dead 4
			孩子生死 kid_state : live 0     dead 1    arrived 2
			孩子等待时间上限 kid_time
			kid_speed
			小孩出发位置 kid_start
			小孩目标位置 kid_end
			每个小孩通过可得分数 kid_score
			小孩颜色 kid_color:用于给小孩加上不同颜色

		2.函数设计
			小孩展示 kid_view
			小孩死亡展示 kid_dead_view
			小孩计时 kid_timer :用于计算小孩等待时间，超时返回true
			小孩闹腾 kid_trouble : 闹腾小孩
			小孩到达 kid_arrive : 到达的小孩给score加分
			小孩被撞 kid_crash : 根据汽车iscrashing 函数判断是否被撞， 被撞就修改state
			小孩是否遇到前面的人 kid_wait: 小孩在行走时遇到前面的等待小孩时自己的状态也改变成等待
			小孩移动 kid_move
			生成小孩 kid_generator:初始化小孩坐标，随机生成可选择的几种颜色中的一种
			检测前方是否有小孩 isobstacle：检测前方 kid_x - width 的位置是否有小孩
*/

class Kids {
	//----------------数据设计-----------------------------
public:
	float y;
	int kid_x;
	int kid_flag;
	int kid_state;
	int kid_time;
	int be_select;
	/*int kid_speed;*/
	bool kid_ob; // 当前是否被强制停止   被强制停止变为 true 加一个定时器，过了时间自动变成
	long long oldTime; // 孩子被撞时间                                             
	long long old_time1, old_time2;
	
	IMAGE stand_image[3];

	IMAGE move_image[4];
	IMAGE move_image_y[2];
	int move_image_num;

	IMAGE scream[3];

	IMAGE death_image[2];
	//char kid_color;

	Kids(int kid_x, int kid_flag, int kid_state, int kid_time);

	//----------------数据设计-----------------------------

	//--------------service--------------------------------
	~Kids();
	/*
		功能：当孩子的状态（kid_state）变为stop 2时，计时开始，达到时间上限kid_time变为true;
				（玩家指挥停止时重新计时）
	*/
	bool kid_timer1(/*Player player*/);

	bool kid_timer2(/*Player player*/);
	/*
		功能： 当孩子状态kid_flag 为stop时 调用（kid_timer) ，函数为true时，小孩开始起哄，修改kid_flag 为fuss
				调用（kid_isobstacle()）若为true，4S后前方小孩（队列kid_v 位于该小孩前一个）也变为闹腾状态
										若为false，4s后小孩kid_flag 改为move
	*/
	void kid_trouble(int i);

	/*

		功能：检测小孩横坐标（kid_x）是否到达目的地（kid_end），若到达，score 加上 kid_score, kid_state 改为 arrived 2，队列中去掉这个小孩
	*/
	bool kid_arrive();

	/*

		功能：当小孩kid_flag 为 move时 小孩kid_x减小 ，单位时间减少量为 kid_speed
	*/
	void kid_move();

	/*

		功能：现在小孩被车撞了，修改对应kid_state, 死亡小孩数目（deadnum） + 1, 从队列kid_v 去掉对应的小孩
	*/
	void kid_crash();

	/*
		功能：检测前方 kid_x - width 的位置是否有小孩，若有，判断前方小孩状态kid_flag是否为stop， 是则返回true
	*/
	bool kid_isobstacle(int i);

	/*
		功能：如果小孩的状态 kid_flag 为move则不断调用（kid_isobstacle()），返回true时修改小孩的状态kid_flag
	*/
	void kid_wait();

	/*
		功能：生成小孩，初始化小孩横坐标 kid_xstart,随机一种颜色kid_color，将这个小孩加入队列kid_q里面，waitnum - 1
	*/
	

	//-----------------------service--------------------------------


	//--------------------view--------------------------------------

		/*
			功能：根据小孩坐标（kid_x , kid_y）检测kid_state(是否为live) 小孩颜色，小孩状态（kid_flag）展示小孩和动作（移动动作 停止动作 起哄动作）
		*/
   void kid_dead_view();

	/*
		功能：展示所有小孩
	*/
   void kid_scream_view();


	void kid_view();

	/*
		功能：小孩死亡时，展示躺在地上的死亡画面
	*/
	


	/*
		死亡后的定时器
	*/
	int timerx(int f);

	int kid_select(vector<Kids>& kid_v, Player joe);

	//---------------------view--------------------------------
};

/*
		功能：展示所有小孩
*/
void kids_view();

void kid_movelog();

void kid_generator();
