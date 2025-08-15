#include "game.h"
#include "button.h"
#include <windows.h>
/*



					   _oo0oo_
					  o8888888o
					  88" . "88
					  (| -_- |)
					  0\  =  /0
					___/`---'\___
				  .' \\|     |// '.
				 / \\|||  :  |||// \
				/ _||||| -:- |||||- \
			   |   | \\\  - /// |   |
			   | \_|  ''\---/''  |_/ |
			   \  .-\__  '-'  ___/-. /
			 ___'. .'  /--.--\  `. .'___
		  ."" '<  `.___\_<|>_/___.' >' "".
		 | | :  `- \`.;`\ _ /`;.`/ - ` : | |
		 \  \ `_.   \_ __\ /__ _/   .-` /  /
	 =====`-.____`.___ \_____/___.-`___.-'=====
					   `=---='

	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		 佛祖保佑     永不宕机     永无BUG



				  ___====-_  _-====___
			_--^^^#####//      \\#####^^^--_
		 _-^##########// (    ) \\##########^-_
		-############//  |\^^/|  \\############-
	  _/############//   (@::@)   \############\_
	 /#############((     \\//     ))#############\
	-###############\\    (oo)    //###############-
   -#################\\  / VV \  //#################-
  -###################\\/      \//###################-
 _#/|##########/\######(   /\   )######/\##########|\#_
 |/ |#/\#/\#/\/  \#/\##\  |  |  /##/\#/  \/\#/\#/\#| \|
 `  |/  V  V  `   V  \#\| |  | |/#/  V   '  V  V  \|  '
	`   `  `      `   / | |  | | \   '      '  '   '
					 (  | |  | |  )
					__\ | |  | | /__
				   (vvv(VVV)(VVV)vvv)

	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			   神兽保佑            永无BUG
*/

int score;
int waitnum;
// int kidnum;
int passnum;
int deadnum;
extern int flag;
ExMessage _msg;
extern MOUSEMSG msg;
vector<Cars *> cars_v;

Player joe(850, 0, 10);
Kids kid(500, 4, 0, 1000);
vector<Kids> kid_v;
// Kids kid_v[10];

extern IMAGE car_body[2];
void GameInit()
{
	loadimage(car_body, _T("resources/car/car11.jpg"), 135, 105);	 // 车身图片
	loadimage(car_body + 1, _T("resources/car/car2.jpg"), 135, 105); // 车身图片
	score = 0;
	waitnum = 10;
	passnum = 0;
	deadnum = 0;
	kid_v.clear();
	cars_v.clear();
	joe.player_x = 850;
}
bool IsWin()
{

	return false;
}
bool IsLost()
{
	return false;
}

int FPS(int f)
{
	static long long oldTime = 0;
	long long nowTime = clock();
	if (nowTime - oldTime >= f)
	{
		oldTime = nowTime;
		return 1;
	}
	return 0;
}

void GameView()
{
	int timi = 0;
	cout << "展示游戏界面" << endl;

	IMAGE game_bk;

	setfillcolor(BROWN);
	setcolor(YELLOW);
	loadimage(&game_bk, "resources/game_bk.jpg");
	while (flag == MY_GAME)
	{
		BeginBatchDraw();
		if (peekmessage(&_msg, EM_MOUSE | EM_KEY))
		{
			if (_msg.message)
			{
				switch (_msg.message)
				{
				case WM_LBUTTONDOWN: // 判断鼠标点击位置
					if (_msg.x >= window_width - textwidth("ESC") && _msg.x <= window_width && _msg.y >= 0 && _msg.y <= textheight("ESC"))
					{
						setfillcolor(YELLOW);
						setcolor(YELLOW);
						fillrectangle(window_width - textwidth("ESC"), 0, textwidth("ESC"), textheight("ESC"));
						flag = MY_PAUSE;
						return;
					}
					break;
				default:
					break;
				}
			}
		}

		// 每秒大约20帧
		if (FPS(50))
		{
			cleardevice();
			putimage(0, 0, &game_bk);
			GameScoreView();	  // 分数视图
			GameDeathView();	  // 死亡人数
			GamePassView();		  // 通过人数
			GameScoreTotalView(); // 目标分数

			KidGenerator();
			joe.makeflag();
			CarsView();
			joe.player_view();

			timi++;
			if (score > 0 && timi % 10 == 1)
				score--;

			if (deadnum >= 5)
			{
				flag = MY_LOSE;
				return;
			}
			if (!kid_v.size() && !waitnum)
			{
				if (score < goal)
				{
					flag = MY_LOSE;
					return;
				}
				else
				{
					flag = MY_WIN;
					return;
				}
			}

			KidsView();

			{ // 生成暂停按钮
				settextstyle(60, 0, _T("Consolas"));
				fillrectangle(window_width - textwidth("暂停"), 0, window_width, textheight("暂停"));
				outtextxy(window_width - textwidth("暂停"), 0, "暂停");
			}
			FlushBatchDraw();
		}
	}
}

