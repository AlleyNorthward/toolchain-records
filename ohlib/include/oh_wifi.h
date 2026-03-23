#ifndef OH_WIFI_H
#define OH_WIFI_H

extern "C"{
    #include "hi_types_base.h"
    #include "hi_wifi_api.h"
}

namespace ohkit{

class Wifi{
private:
    hi_char ifname[WIFI_IFNAME_MAX_SIZE + 1] = {0};
    hi_s32 len = sizeof(ifname);
    hi_u32 num = WIFI_SCAN_AP_LIMIT;

public:
    Wifi();
    hi_void start();
    hi_void scan();
    hi_void link(const hi_char* name = "iPhone", const hi_char* passward = "1234554321");

private:
    static hi_void wifi_wpa_event_cb(const hi_wifi_event* hisi_event);

public:
    const hi_char* get_ifname()const{return ifname;};
};

}


#endif