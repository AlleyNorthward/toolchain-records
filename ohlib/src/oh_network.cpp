#include "oh_network.h"
#include "oh_log_utils.h"
#include <unistd.h>


namespace ohkit{

netif* NetWork::netif_ptr = nullptr;
IpMode NetWork::ip_mode = IpMode::OH_STATIC;

NetWork::NetWork(NetWorkAttr* config_):config(config_){
    LOG_RET(OH_W, "NetWork Constructor", OH_DEFAULT_ID);
}

hi_void NetWork::setStaticIp(){
    if(NetWork::netif_ptr == nullptr){
        LOG_RET(OH_E, "NetWork setStaticIp Fun, nullptr", OH_DEFAULT_ID);
        return ;
    }

    netifapi_dhcp_stop(NetWork::netif_ptr);
    sleep(1);

    ip4_addr_t ip_addr, netmask, gw;
    ip4addr_aton(config->ip, &ip_addr);
    ip4addr_aton(config->netmask, &netmask);
    ip4addr_aton(config->gateway, &gw);

    netifapi_netif_set_addr(NetWork::netif_ptr, &ip_addr, &netmask, &gw);
    netif_set_up(NetWork::netif_ptr);

    Log::instance().info("Static Ip Configured:");
    Log::instance().info("  IP: %s", config->ip);
    Log::instance().info("  Netmask: %s", config->netmask);
    Log::instance().info("  Gateway: %s", config->gateway);

    Log::instance().info("Verification:");
    Log::instance().info("  IP: %s", ip4addr_ntoa(netif_ip4_addr(NetWork::netif_ptr)));
    Log::instance().info("  Netmask: %s", ip4addr_ntoa(netif_ip4_netmask(NetWork::netif_ptr)));
    Log::instance().info("  Gateway: %s", ip4addr_ntoa(netif_ip4_gw(NetWork::netif_ptr)));
    Log::instance().info("====================================");
}

hi_void NetWork::resetAddr(){
    ip4_addr_t ipaddr, netmask, gw;
    printf("%s %d \r\n", __FILE__, __LINE__);
    if (netif_ptr == nullptr) {
        printf("hisi_reset_addr::Null param of netdev\r\n");
        return;
    }

    IP4_ADDR(&ipaddr, 0, 0, 0, 0);
    IP4_ADDR(&netmask, 0, 0, 0, 0);
    IP4_ADDR(&gw, 0, 0, 0, 0);

    netifapi_netif_set_addr(netif_ptr, &ipaddr, &netmask, &gw);
}

hi_void NetWork::startDhcp(){
    netifapi_dhcp_start(netif_ptr);
}

}