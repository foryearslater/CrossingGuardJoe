#include "application.h"

MOUSEMSG msg;
int flag = MY_MENU;

void Application::controller()
{
    while (1)
    {

        switch (flag)
        {
        case MY_MENU:
            pre_flag = MY_MENU;
            menu_view();
            break;
        case MY_SETTING:
            setting_view();
            break;
        case MY_GAME:

            cout << "加载游戏界面" << endl;

            GameView();
            break;
        case MY_LOSE:
            LoseView();
            break;
        case MY_WIN:
            WinView();
            break;
        case MY_HELP:
            help_view();
            break;
        case MY_PAUSE:
            pre_flag = MY_PAUSE;
            PauseView();
            break;
        case MY_OVER:
            exit(0);
        }
    }
}

void Application::menu_view()
{

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

        if (!game_button.TouchButton(YELLOW))
        {
            game_button.ShowButton(BROWN);
        }
        if (!setting_button.TouchButton(YELLOW))
        {
            setting_button.ShowButton(BROWN);
        }
        if (!help_button.TouchButton(YELLOW))
        {
            help_button.ShowButton(BROWN);
        }
        if (!over_button.TouchButton(YELLOW))
        {
            over_button.ShowButton(BROWN);
        }
        if (game_button.ClickButton())
        {
            flag = MY_GAME;
            GameInit();
            cout << "跳转到游戏界面" << endl;
        }
        else if (setting_button.ClickButton())
        {
            flag = MY_SETTING;
        }
        else if (help_button.ClickButton())
        {
            flag = MY_HELP;
        }
        else if (over_button.ClickButton())
        {
            flag = MY_OVER;
        }
        FlushBatchDraw();
    }
}

void Application::setting_view()
{
    Button return_button(1000, 650, 100, 50, "返回", BROWN);
    Button muson_button(500, 450, 150, 50, "音乐开", BROWN);
    Button musoff_button(500, 450, 150, 50, "音乐关", YELLOW);
    setbkcolor(RGB(191, 187, 177));
    BeginBatchDraw();
    while (flag == MY_SETTING)
    {
        cleardevice();
        msg = GetMouseMsg();
        if (!return_button.TouchButton(YELLOW))
        {
            return_button.ShowButton(BROWN);
        }
        if (MUS == 1)
        {
            muson_button.ShowButton(BROWN);
            if (muson_button.ClickButton())
            {
                mciSendString(_T("close bkmusic"), NULL, 0, NULL);
                MUS = 0;
            }
        }
        else if (MUS == 0)
        {
            musoff_button.ShowButton(YELLOW);
            if (musoff_button.ClickButton())
            {
                mciSendString(_T("open resources/bgm1.mp3 alias bkmusic"), NULL, 0, NULL); // 播放音乐
                mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
                MUS = 1;
            }
        }
        settextcolor(WHITE);
        settextstyle(50, 0, _T("Consolas"));
        outtextxy(500, 500, _T("敬请期待"));
        if (return_button.ClickButton())
        {
            flag = pre_flag;
        }
        FlushBatchDraw();
    }
}
void Application::help_view()
{
    Button return_button(1000, 650, 100, 50, "返回", BROWN);
    setbkcolor(RGB(191, 187, 177));
    BeginBatchDraw();
    loadimage(&img, "resources/游戏帮助.png", window_width, window_height);
    while (flag == MY_HELP)
    {

        cleardevice();
        msg = GetMouseMsg();
        putimage(0, 0, &img);

        if (!return_button.TouchButton(YELLOW))
        {
            return_button.ShowButton(BROWN);
        }

        if (return_button.ClickButton())
        {
            flag = pre_flag;
        }
        FlushBatchDraw();
    }
}
void Application::PauseView()
{
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
        /*GameScoreView();
        GameDeathView();
        game_wait_view();
        GamePassView();
        .....
        */
        // for (auto it = cars_v.begin(); it != cars_v.end(); ++it) {
        //     if ((*it)->car_state == 1)
        //     {
        //         (*it)->CarView();
        //     }
        // }
        msg = GetMouseMsg();

        if (!continue_button.TouchButton(YELLOW))
        {
            continue_button.ShowButton(BROWN);
        }
        if (!setting_button.TouchButton(YELLOW))
        {
            setting_button.ShowButton(BROWN);
        }
        if (!help_button.TouchButton(YELLOW))
        {
            help_button.ShowButton(BROWN);
        }

        if (!menu_button.TouchButton(YELLOW))
        {
            menu_button.ShowButton(BROWN);
        }
        if (!over_button.TouchButton(YELLOW))
        {
            over_button.ShowButton(BROWN);
        }
        if (continue_button.ClickButton())
        {
            flag = MY_GAME;
        }
        else if (setting_button.ClickButton())
        {
            flag = MY_SETTING;
        }
        else if (help_button.ClickButton())
        {
            flag = MY_HELP;
        }
        else if (menu_button.ClickButton())
        {
            flag = MY_MENU;
        }
        else if (over_button.ClickButton())
        {
            flag = MY_OVER;
        }
        FlushBatchDraw();
    }
}