CXX = $(shell fltk-config --cxx)
CXXFLAGS = $(shell fltk-config --cxxflags)
FLTK_LIBS = $(shell fltk-config --libs)
FLTK_LDFLAGS = $(shell fltk-config --ldflags)

Simulator: main.cpp Menu.cpp Menu.h Slider.cpp Slider.h ProjectileBox.cpp ProjectileBox.h
	$(CXX) $(CXXFLAGS) -o Simulator main.cpp Menu.cpp Menu.h Slider.cpp Slider.h ProjectileBox.cpp ProjectileBox.h $(FLTK_LIBS) $(FLTK_LDFLAGS)
