//Author: xcw
//Email:  xcw_coder@qq.com
//2018年12月13日22:58:29
#pragma once
#include "Channel.h"
#include "HttpData.h"
#include "Timer.h"
#include <vector>
#include <unordered_map>
#include <sys/epoll.h>
#include <memory>

class Epoll 
{
public: 
    typedef std::shared_ptr<Channel> SP_Channel;
    Epoll();
    ~Epoll();
    void epoll_add(SP_Channel request, int timeout);
    void epoll_mod(SP_Channel request, int timeout);
    void epoll_del(SP_Channel request);
    std::vector<SP_Channel> poll();
    std::vector<SP_Channel> getEventRequest(int event_num);
    void add_timer(SP_Channel request_data, int timeout);
    int getEpollFd()
    {
        return epollFd_;
    }
    void handleExpired();

private: 
    static const int MAXFDS = 100000;
    int epollFd_;
    std::vector<epoll_event> events_;
    SP_Channel fd2chan_[MAXFDS];
    std::shared_ptr<HttpData> fd2http_[MAXFDS];
    TimerManager timerManager_;
};