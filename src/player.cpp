#include "player.h"

Player::Player(int player_x, int player_flag, int player_speed)
{
	this->player_x = player_x;
	this->player_flag = player_flag;
	this->player_speed = player_speed;
	this->player_width = WIDTH;
	// 初始为第一帧图片
	this->move_left_num = 0;
	this->move_right_num = 0;
	this->be_hit_left_num = 0;
	this->be_hit_right_num = 0;
	// 加载站立图片
	loadimage(&stand_image[0], "resources/man/standing/Guard46.png", 100, 130);
	loadimage(&stand_image[1], "resources/man/standing/Guard46_y.png", 100, 130);

	// 加载左走图片
	for (int i = 46; i < 55; i++)
	{
		char filename[60] = "";
		sprintf(filename, "resources/man/move_left/Guard%d.png", i);
		loadimage(this->move_left_image + i - 46, filename, 100, 130);
		// 这里是左掩码图的批量加载
		char filename_y[60] = "";
		sprintf(filename_y, "resources/man/move_left/Guard%d_y.png", i);
		loadimage(this->move_left_image_y + i - 46, filename_y, 100, 130);
	}
	// 加载右走图片
	for (int i = 54; i < 63; i++)
	{
		char filename[60] = "";
		sprintf(filename, "resources/man/move_right/Guard%d.png", i);
		loadimage(this->move_right_image + i - 54, filename, 100, 130);
		// 这里是右掩码图的批量加载
		char filename_y[60] = "";
		sprintf(filename_y, "resources/man/move_right/Guard%d_y.png", i);
		loadimage(this->move_right_image_y + i - 54, filename_y, 100, 130);
	}
	// 加载被撞击到左图片
	for (int i = 36; i < 40; i++)
	{
		char filename[60] = "";
		sprintf(filename, "resources/man/be_hit/be_hit_left/Guard%d.png", i);
		loadimage(this->be_hit_left_image + i - 36, filename, 100, 130);
		// 这里是左掩码图的批量加载
		char filename_y[60] = "";
		sprintf(filename_y, "resources/man/be_hit/be_hit_left/Guard%d_y.png", i);
		loadimage(this->be_hit_left_image_y + i - 36, filename_y, 100, 130);
	}
	// 加载被撞击到右图片
	for (int i = 35; i < 39; i++)
	{
		char filename[60] = "";
		sprintf(filename, "resources/man/be_hit/be_hit_right/Guard%d.png", i);
		loadimage(this->be_hit_right_image + i - 35, filename, 100, 130);
		// 这里是左掩码图的批量加载
		char filename_y[60] = "";
		sprintf(filename_y, "resources/man/be_hit/be_hit_right/Guard%d_y.png", i);
		loadimage(this->be_hit_right_image_y + i - 35, filename_y, 100, 130);
	}
	// 加载指挥行走图片
	loadimage(&this->move_command_image, "resources/man/move_command/Guard71.png", 100, 130);
	loadimage(&this->move_command_image_y, "resources/man/move_command/Guard71_y.png", 100, 130);
	// 加载指挥停下图片
	loadimage(&this->stop_command_image, "resources/man/stop_command/Guard1.png", 100, 130);
	loadimage(&this->stop_command_image_y, "resources/man/stop_command/Guard1_y.png", 100, 130);
}

void Player::player_stand()
{
	putimage(this->player_x, 480, &this->stand_image[1], SRCAND);
	putimage(this->player_x, 480, &this->stand_image[0], SRCPAINT);
}

void Player::move_command(vector<Kids> &kid_v, Player joe)
{
	putimage(this->player_x, 480, &this->move_command_image_y, SRCAND);
	putimage(this->player_x, 480, &this->move_command_image, SRCPAINT);

	for (int i = 0; i < kid_v.size(); i++)
	{
		int kid_num = kid_v[i].KidSelect(kid_v, joe);
		if (kid_num != -1)
		{

			kid_v[kid_num].kid_flag = 1;
			kid_v[kid_num].kid_ob = false;
			kid_v[kid_num].old_time1 = INT64_MAX;
			kid_v[kid_num].old_time2 = INT64_MAX;
		}
	}
}

void Player::stop_command(vector<Kids> &kid_v, Player joe)
{
	putimage(this->player_x, 480, &this->stop_command_image_y, SRCAND);
	putimage(this->player_x, 480, &this->stop_command_image, SRCPAINT);

	for (int i = 0; i < kid_v.size(); i++)
	{
		int kid_num = kid_v[i].KidSelect(kid_v, joe);
		if (kid_num != -1)
		{

			kid_v[kid_num].kid_flag = 2;
			kid_v[kid_num].kid_ob = true;
			kid_v[kid_num].old_time1 = clock();
		}
	}
}

void Player::player_be_hit()
{
	if (this->player_flag == 5)
	{
		this->player_x -= 20;
		putimage(this->player_x, 480, this->be_hit_left_image_y + this->be_hit_left_num, SRCAND);
		putimage(this->player_x, 480, this->be_hit_left_image + this->be_hit_left_num, SRCPAINT);
		/*Sleep(600);*/
		this->be_hit_left_num++;
		if (this->be_hit_left_num == 4)
		{
			this->be_hit_left_num = 0;
			this->player_flag = 0;
		}
	}
	else
	{
		this->player_x += 20;
		putimage(this->player_x, 480, this->be_hit_right_image_y + this->be_hit_right_num, SRCAND);
		putimage(this->player_x, 480, this->be_hit_right_image + this->be_hit_right_num, SRCPAINT);
		/*Sleep(600);*/
		this->be_hit_right_num++;
		if (this->be_hit_right_num == 4)
		{
			this->be_hit_right_num = 0;
			this->player_flag = 0;
		}
	}
}

void Player::player_moving()
{

	if (this->player_flag == 3)
	{
		putimage(this->player_x, 480, this->move_left_image_y + this->move_left_num, SRCAND);
		putimage(this->player_x, 480, this->move_left_image + this->move_left_num, SRCPAINT);
		if (this->player_x >= 50)
		{
			this->player_x -= this->player_speed;
		}
		this->move_left_num++;
		/*Sleep(60);*/
		if (this->move_left_num == 8)
			this->move_left_num = 0;
	}
	else
	{
		putimage(this->player_x, 480, this->move_right_image_y + this->move_right_num, SRCAND);
		putimage(this->player_x, 480, this->move_right_image + this->move_right_num, SRCPAINT);

		if (this->player_x <= 1080)
		{
			this->player_x += this->player_speed;
		}
		this->move_right_num++;
		/*Sleep(60);*/
		if (this->move_right_num == 8)
			this->move_right_num = 0;
	}
}

void Player::makeflag()
{
	/*cout << "按键控制" << endl;*/
	if (GetAsyncKeyState(0x4A))
	{
		this->player_flag = 1;
	}
	else if (GetAsyncKeyState(0x4B))
	{
		this->player_flag = 2;
	}
	else if (GetAsyncKeyState(0x41))
	{
		this->player_flag = 3;
	}
	else if (GetAsyncKeyState(0x44))
	{
		this->player_flag = 4;
	}
	else
	{
		this->player_flag = 0;
	}
}

void Player::player_view()
{

	// cleardevice();
	switch (this->player_flag)
	{

	case 0:
		this->player_stand();
		break;
	case 1:
		this->move_command(kid_v, joe);
		break;
	case 2:
		this->stop_command(kid_v, joe);
		break;
	case 3:
	case 4:
		this->player_moving();
		break;
	case 5:
	case 6:

		this->player_be_hit();
		break;

	default:
		break;
	}
}