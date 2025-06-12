#include "kid.h"
#include <chrono>

#pragma comment( lib, "MSIMG32.LIB")

int Kids::timerx(int f) {
	long long nowTime = clock();
	if (nowTime - oldTime >= f) {
		return 0;
	}
	return 1;
}



Kids::Kids(int kid_x, int kid_flag, int kid_state, int kid_time)
{
	this->y = kid_y;
	this->kid_x = kid_x;
	this->kid_flag = kid_flag;
	this->kid_state = kid_state;
	this->kid_time = kid_time;
	this->move_image_num=0;
	this->kid_ob = 0;
	this->be_select = 0;

	long long old_time1 = INT64_MAX;
	long long old_time2 = INT64_MAX;

	loadimage(&stand_image[0], "resources/child/child_stand.png", 60, 80);
	loadimage(&stand_image[1], "resources/child/child_stand_y.png", 60, 80);
	loadimage(&stand_image[2], "resources/child/child_stand_s.png", 60, 80);
	//加载行走图片1
	loadimage(&this->move_image[0], "resources/child/child_move/move1.png", 60, 80);
	loadimage(&this->move_image_y[0], "resources/child/child_move/move1_y.png", 60, 80);
	loadimage(&this->move_image[2], "resources/child/child_move/move1_s.png", 60, 80);
	//加载行走图片2
	loadimage(&this->move_image[1], "resources/child/child_move/move2.png", 60, 80);
	loadimage(&this->move_image_y[1], "resources/child/child_move/move2_y.png", 60, 80);
	loadimage(&this->move_image[3], "resources/child/child_move/move2_s.png", 60, 80);

	loadimage(&death_image[0], "resources/child/child_death.png", 60, 80);
	loadimage(&death_image[1], "resources/child/child_death_y.png", 60, 80);

	loadimage(&scream[0], "resources/child/child_scream.png", 60, 80);
	loadimage(&scream[1], "resources/child/child_scream_y.png", 60, 80);
	loadimage(&scream[2], "resources/child/child_scream_s.png", 60, 80);
}

Kids::~Kids() {}


bool Kids::kid_timer1() {
	if (kid_flag == 2)
	{
		long long new_time = clock();
		/*if (kid_flag == 1 || kid_ob)
		{
			old_time1 = new_time;
			return false;
		}*/
		if (new_time - old_time1 > kid_time)
		{
			return true;
		}
	}
	return false;
}

bool Kids::kid_timer2() {
	if (kid_flag == 2)
	{
		long long new_time = clock();
		/*if (kid_flag == 1 || kid_ob)
		{
			old_time2 = new_time;
			return false;
		}*/
		if (new_time - old_time2 > kid_time)
		{
			return true;
		}
	}
	return false;
}

void Kids::kid_trouble(int i) {
	if (kid_flag == 2)
	{

		if (kid_timer1())
		{
			kid_flag = 3;
			kid_v[i].kid_ob = false;
			kid_v[i].old_time1 = INT64_MAX;
			kid_v[i].old_time2 = clock();
		}
	}
}
bool Kids::kid_arrive()
{

	return false;
}

void Kids::kid_move()
{
	if (this->be_select == 1)
	{
		putimage(this->kid_x, 560, &(this->move_image_y[this->move_image_num]), SRCAND);
		putimage(this->kid_x, 560, &(this->move_image[this->move_image_num + 2]), SRCPAINT);

	}
	else
	{
		putimage(this->kid_x, 560, &(this->move_image_y[this->move_image_num]), SRCAND);
		putimage(this->kid_x, 560, &(this->move_image[this->move_image_num]), SRCPAINT);
	}

	if (this->move_image_num == 0) {
		this->move_image_num = 1;
	}
	else {
		this->move_image_num = 0;
	}
	kid_x -= 3;
}

bool Kids::kid_isobstacle(int i) {
	if (kid_v[i].kid_x - kid_v[i - 1].kid_x <= WIDTH) return true;
	return false;
}


void Kids::kid_wait()
{
	if (this->be_select == 1)
	{
		putimage(this->kid_x, 560, &this->stand_image[1], SRCAND);
		putimage(this->kid_x, 560, &this->stand_image[2], SRCPAINT);
	}
	else
	{
		putimage(this->kid_x, 560, &this->stand_image[1], SRCAND);
		putimage(this->kid_x, 560, &this->stand_image[0], SRCPAINT);
	}
}



