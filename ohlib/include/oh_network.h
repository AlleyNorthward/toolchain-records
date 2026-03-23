#ifndef OH_NETWORK_H
#define OH_NETWORK_H


extern "C"{
    #include "hi_types_base.h"
    #include "lwip/ip_addr.h"
    #include "lwip/netifapi.h"
    #include "lwip/inet.h"
}

namespace ohkit{

struct NetWorkAttr{
    const hi_char* ip;
    const hi_char* netmask;
    const hi_char* gateway;
};

enum class IpMode{
    OH_DHCP,
    OH_STATIC
};

class NetWork{
private:
    NetWorkAttr* config;

public:
    static netif *netif_ptr;
    static IpMode ip_mode;

public:
    NetWork(NetWorkAttr* config_ = nullptr);
    hi_void setStaticIp();
    static hi_void resetAddr();
    static hi_void startDhcp();
};

}

#endif