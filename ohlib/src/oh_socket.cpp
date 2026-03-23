#include "oh_socket.h"
#include "oh_network.h"
#include "oh_log_utils.h"
#include <unistd.h>

namespace ohkit{

IpEndpoint::IpEndpoint(const hi_char* ip, hi_u16 port){
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
}

IpEndpoint IpEndpoint::Any(hi_u16 port){
    IpEndpoint ep;
    ep.addr.sin_family = AF_INET;
    ep.addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ep.addr.sin_port = htons(port);
    return ep;
}

Socket::Socket():fd(-1){
    LOG_RET(OH_W, "Socket Constructor", OH_DEFAULT_ID);
}

hi_void Socket::init(hi_s32 type, hi_s32 protocol){
    fd = socket(AF_INET, type, protocol);
    if(fd < 0)
        Log::instance().error("Socket Create Failed. fd < 0.");
}

hi_void Socket::connect_oh(const IpEndpoint& server){
    hi_s32 ret = connect(fd, (sockaddr*)&server.addr, sizeof(server.addr));
    if(ret < 0)
        Log::instance().error("connect_oh Failed. errno: [%d]", errno);
}

hi_void Socket::bind_oh(const IpEndpoint& server){
    hi_s32 ret = bind(fd, (sockaddr*)&server.addr, sizeof(server.addr));
    if(ret < 0)
        Log::instance().error("bind_od Failed.");
}

hi_void Socket::listen_oh(hi_s32 backlog){
    hi_s32 ret = listen(fd, backlog);
    if(ret < 0)
        Log::instance().error("listen_oh Failed.");
}

Socket Socket::accept_oh(IpEndpoint& client, socklen_t& client_size){
    hi_s32 client_fd = accept(fd, (sockaddr*)&client.addr, &client_size);
    if(client_fd < 0){
        Log::instance().error("accept_oh Failed.");
        return Socket{};
    }
    return Socket{client_fd};
}

hi_s32 Socket::recv_oh(Socket s, hi_char* recv_buf){
    memset(recv_buf, 0, sizeof(recv_buf));
    return recv(s.getFd(), recv_buf, sizeof(recv_buf - 1), 0);
}

hi_s32 Socket::recv_oh(hi_char* recv_buf){
    memset(recv_buf, 0, sizeof(recv_buf));
    hi_s32 ret = recv(fd, recv_buf, sizeof(recv_buf - 1), 0);
    if (ret > 0) {
        recv_buf[ret] = '\0';
    }
    return ret;
}

hi_void Socket::send_oh(Socket s, const hi_char* send_data){
    send(s.getFd(), send_data, strlen(send_data), 0);
}

hi_void Socket::send_oh(const hi_char* send_data){
    send(fd, send_data, strlen(send_data), 0);
}

hi_void Socket::close_oh(){
    close(fd);
}


hi_void Socket::testPing(NetWorkAttr& config){
    if(NetWork::netif_ptr == nullptr){
        LOG_RET(OH_E, "Socket testPing func, nullptr", OH_DEFAULT_ID);
    }

    Log::instance().info("====== Testing Ping =====");
    hi_s32 sock = socket(AF_INET, SOCK_RAW, 1);

    if(sock >= 0){
        struct sockaddr_in destination;
        destination.sin_family = AF_INET;
        destination.sin_port = 0;
        destination.sin_addr.s_addr = inet_addr(config.gateway);

        hi_char packet[64] = "ping";
        hi_s32 ret = sendto(sock, packet, sizeof(packet), 0, (sockaddr *)& destination, sizeof(destination));

        if(ret > 0){
            Log::instance().info("Send test packet success.");
        } else{
            Log::instance().error("Send test packet failed, errno: [%d].", errno);
        }
    } else{
        Log::instance().error("Ping socket create failed, errno: [%d].", errno);
    }
}

hi_void Socket::testUdp(){
    Log::instance().info("====== Testing Udp =====");
    hi_s32 test_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(test_sock >= 0){
        struct sockaddr_in local;
        local.sin_family = AF_INET;
        local.sin_port = htons(UDP_SERVER_PORT);
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        hi_s32 ret = bind(test_sock, (sockaddr*)& local, sizeof(local));
        if(ret == 0){
            Log::instance().info("UDP port %d bind success.", UDP_SERVER_PORT);
        } else{
            Log::instance().error("UDP port %d bind failed.", UDP_SERVER_PORT);
        }
        close(test_sock);
    } else{
        Log::instance().error("Udp socket create failed, errno: [%d].", errno);
    }
}

hi_void Socket::testTcp(NetWorkAttr& config, hi_u16 port){
    Log::instance().info("====== Testing Tcp =====");
    hi_s32 tcp_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(tcp_sock >= 0){
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = inet_addr(config.gateway);

        hi_s32 ret = connect(tcp_sock, (sockaddr*)& server, sizeof(server));
        if(ret == 0){
            Log::instance().info("Tcp connect success.");
        } else {
            Log::instance().error("Tcp connect failed, errno: [%d].", errno);
        }
    } else{
        Log::instance().error("Tcp socket create failed, errno: [%d].", errno);
    }
}

hi_void Socket::testTCPServerTask(const hi_char* send_data){
    Socket listen, client;
    IpEndpoint s = IpEndpoint::Any(TCP_SERVER_PORT);
    IpEndpoint c;

    socklen_t client_len = sizeof(c.addr);
    hi_char recv_buf[512];
    Log::instance().info("========= TCP Server Mode ========");
    Log::instance().info("Server listening on port %d...", TCP_SERVER_PORT);

    listen.init(SOCK_STREAM, 0);
    if(listen.getFd() < 0){
        Log::instance().error("Socket creation failed! errnf = [%d].", errno);
        return;
    }

    listen.bind_oh(s);
    listen.listen_oh(5);

    while(1){
        client = listen.accept_oh(c, client_len);
        Log::instance().info("Client connected: %s:%d", inet_ntoa(c.addr.sin_addr), ntohs(c.addr.sin_port));

        while(1){
            memset(recv_buf, 0, sizeof(recv_buf));
            hi_s32 ret = client.recv_oh(recv_buf);

            if(ret <= 0){
                Log::instance().warn("Client disconnected.");
                break;
            }

            Log::instance().info("Received: %s", recv_buf);
            client.send_oh(send_data);
        }
        client.close_oh();
    }
    listen.close_oh();
}

hi_void Socket::testTCPClientTask(const hi_char* send_data){
    Socket client;
    char recv_buf[512];

    int count = 0;

    Log::instance().info("======== TCP Client Mode ============");
    while(1){
        client.init(SOCK_STREAM, 0);
        IpEndpoint server("172.20.10.7", TCP_SERVER_PORT);
        client.connect_oh(server);

        while(1){
            memset(recv_buf, 0, sizeof(recv_buf));
            client.send_oh(send_data);
            Log::instance().info("Sent [%d]: %s", ++count, send_data);

            hi_s32 ret = client.recv_oh(recv_buf);
            if(ret <= 0){
                Log::instance().info("Server Do not Send info");
                break;
            }
            Log::instance().info("Received[%d]: %s", count, recv_buf);
            sleep(3);
        }
        client.close_oh();
        sleep(3);
    }
}

}