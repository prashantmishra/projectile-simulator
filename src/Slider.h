#ifndef SLIDER_H
#define SLIDER_H

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

#define ANGLE_MAX 85
#define ANGLE_MIN 5
#define RANGE_MAX 1500
#define RANGE_MIN 0
#define SPEED_MAX 120
#define SPEED_MIN 10

// Class for passing parameter through slider

class Slider : public Fl_Group {

private:

    Fl_Int_Input *input;
    Fl_Slider *slider;

public:

    Slider(int x, int y, int w, int h, const char *l=0);

    // For passing input value to slider
    static void Input1_CB(Fl_Widget *w, void *data);
    void Input1_CB2();

    // For passing slider value to input
    static void Slider1_CB(Fl_Widget *w, void *data);
    void Slider1_CB2();

    int value();
    void value(int val);
    void bounds(int low, int high);

};

#endif
