#include "ProjectileBox.h"
#include "Menu.h"
#include <X11/Xlib.h>

using namespace std;

#define PI 3.141592
#define MAIN_WINDOW_COLOR 238
#define SLIDER_COLOR 47

//Callback Functions

void start_cb(Fl_Widget*, void* v) {

    ProjectileBox* p = (ProjectileBox*) v;
    p->range_cb = p->sl_range->value();
    p->speed_cb = p->sl_speed->value();
    p->angle_cb = (p->sl_angle->value())*PI/180;

    struct timeval time_cb;
    gettimeofday(&time_cb, NULL);
    p->sec_cb = time_cb.tv_sec;
    p->usec_cb = time_cb.tv_usec;

    p->main_window->redraw();

}


void close_cb(Fl_Widget*, void* v) {
    exit(0);
}

// TODO: Choose a good color scheme

int main() {

    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);

    int width = s->width*0.6;
    int height = s->height*0.6;

    Fl_Double_Window* window = new Fl_Double_Window(width, height, "Projectile Motion Simulator");
    window->color(MAIN_WINDOW_COLOR);

    Slider *sl_speed = new Slider(0.85*window->w(), 0.15*window->h(), 0.13*window->w(), 0.05*window->h(), "Velocity (m/s)");
    sl_speed->color(SLIDER_COLOR);
    sl_speed->box(FL_DOWN_BOX);
    sl_speed->bounds(SPEED_MIN, SPEED_MAX);
    sl_speed->value((SPEED_MIN+SPEED_MAX)/2);

    Slider *sl_angle = new Slider(0.85*window->w(), 0.35*window->h(), 0.13*window->w(), 0.05*window->h(), "Angle (deg)");
    sl_angle->color(SLIDER_COLOR);
    sl_angle->box(FL_DOWN_BOX);
    sl_angle->bounds(ANGLE_MIN, ANGLE_MAX);
    sl_angle->value((ANGLE_MIN+ANGLE_MAX)/2);

    Slider *sl_range = new Slider(0.85*window->w(), 0.55*window->h(), 0.13*window->w(), 0.05*window->h(), "Predict Range (m)");
    sl_range->color(SLIDER_COLOR);
    sl_range->box(FL_DOWN_BOX);
    sl_range->bounds(RANGE_MIN, RANGE_MAX);
    sl_range->value((RANGE_MIN+RANGE_MAX)/2);

    Fl_Button* start = new Fl_Button(0.85*window->w(), 0.75*window->h(), 0.05*window->w(), 0.04*window->h(), "Start");
    Fl_Button* close = new Fl_Button(0.92*window->w(), 0.75*window->h(), 0.05*window->w(), 0.04*window->h(), "Quit");

    ProjectileBox *projectile_box = new ProjectileBox(0.01*width, 0.06*height, 0.83*window->w(), 0.92*window->h(), sl_speed, sl_angle, sl_range, window);
    close->callback(close_cb, projectile_box);
    start->callback(start_cb, projectile_box);

    Menu* menu = new Menu(window);

    window->show();
    return(Fl::run());

}
