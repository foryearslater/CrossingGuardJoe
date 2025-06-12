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
#include <cstring>
#include <string>
#include <sstream>
#include <cstdio>
#include "game.h"
#include "button.h"

void controller();

void menu_view();

void setting_view();

void help_view();


using namespace std;
IMAGE menu_bk;
IMAGE img;
int flag = MY_MENU;
int pre_flag = MY_MENU;
bool MUS = 1;
extern vector<Cars*> cars_v;
MOUSEMSG msg;

int main() {
    mciSendString(_T("open resources/bgm1.mp3 alias bkmusic"), NULL, 0, NULL);
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
    initgraph(window_width, window_height, SHOWCONSOLE);
    setbkcolor(WHITE);

    controller();
    return 0;
}

void controller() {
    while (1) {

        switch (flag) {
        case MY_MENU:
            pre_flag = MY_MENU;
            menu_view();
            break;
        case MY_SETTING:
            setting_view();
            break;
        case MY_GAME:
            
            cout << "加载游戏界面" << endl;
            
            game_view();
            break;
        case MY_LOSE:
            lose_view();
            break;
        case MY_WIN:
            win_view();
            break;
        case MY_HELP:
            help_view();
            break;
        case MY_PAUSE:
            pre_flag = MY_PAUSE;
            pause_view();
            break;
        case MY_OVER:
            exit(0);
        }
    }
}

void menu_view() {

    Button game_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + default_height,
        four_text_w, default_height, "开始游戏", BROWN);
    Button setting_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + 2 * default_height,
        four_text_w, default_height, "设置", BROWN);
    Button help_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + 3 * default_height,
        four_text_w, default_height, "帮助", BROWN);
    Button over_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + 4 * default_height,
        four_text_w, default_height, "退出游戏", BROWN);
    BeginBatchDraw();
    cleardevice();
    loadimage(&menu_bk, ("resources/menubk.jpg"), getwidth(), getheight());
    putimage(0, 0, &menu_bk);

    while (flag == MY_MENU)
    {

        msg = GetMouseMsg();

        if (!game_button.touch_button(YELLOW)) {
            game_button.show_button(BROWN);
        }
        if (!setting_button.touch_button(YELLOW)) {
            setting_button.show_button(BROWN);
        }
        if (!help_button.touch_button(YELLOW)) {
            help_button.show_button(BROWN);
        }
        if (!over_button.touch_button(YELLOW)) {
            over_button.show_button(BROWN);
        }
        if (game_button.click_button()) {
            flag = MY_GAME;
            game_init();
            cout << "跳转到游戏界面" << endl;
        }
        else if (setting_button.click_button()) {
            flag = MY_SETTING;
        }
        else if (help_button.click_button()) {
            flag = MY_HELP;
        }
        else if (over_button.click_button()) {
            flag = MY_OVER;
        }
        FlushBatchDraw();
    }

}

void setting_view() {
    Button return_button(1000, 650, 100, 50, "返回", BROWN);
    Button muson_button(500, 450, 150, 50, "音乐开", BROWN);
    Button musoff_button(500, 450, 150, 50, "音乐关", YELLOW);
    setbkcolor(RGB(191, 187, 177));
    BeginBatchDraw();
    while (flag == MY_SETTING)
    {
        cleardevice();
        msg = GetMouseMsg();
        if (!return_button.touch_button(YELLOW)) {
            return_button.show_button(BROWN);
        }
        if (MUS==1){
            muson_button.show_button(BROWN);
            if (muson_button.click_button())
            {
                mciSendString(_T("close bkmusic"), NULL, 0, NULL);
                MUS = 0;
            }
        }
        else if (MUS == 0) {
            musoff_button.show_button(YELLOW);
            if (musoff_button.click_button())
            {
                mciSendString(_T("open resources/bgm1.mp3 alias bkmusic"), NULL, 0, NULL);//播放音乐
                mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
                MUS = 1;
            }
        }
        settextcolor(WHITE);
        settextstyle(50, 0, _T("Consolas"));
        outtextxy(500, 500, _T("敬请期待"));
        if (return_button.click_button()) {
            flag = pre_flag;
        }
        FlushBatchDraw();
    }

}
void help_view() {
    Button return_button(1000, 650, 100, 50, "返回", BROWN);
    setbkcolor(RGB(191, 187, 177));
    BeginBatchDraw();
    loadimage(&img, "resources/游戏帮助.png",window_width,window_height);
    while (flag == MY_HELP)
    {

        cleardevice();
        msg = GetMouseMsg();
        putimage(0, 0, &img);

        if (!return_button.touch_button(YELLOW)) {
            return_button.show_button(BROWN);
        }

        if (return_button.click_button()) {
            flag = pre_flag;
        }
        FlushBatchDraw();
    }
}
void pause_view() {
    IMAGE game_bk;

    Button continue_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + 0 * default_height,
        four_text_w, default_height, "继续游戏", BROWN);
    Button setting_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + 1 * default_height,
        four_text_w, default_height, "设置", BROWN);
    Button help_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + 2 * default_height,
        four_text_w, default_height, "帮助", BROWN);
    Button menu_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + 3 * default_height,
        four_text_w, default_height, "返回菜单", BROWN);
    Button over_button(getwidth() / 2 - four_text_w / 2, getheight() / 2 - default_height / 2 + 4 * default_height,
        four_text_w, default_height, "退出游戏", BROWN);
    BeginBatchDraw();
    loadimage(&img, "resources/PAUSE.png", window_width, window_height);
    while (flag == MY_PAUSE)
    {
        cleardevice();
        putimage(0, 0, &game_bk);
        loadimage(&game_bk, "resources/game_bk.jpg");
        /*game_score_view();
        game_death_view();
        game_wait_view();
        game_pass_view();
        .....
        */
        //for (auto it = cars_v.begin(); it != cars_v.end(); ++it) {
        //    if ((*it)->car_state == 1)
        //    {
        //        (*it)->car_view();
        //    }
        //}
        msg = GetMouseMsg();

        if (!continue_button.touch_button(YELLOW)) {
            continue_button.show_button(BROWN);
        }
        if (!setting_button.touch_button(YELLOW)) {
            setting_button.show_button(BROWN);
        }
        if (!help_button.touch_button(YELLOW)) {
            help_button.show_button(BROWN);
        }
       
        if (!menu_button.touch_button(YELLOW)) {
            menu_button.show_button(BROWN);
        }
        if (!over_button.touch_button(YELLOW)) {
            over_button.show_button(BROWN);
        }
        if (continue_button.click_button()) {
            flag = MY_GAME;
        }
        else if (setting_button.click_button()) {
            flag = MY_SETTING;
        }
        else if (help_button.click_button()) {
            flag = MY_HELP;
        }
        else if (menu_button.click_button()) {
            flag = MY_MENU;
        }
        else if (over_button.click_button()) {
            flag = MY_OVER;
        }
        FlushBatchDraw();
    }
}
