#ifndef PROJECTILE_BOX_H
#define PROJECTILE_BOX_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Slider.H>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sys/time.h>
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Menu_Bar.H>
#include "Slider.h"

// Class for plotting trajectory

class ProjectileBox : public Fl_Box {

public:

    ProjectileBox(int X,int Y,int W,int H, Slider*_sl_speed, Slider* _sl_angle, Slider* _sl_range, Fl_Double_Window* window, const char*L=0);
    void draw();
    static void refresh(void *userdata);
    int calculateY(int X);

    Fl_Double_Window* main_window;
    Slider* sl_speed;
    Slider* sl_angle;
    Slider* sl_range;

    float speed_cb;
    float angle_cb;
    int range_cb;
    struct timeval time_cb;
    long sec_cb;
    long usec_cb;
};

#endif
