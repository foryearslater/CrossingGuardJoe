#include "application.h"

int main()
{
    mciSendString(_T("open resources/bgm1.mp3 alias bkmusic"), NULL, 0, NULL);
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
    initgraph(window_width, window_height, SHOWCONSOLE);
    setbkcolor(WHITE);

    Application app;
    app.controller();
    return 0;
}
