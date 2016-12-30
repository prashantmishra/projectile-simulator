#include "Menu.h"
#include <FL/forms.H>
#define MENU_COLOR 238
#define TEXT_COLOR 239

// TODO: Change font and font-size

Menu::Menu(Fl_Double_Window* window) {

    main_window = window;
    menubar = new Fl_Menu_Bar(0, 0, main_window->w(), 0.04*main_window->h());
    menubar->color(TEXT_COLOR);
    menubar->add("File/Quit", 0, Menu_Cb, (void*)this);
    menubar->add("Options/Help", 0, Menu_Cb, (void*)this);
    menubar->add("Options/About", 0, Menu_Cb, (void*)this);

    menubar->labelsize(48);

    main_window->redraw();
    main_window->end();
    main_window->show();

}

void Menu::Menu_Cb(Fl_Widget*w, void*data) {
    Menu *o = (Menu*)data;
    o->Menu_Cb2();
}

void Menu::Menu_Cb2() {
    char picked[80];
    menubar->item_pathname(picked, sizeof(picked)-1);
    printf("CALLBACK: You picked '%s'\n", picked);

    if (strcmp(picked, "File/Quit") == 0) {

        exit(0);

    } else if (strcmp(picked, "Options/Help") == 0){

        Fl_Window *M = new Fl_Window(0.3*main_window->w(), 0.4*main_window->h());
        M->color(MENU_COLOR);
        Fl_Text_Display *disp = new Fl_Text_Display(0.05*M->w(), 0.05*M->h(), 0.9*M->w(), 0.9*M->h(), "HELP");
        disp->color(TEXT_COLOR);
        Fl_Text_Buffer *tbuff = new Fl_Text_Buffer();
        disp->wrap_mode(3, 40);
        disp->buffer(tbuff);
        tbuff->text("This is Projectile-Motion Simulator plus a guessing game. "
                    "You have to input the velocity and the angle of projection "
                    "through sliders. The program will show you :- \n \n"
                    "i) The trajectory of particle. \n"
                    "ii)  Its time of flight. \n"
                    "iii) Its horizontal range. \n"
                    "iv)  Comment based on your guess. \n \n"
                    "Happy Guessing!");
        M->show();
        Fl::run();

    } else if (strcmp(picked, "Options/About") == 0){

        Fl_Window *M = new Fl_Window(0.3*main_window->w(), 0.4*main_window->h());
        M->color(MENU_COLOR);
        Fl_Text_Display *disp = new Fl_Text_Display(0.05*M->w(), 0.05*M->h(), 0.9*M->w(), 0.9*M->h(), "ABOUT");
        disp->color(TEXT_COLOR);
        Fl_Text_Buffer *tbuff = new Fl_Text_Buffer();
        disp->wrap_mode(3, 40);
        disp->buffer(tbuff);
        tbuff->text("Projectile-Simulator is free software: you can redistribute it "
                    "and/or modify it under the terms of the GNU General Public License "
                    "as published by the Free Software Foundation, either version 3 of "
                    "the License, or (at your option) any later version. \n \n"
                    "Projectile-Simulator is distributed in the hope that it will be useful, "
                    "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                    "GNU General Public License for more details.) \n \n"
                    "Author - Prashant Mishra");
        M->show();
        Fl::run();

    }

}
