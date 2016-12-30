#include "ProjectileBox.h"

#define BG_COLOR 239
#define TICK_COLOR 0
#define CIRC_COLOR 0
#define UPDATE_RATE 0.015
#define SPEED_FACTOR 3
#define GRAVITY 9.81

ProjectileBox::ProjectileBox(int X,int Y,int W,int H, Slider*_sl_speed, Slider* _sl_angle,Slider* _sl_range,Fl_Double_Window* window, const char*L) : Fl_Box(X, Y, W, H, L) {
    main_window = window;
    sl_speed = _sl_speed;
    sl_angle = _sl_angle;
    sl_range = _sl_range;
    box(FL_FLAT_BOX);
    color(BG_COLOR);
    Fl::add_timeout(UPDATE_RATE, refresh, (void*)this);

    gettimeofday(&time_cb, NULL);
    sec_cb = time_cb.tv_sec;
    usec_cb = time_cb.tv_usec;
}


void ProjectileBox::draw() {

    struct timeval currTime;
    gettimeofday(&currTime, NULL);
    long elapsed_useconds = (currTime.tv_sec - sec_cb)*1000000L + currTime.tv_usec - usec_cb;
    elapsed_useconds *= SPEED_FACTOR;

    // Calculate values which will be of interest to us
    float x_curr = speed_cb*cos(angle_cb)*elapsed_useconds/1000000;
    float range = speed_cb*speed_cb*sin(2*angle_cb)/GRAVITY;
    float time_flight = 2*speed_cb*sin(angle_cb)/GRAVITY;
    long max_range = SPEED_MAX*SPEED_MAX/GRAVITY;
    float max_height = SPEED_MAX*SPEED_MAX*sin(ANGLE_MAX)*sin(ANGLE_MAX)/(2*GRAVITY);

    long range_centi_m = (x_curr > range ? range*100 : x_curr*100);
    long elapsed_centiseconds = (x_curr > range ? time_flight*100 : elapsed_useconds/10000);

    // Make sure ball never goes off-screen for these set of values
    float tr_ratio = 2/(sin(ANGLE_MAX*3.141592/180)*sin(ANGLE_MAX*3.141592/180));
    float sc_ratio = this->w()/this->h();

    float factor;
    if (sc_ratio > tr_ratio) {
        factor = 0.9*this->h()/max_height;
    } else {
        factor = 0.9*this->w()/max_range;
    }

    int x_off = x() + 0.05*this->w();
    int y_off = y() + 0.95*this->h();

    char secs[80]; sprintf(secs, "Time of Flight  -  %02ld:%02ld secs", elapsed_centiseconds/100, elapsed_centiseconds%100);
    char dist[80]; sprintf(dist, "Horizontal distance  -  %02ld.%02ld metres", range_centi_m/100, range_centi_m%100);
    char badguess[80]; sprintf(badguess, "You are terrible at this!");
    char okayguess[80]; sprintf(okayguess, "Decent. But there is room for improvement.");
    char goodguess[80]; sprintf(goodguess, "Amazing! You are great at guessing game.");

    Fl_Box::draw();

    //when the ball is still in flight, subtracting 4 in fl_pie() to account for radius of ball
    if (x_curr < range) {

        for (int _x=0; _x < x_curr; _x += 8) {
            fl_color(TICK_COLOR);
            fl_line(x_off + factor*_x, y_off - factor*calculateY(_x), x_off + factor*(_x+1), y_off - factor*calculateY(_x+1));
            fl_line_style(FL_CAP_SQUARE,1,0);
            fl_color(CIRC_COLOR);
            fl_draw(secs, x() + 0.1*this->w(), y() + 0.05*this->h());
            fl_draw(dist, x() + 0.6*this->w(), y() + 0.05*this->h());
        }

        fl_pie(x_off + factor*x_curr - 4, y_off - factor*calculateY(x_curr) - 4, 8, 8, 0.0, 360.0);

    //when the flight is over
    } else {

        for (int _x=0; _x < range; _x += 8) {
            fl_color(TICK_COLOR);
            fl_line(x_off + factor*_x, y_off - factor*calculateY(_x), x_off + factor*(_x+1), y_off - factor*calculateY(_x+1));
            fl_line_style(FL_CAP_SQUARE,1,0);
            fl_color(CIRC_COLOR);
            fl_draw(secs, x() + 0.1*this->w(), y() + 0.05*this->h());
            fl_draw(dist, x() + 0.6*this->w(), y() + 0.05*this->h());
        }

        fl_pie(x_off + factor*range - 4, y_off - factor*calculateY(range) - 4, 8, 8, 0.0, 360.0);

        if (range_cb > 2*range || range_cb < 0.5*range) {
            fl_draw(badguess, x() + 0.35*this->w(), y() + 0.15*this->h());
        } else if (range_cb > 1.3*range || range_cb < 0.75*range) {
            fl_draw(okayguess, x() + 0.35*this->w(), y() + 0.15*this->h());
        } else {
            fl_draw(goodguess, x() + 0.35*this->w(), y() + 0.15*this->h());
        }

        return;
    }

    fl_color(TICK_COLOR);

}

void ProjectileBox::refresh(void *userdata) {
    ProjectileBox *o = (ProjectileBox*)userdata;
    o->redraw();
    Fl::repeat_timeout(UPDATE_RATE, refresh, userdata);
}

// Get Y given X on a parabolic projectile trajectory
int ProjectileBox::calculateY(int X) {
    return X*tan(this->angle_cb) - (GRAVITY*X*X)/(2*speed_cb*speed_cb*cos(this->angle_cb)*cos(this->angle_cb));
}