void GameScoreView()
{
	settextcolor(BLACK);
	settextstyle(30, 0, _T("Consolas"));
	string text = "Score: " + to_string(score);
	outtextxy(score_x, score_y, _T(text.c_str()));
}

void GameScoreTotalView()
{
	settextcolor(BLACK);
	settextstyle(30, 0, _T("Consolas"));
	string text = "目标分数: " + to_string(goal);
	outtextxy(total_score_x, total_score_y, _T(text.c_str()));
}

void GameDeathView()
{
	settextcolor(BLACK);
	settextstyle(30, 0, _T("Consolas"));
	string text = "死亡数: " + to_string(deadnum);
	outtextxy(death_x, death_y, _T(text.c_str()));
}

void GamePassView()
{
	settextcolor(BLACK);
	settextstyle(30, 0, _T("Consolas"));
	string text = to_string(passnum);
	string _text = to_string(waitnum);
	if (text.size() < 2)
		text = "0" + text;
	if (_text.size() < 2)
		_text = "0" + _text;
	outtextxy(pass_x, pass_y, _T(text.c_str()));
	outtextxy(wait_x, wait_y, _T(_text.c_str()));
}

void WinView()
{
	IMAGE win_bk;
	int back_x = 0, back_y = window_height - 50;
	int restart_x = window_width - 200, restart_y = window_height - 50;
	Button back_button(back_x, back_y, 200, 50, "返回菜单", BROWN);
	Button over_button(restart_x, restart_y, 200, 50, "退出游戏", BROWN);
	loadimage(&win_bk, _T("resources/win.png"), window_width, window_height);

	BeginBatchDraw();
	while (flag == MY_WIN)
	{
		msg = GetMouseMsg();
		setbkcolor(RGB(191, 187, 177));
		cleardevice();
		putimage(0, 0, &win_bk);
		if (!back_button.TouchButton(YELLOW))
		{
			back_button.ShowButton(BROWN);
		}
		if (!over_button.TouchButton(YELLOW))
		{
			over_button.ShowButton(BROWN);
		}
		if (back_button.ClickButton())
		{
			flag = MY_MENU;
		}
		if (over_button.ClickButton())
		{
			GameInit();
			flag = MY_OVER;
		}
		FlushBatchDraw();
	}
}
void LoseView()
{
	IMAGE lose_bk;
	int back_x = 0, back_y = window_height - 50;
	int restart_x = window_width - 200, restart_y = window_height - 50;
	Button back_button(back_x, back_y, 200, 50, "返回菜单", BROWN);
	Button replay_button(restart_x, restart_y, 200, 50, "重新开始", BROWN);
	loadimage(&lose_bk, _T("resources/lose.jpg"), window_width, window_height);
	BeginBatchDraw();
	while (flag == MY_LOSE)
	{
		msg = GetMouseMsg();
		cleardevice();
		putimage(0, 0, &lose_bk);
		if (!back_button.TouchButton(YELLOW))
		{
			back_button.ShowButton(BROWN);
		}
		if (!replay_button.TouchButton(YELLOW))
		{
			replay_button.ShowButton(BROWN);
		}
		if (back_button.ClickButton())
		{
			flag = MY_MENU;
		}
		if (replay_button.ClickButton())
		{
			GameInit();
			flag = MY_GAME;
		}
		FlushBatchDraw();
	}
	return;
}
