#pragma once
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <graphics.h>
#include <easyx.h>
#include <algorithm>
#include <time.h>
#include <queue>
#include <vector>
#include <string>
#include <sstream>

#include "game.h"
#include "button.h"

class Application
{
public:
	void controller();

	void menu_view();

	void setting_view();

	void help_view();

	void PauseView();

private:
	IMAGE menu_bk;
	IMAGE img;
	int pre_flag = MY_MENU;
	bool MUS = 1;
	vector<Cars *> cars_v;
};