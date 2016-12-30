#ifndef MENU_H
#define MENU_H

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

// Class for creating Menu-bar

class Menu {

private:

    Fl_Menu_Bar* menubar;
    Fl_Double_Window* main_window;

public:

    Menu(Fl_Double_Window*);

    // Static menu callback
    static void Menu_Cb(Fl_Widget*, void*);
    // Callback method with class access
    void Menu_Cb2();

};

#endif
