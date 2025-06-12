#include "button.h"
extern MOUSEMSG msg;
using namespace std;
Button::Button(int a, int b, int _width, int _height, const TCHAR* _text, int fill_colour) :x(a), y(b), width(_width), height(_height), text(_text) {};
bool Button::touch_button(int newcolour) {
    if (msg.x >= this->x && msg.x <= this->x + this->width &&
        msg.y >= this->y && msg.y <= this->y + this->height) {
        show_button(YELLOW);
        return 1;
    }
    return 0;
}
bool Button::click_button() {
    if (msg.uMsg == WM_LBUTTONDOWN) {
        if (msg.x >= this->x && msg.x <= x + this->width &&
            msg.y >= this->y && msg.y <= y + this->height) {
            return true;
        }
    }
    return false;
}
void Button::show_button(int color) {
    setbkmode(TRANSPARENT);
    setfillcolor(color);
    fillroundrect(this->x, this->y, this->x + this->width, this->y + this->height, 0, 0);
    TCHAR s1[50] = "ºÚÌå";
    settextstyle(50, 0, s1);
    settextcolor(WHITE);
    int tx = this->x + (this->width - textwidth(this->text)) / 2;
    int ty = this->y + (this->height - textheight(this->text)) / 2;
    outtextxy(tx, ty, this->text);
}

