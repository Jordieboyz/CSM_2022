#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

// Defines
#define N_rooms 8


class Light {
public: 
    void On(){ }; 
    void Off(){ };

    void setBrightness( int brightness ){ };
    void setColor( int color ){ };
};


class LightControl { 
public:
    void setBrightness( int brightness ){ };
    void setColor( int Color ) { };

private:
    int brightness = 0;
    int color = 0;

    Light* rooms[N_rooms] = {};
};

#endif /* _LIGHT_HPP_ */