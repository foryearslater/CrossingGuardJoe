#pragma once
#include <easyx.h>
#include "loadimage.h"
#include <graphics.h>
#include <string>
#include <iostream>
#ifdef UNICODE
#undef UNICODE
#endif

class Button
{
public:
	Button(int a, int b, int _width, int _height, const TCHAR *_text, int fill_colour);
	bool TouchButton(int newcolor);
	bool ClickButton();
	void ShowButton(int color);

private:
	int x;
	int y;
	int width;
	int height;
	const TCHAR *text;
};