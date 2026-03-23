#include "oh_wifi.h"
#include "oh_log_utils.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <unistd.h>
#include "oh_network.h"

namespace ohkit{

Wifi::Wifi(){
    LOG_RET(OH_W, "Wifi Constructor", OH_DEFAULT_ID);
}

hi_void Wifi::start(){
    hi_u32 ret = hi_wifi_sta_start(ifname, &len);
    LOG_RET(ret, "Wifi start func. hi_wifi_sta_start", OH_DEFAULT_ID);
    ret = hi_wifi_register_event_callback(Wifi::wifi_wpa_event_cb);
    LOG_RET(ret, "Wifi start func. hi_wifi_register_event_callback", OH_DEFAULT_ID);
}

hi_void Wifi::scan(){
    hi_u32 ret = hi_wifi_sta_scan();
    LOG_RET(ret, "Wifi scan func. hi_wifi_sta_scan", OH_DEFAULT_ID);
    hi_wifi_ap_info *pst_results = (hi_wifi_ap_info *)malloc(sizeof(hi_wifi_ap_info) * WIFI_SCAN_AP_LIMIT);
    if (pst_results == nullptr) {
        Log::instance().error("malloc failed.");
        return;
    }
    ret = hi_wifi_sta_scan_results(pst_results, &num);

    if(ret == HI_ERR_SUCCESS){
        Log::instance().info("Found %d Aps:", num);

        for(hi_u32 i = 0; i < num && i < WIFI_SCAN_AP_LIMIT; ++i){
            if(strlen(pst_results[i].ssid) > 0){
                Log::instance().info("  %d: %s\n", i + 1, pst_results[i].ssid);
            }
        }
    }

    free(pst_results);
}

hi_void Wifi::link(const hi_char* name, const hi_char* passward){
    Log::instance().info("Connecting to WiFi ...");
    hi_u32 ret ;
    hi_wifi_assoc_request assoc_req = {0};
    memcpy_s(assoc_req.ssid, HI_WIFI_MAX_SSID_LEN + 1, name, strlen(name));
    assoc_req.auth = HI_WIFI_SECURITY_WPA2PSK;
    memcpy(assoc_req.key, passward, strlen(passward));

    ret = hi_wifi_sta_connect(&assoc_req);
    LOG_RET(ret, "Wifi connect func. hi_wifi_sta_connect", OH_DEFAULT_ID);
    Log::instance().info("Waiting for WiFi connection...");
    sleep(8);
}

hi_void Wifi::wifi_wpa_event_cb(const hi_wifi_event* hisi_event){
    if (hisi_event == nullptr)
        return;

    switch (hisi_event->event) {
        case HI_WIFI_EVT_SCAN_DONE:
            Log::instance().warn("WiFi: Scan results available");
            break;
        case HI_WIFI_EVT_CONNECTED:
            Log::instance().info("WiFi: Connected");
            if(NetWork::ip_mode == IpMode::OH_DHCP)
                NetWork::startDhcp();
            break;
        case HI_WIFI_EVT_DISCONNECTED:
            Log::instance().warn("WiFi: Disconnected");
            if(NetWork::ip_mode == IpMode::OH_DHCP){
                netifapi_dhcp_stop(NetWork::netif_ptr);
                NetWork::resetAddr();
            }
            break;
        case HI_WIFI_EVT_WPS_TIMEOUT:
        Log::instance().error("WiFi: Timeout.");
            break;
        default:
            break;
    }
}

}