void Kids::kid_dead_view()
{
	if (this->timerx(3000)) {
		putimage(this->kid_x, y += (float)car_speed - 1.3, &this->death_image[1], SRCAND);
		putimage(this->kid_x, y += (float)car_speed - 1.3, &this->death_image[0], SRCPAINT);

	}
	else {
		this->kid_state = 1;

	}
}


void Kids::kid_scream_view()
{
	if (this->be_select == 1)
	{
		putimage(this->kid_x, 560, &this->scream[1], SRCAND);
		putimage(this->kid_x, 560, &this->scream[2], SRCPAINT);
	}
	else
	{
		putimage(this->kid_x, 560, &this->scream[1], SRCAND);
		putimage(this->kid_x, 560, &this->scream[0], SRCPAINT);
	}
}

void Kids::kid_view()
{
	switch (this->kid_flag)
	{
	case 1:
		this->kid_move();
		break;
	case 2:
		this->kid_wait();
		break;
	case 3:
		this->kid_scream_view();
		break;
	case 4:
		this->kid_dead_view();
		break;
	
	default:
		break;
	}
}
int Kids::kid_select(vector<Kids>& kid_v, Player joe)
{
	int num = 0;
	for (vector<Kids>::iterator i = kid_v.begin(); i != kid_v.end(); ++i)
	{

		if ((*i).kid_x >= joe.player_x -10 && (*i).kid_x <= joe.player_x + 30 && (*i).kid_flag != 4)
		{
			return num;
		}

		num++;
		(*i).be_select = 0;
	}
	return -1;
}

void kid_movelog() {

	for (int i = 0; i < kid_v.size(); i++)
	{
		//小孩队伍被指挥(某一个小孩2前面有小孩1，小孩1正在走路，小孩2停止，则小孩2也开始走路）
		if ((i >= 1) && !kid_v[i].kid_ob && kid_v[i].kid_flag == 2 && kid_v[i].kid_isobstacle(i) && kid_v[i - 1].kid_flag == 1 && kid_v[i - 1].kid_state == 0 && kid_v[i].kid_state == 0 && kid_v[i-1].kid_flag !=4)
		{
			kid_v[i].kid_flag = 1;
		}
		// 小孩队伍被停止
		if ((i >= 1) && kid_v[i].kid_flag == 1 && kid_v[i].kid_isobstacle(i) && kid_v[i - 1].kid_flag != 1 && kid_v[i - 1].kid_state == 0 && kid_v[i].kid_state == 0 && kid_v[i - 1].kid_flag != 4)
		{
			kid_v[i].kid_flag = 2;
			kid_v[i].old_time1 = clock();

		}
		//小孩不耐烦
		kid_v[i].kid_trouble(i);

		//小孩不耐烦准备移动
		if (kid_v[i].kid_flag == 3)
		{
			long long new_time = clock();
			if (new_time - kid_v[i].old_time2 <= kid_v[i].kid_time)
			{
				continue;
			}
			kid_v[i].old_time2 = INT64_MAX;

			kid_v[i].kid_ob = false;
			kid_v[i].kid_flag = 1;//小孩收到指挥开始移动
		}
	}

}

void kid_generator()
{
	if(!kid_v.size() && waitnum){
		for (int i = 0; i < 5; i++ , waitnum --)
		{
			Kids  kid(1200 + 50 * i, 1, 0, 3000);
			//kid_v.push_back(kid);
			kid_v.push_back(kid);
		}
	}
}


void kids_view() {
	//kid_generator();
	if (!kid_v.empty()) {
		kid_movelog();
	}
	
	//for (auto it = kid_v.begin(); it != kid_v.end(); ++it) {
	//	if(it->kid_state ==  0)
	//		it->kid_view();
	//}
	if (!kid_v.empty() && kid_v[0].kid_x == 1000)
	{
		//kid_v[0].kid_ob = true;
		//kid_v[0].kid_flag = 2;
		//kid_v[0].kid_x--;
	}
	for(int i = 0;i< kid_v.size();i++){
		if (kid_v[i].kid_x <= 150) {
			kid_v[i].kid_state = 2;
			passnum++;
			score += 200;
		}
		if (kid_v[i].kid_state == 0)
		{
			if (kid_v[i].kid_select(kid_v, joe) != -1)
			{
				kid_v[kid_v[i].kid_select(kid_v, joe)].be_select = 1;
			}
         kid_v[i].kid_view();
		}
			
		else {
			kid_v.erase(kid_v.begin() + i);
			i--;
		}
	}
}


