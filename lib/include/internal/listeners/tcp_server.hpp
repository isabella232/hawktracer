#ifndef HAWKTRACER_INTERNAL_LISTENERS_TCP_SERVER_HPP
#define HAWKTRACER_INTERNAL_LISTENERS_TCP_SERVER_HPP

#include <mutex>
#include <thread>
#include <unordered_set>

namespace HawkTracer
{

class TCPServer
{
public:
    ~TCPServer();

    void write(char* buffer, size_t size);
    bool start(int port);
    void stop();

    bool is_running() const { return _sock_fd != -1; }
    size_t client_count() const { return _client_sock_fd.size(); }

private:
    bool _safe_write(int sock_fd, char* buffer, size_t size);
    void _run();

    std::thread _accept_client_thread;
    std::unordered_set<int> _client_sock_fd;
    std::mutex _client_mutex;
    int _sock_fd = -1;
};

}

#endif /* HAWKTRACER_INTERNAL_LISTENERS_TCP_SERVER_HPP */
