#pragma once
#include <easyx.h>
#include "loadimage.h"
#include <graphics.h>
#include <string>
#include<iostream>
using namespace std;
#ifdef UNICODE
#undef UNICODE
#endif


class Button {
public:
	Button(int a, int b, int _width, int _height, const TCHAR* _text, int fill_colour);
	bool touch_button(int newcolor);
	bool click_button();
	void show_button(int color);


private:
	int x;
	int y;
	int width;
	int height;
	const TCHAR* text;
};