#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

// Local Include Files
#include "resources.hpp"

// Defines
#define str(s) (const char *)#s


struct Setting {

    const char * name;
    int value;

    Setting(){};

    Setting(const char * name) : 
        name( name ), value( 0 ) {}

    Setting(const char * name, int value) : 
        name( name ), value( value ) {}

    bool operator==(const char * rhs){
        return (this->name == rhs);
    }
};

class smartLightSettings { 
public:
    int getSetting(const char * name){ 
        for(auto item : settings){
            if(item->name == name){
                return item->value;
            }
        }
        return -1;
    };

    void setSetting(const char * name, int value){
        for(auto item : settings){
            if(item->name == name){
                item->value = value;
            }
        }
    };

    Setting* addSetting( const char * name, int value = 0){
        for(auto item : settings){
            if(item->name == name){
                return nullptr;
            }
        }

        // have to do it like this because can't use "opeartor new", no heap on arduino...
        Setting* set;
        set->name = name;
        set->value = value;

        settings[curr_arr_size] = set;
        curr_arr_size++;
        return set;
    };

    Setting* at(int idx){
        return settings[idx];
    };

    // define the "standard settings"
    smartLightSettings(){
        addSetting(str(Brightness));
        addSetting(str(Color));
        addSetting(str(ESM));
        addSetting(str(doneButton), -1);
        addSetting(str(OnOffTime));
        addSetting(str(autoColor));
        addSetting(str(LightThreshold));
        addSetting(str(Mode));
    }
private:
    Setting* settings[8] = {};

    size_t curr_arr_size = 0;
};

#endif /* _SETTINGS_HPP_ */