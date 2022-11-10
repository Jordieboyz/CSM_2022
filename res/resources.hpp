#ifndef _RESOURCES_HPP_
#define _RESOURCES_HPP_


enum buttons { UPBUTTONID = 0, DOWNBUTTONID, CHECKBUTTONID, CANCELBUTTONID };
enum modes { Manual = 0, Automatic};
enum settings { Brightness = 0, Color, ESM, OnOffTime , autoColor, LightThreshold, Mode};


struct selectableSettings {

    settings current;

    int min = 0;
    int max = 0;

    virtual void reset(){
        current = static_cast<settings>(int(min));
    }

    settings& operator--(int){
        int a = static_cast<int>(current);
        (a == min) ? a = max : a--;
        current = static_cast<settings>(a);
        return current;
    };

    settings& operator++(int){
        int a = static_cast<int>(current);
        (a == max) ? a = min : a++;
        current = static_cast<settings>(a);
        return current;
    };

    settings& operator!(){
        bool a = static_cast<bool>(current);
        a = !a;
        current = static_cast<settings>(a);
        return current;
    };

    template<typename T>
    bool operator==(const T rhs){
        return (this->current == rhs);
    }
    
    operator int(){
        return static_cast<int>(current);
    }

    selectableSettings(int min = 0, int max = 0) :
        min(min),
        max(max)
    {
        reset();
    }
};




struct modeSettings : public selectableSettings {
    modeSettings():
        selectableSettings(modes::Manual, modes::Automatic)
    { reset(); }
};

struct manualSettings : public selectableSettings {
    manualSettings(int min = settings::Brightness, int max = settings::ESM) :
        selectableSettings(min, max)
    { reset(); }
};

struct automaticSettings : public selectableSettings {
    automaticSettings(int min = settings::OnOffTime, int max = settings::LightThreshold) :
        selectableSettings(min, max)
    { reset(); }
};

struct pos{
    float x;
    float y;
};

#endif /* _RESOURCES_HPP_ */