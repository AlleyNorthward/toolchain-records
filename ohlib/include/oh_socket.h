#ifndef OH_SOCKET_H
#define OH_SOCKET_H

extern "C"{
    #include "hi_types_base.h"
    #include "lwip/sockets.h"
    #include <netinet/in.h>
}

/*
@author 巷北
@time 2026/3/18 10:41
@describe
这里有了一个网络层的依赖项, 是必须的吗? 可是如果我想引用netif_ptr的话,
就不得不存在依赖啊.
*/

#define TCP_SERVER_PORT             8888
#define TCP_CLINET_PORT             8889
#define UDP_SERVER_PORT             8890
#define UDP_CLIENT_PORT             8891

namespace ohkit{

struct NetWorkAttr;

class IpEndpoint{
public:
    sockaddr_in addr;
public:
    IpEndpoint(){memset(&addr, 0, sizeof(addr));};
    IpEndpoint(const hi_char* ip, hi_u16 port);
    static IpEndpoint Any(hi_u16 port);
};


class Socket{
private:
    using oh_fd_t = int;
    oh_fd_t fd;

private:
    Socket(oh_fd_t fd_):fd(fd_){};
public:
    Socket();
    hi_void init(hi_s32 type, hi_s32 protocol);
    hi_void connect_oh(const IpEndpoint& server);
    hi_void bind_oh(const IpEndpoint& server);
    hi_void listen_oh(hi_s32 backlog = 5);
    Socket accept_oh(IpEndpoint& client, socklen_t& client_size);
    hi_s32 recv_oh(Socket s, hi_char* recv_buf);
    hi_s32 recv_oh(hi_char* recv_buf);
    hi_void send_oh(Socket s, const hi_char* send_data);
    hi_void send_oh(const hi_char* send_data);
    hi_void close_oh();
    oh_fd_t getFd() const {return fd;}

    static hi_void testPing(NetWorkAttr& config);
    static hi_void testTcp(NetWorkAttr& config, hi_u16 port = 80);
    static hi_void testUdp();

    static hi_void testTCPServerTask(const hi_char* send_data = "Hello Oh Server!");
    static hi_void testTCPClientTask(const hi_char* send_data = "Hello Oh Client!");
    static hi_void testUDPServerTask();
    static hi_void testUDPClientTask();
};

}

#endif