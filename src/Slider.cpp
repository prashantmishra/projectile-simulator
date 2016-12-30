#include "Slider.h"

#define SLIDER_COLOR 247

Slider::Slider(int x, int y, int w, int h, const char *l) : Fl_Group(x, y, w, h, l) {
    int _w = w*0.3;
    int _h = h*0.9;

    // Tweaked the constant values, these work well
    input  = new Fl_Int_Input(x + 0.05*_w, y + 0.05*_h, _w, _h);
    input->callback(Input1_CB, (void*)this);
    input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED|FL_WHEN_CHANGED);
    input->color(SLIDER_COLOR);

    slider = new Fl_Slider(x + 1.1*_w, y + 0.05*_h, w - 1.15*_w, _h);
    slider->type(1);
    slider->callback(Slider1_CB, (void*)this);
    slider->color(SLIDER_COLOR);

    // Defaults
    bounds(20, 80);
    value(50);
    end();
}

void Slider::Input1_CB(Fl_Widget *w, void *data) {
    ((Slider*)data)->Input1_CB2();
}

void Slider::Input1_CB2() {
    int val = 0;
    if (sscanf(input->value(), "%d", &val) != 1) {
        std::cout << "Could not set value from slider..";
        val = slider->value();
    }
    slider->value((int)(val + 0.5));
}

void Slider::Slider1_CB(Fl_Widget *w, void *data) {
    ((Slider*)data) -> Slider1_CB2();
}

void Slider::Slider1_CB2() {
    char s[10];
    sprintf(s, "%d", (int)(slider->value() + 0.5));
    slider->value((int)(slider->value() + 0.5));
    input->value(s);
}

int Slider::value() {
    return (int) slider->value() + 0.5;
}

void Slider::value(int val) {
    slider->value(val);
    Slider1_CB2();
}

void Slider::bounds(int low, int high) {
    slider->bounds(low, high);
}
