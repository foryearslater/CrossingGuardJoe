#include "car.h"
extern Player joe;

extern vector<Cars *> cars_v;

const int car_speed = 3;
const int car_width = WIDTH * 3;
const int car_height = 40;
const int car_timemin = 8000;
const int car_timemax = 12000;
const int car_y0 = 300;
const int car_x1 = (100 - WIDTH * 3) / 2 + 450;
const int car_x2 = (100 - WIDTH * 3) / 2 + 550;
const int car_x3 = (100 - WIDTH * 3) / 2 + 650;
const int car_y1 = 466;
const int car_r1 = 460;
const int car_r2 = 600;
const int car_r3 = 744;
const int car_end = 900;

Cars::Cars(int a)
{
    car_state = 1;
    if (a == -1)
    {
        car_x = car_x1;
        car_y = car_y0;
        car_lane = -1;
    }
    if (a == 0)
    {
        car_x = car_x2;
        car_y = car_y0;
        car_lane = 0;
    }
    if (a == 1)
    {
        car_x = car_x3;
        car_y = car_y0;
        car_lane = 1;
    }
}

Cars::~Cars() {};

void Cars::CarRoute()
{
    if (this->car_lane == -1)
    {
        while (this->car_y >= 300 && this->car_y <= 550)
        {
            this->car_x = car_x1 - (this->car_y - 200) / 5;
            return;
        }
    }
    else if (this->car_lane == 0)
    {
        return;
    }
    else if (this->car_lane == 1)
    {
        while (this->car_y >= 300 && this->car_y <= 550)
        {
            this->car_x = car_x3 + (this->car_y - 200) / 5;
            return;
        }
    }
}

bool Cars::IsArriving()
{
    if (this->car_y + car_height <= roadbot && this->car_y + car_height >= roadtop)
    {
        return true;
    }
    return false;
}
void Cars::IsCrashPlayer()
{
    if (0 < (this->car_x - joe.player_x) && (this->car_x - joe.player_x) < (this->car_width / 2 + joe.player_width / 2))
    {
        joe.player_flag = 5;
    }
    else if (0 < (joe.player_x - this->car_x) && (joe.player_x - this->car_x) < (this->car_width / 2 + joe.player_width / 2))
    {
        joe.player_flag = 6;
    }
}

void Cars::IsCrashingKid()
{

    for (auto &i : kid_v)
    {
        if (i.kid_state == 0 && this->car_x - car_width / 2 + 15 < i.kid_x && this->car_x + car_width / 2 + 20 > i.kid_x)
        {
            if (i.kid_flag != 4)
            {
                deadnum++;
                i.kid_flag = 4;
            }

            i.oldTime = clock();
        }
    }
}

IMAGE car_body[2];
void Cars::CarView()
{

    putimage(this->car_x, this->car_y, car_body, NOTSRCERASE);
    putimage(this->car_x, this->car_y, car_body + 1, SRCINVERT);

    return;
}

void Cars::CarMove()
{
    car_y += car_speed;
}

bool Timer1()
{
    static DWORD t11, t12, dt1 = rand() % (car_timemax - car_timemin + 1) + car_timemin;
    if (t12 - t11 > dt1)
    {
        t11 = t12;
        dt1 = rand() % (car_timemax - car_timemin + 1) + car_timemin;
        return true;
    }
    t12 = clock();
    return false;
}

bool Timer2()
{
    static DWORD t21, t22, dt2 = rand() % (car_timemax - car_timemin + 1) + car_timemin;
    if (t22 - t21 > dt2)
    {
        t21 = t22;
        dt2 = rand() % (car_timemax - car_timemin + 1) + car_timemin;
        return true;
    }
    t22 = clock();
    return false;
}
bool Timer3()
{
    static DWORD t31, t32, dt3 = rand() % (car_timemax - car_timemin + 1) + car_timemin;
    if (t32 - t31 > dt3)
    {
        t31 = t32;
        dt3 = rand() % (car_timemax - car_timemin + 1) + car_timemin;
        return true;
    }
    t32 = clock();
    return false;
}

void CarsView()
{

    if (Timer1())
    {
        cars_v.push_back(new Cars(-1));
    }
    if (Timer2())
    {
        cars_v.push_back(new Cars(0));
    }
    if (Timer3())
    {
        cars_v.push_back(new Cars(1));
    }
    for (auto it = cars_v.begin(); it != cars_v.end();)
    {
        if ((*it)->car_y > 900)
        {
            (*it)->car_state = 0;
        }
        if ((*it)->car_state == 1)
        {

            (*it)->CarView();
            (*it)->CarMove();
            (*it)->CarRoute();
            if ((*it)->IsArriving())
            {

                (*it)->IsCrashPlayer();

                (*it)->IsCrashingKid();
            }
            it++;
        }
        else
        {
            it = cars_v.erase(it);
        }
    }
}
