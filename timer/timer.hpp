#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "boost/signals2.hpp"
#include <boost/enable_shared_from_this.hpp>


class Timer {
  public:
    Timer();
    Timer(const int interval_sec);
    ~Timer();
    void start();
    void start(const int interval_sec);
    void setInterval(const int interval_sec);
    void stop();
    boost::signals2::signal<void (void)> sigTick;
  private:
    void startTimer();
    void stopTimer();
    void reset();
    void tickTimer();
  private:
    boost::shared_ptr<boost::asio::io_service> io_service;
    boost::shared_ptr<boost::thread> io_thread;
    boost::scoped_ptr<boost::asio::deadline_timer> timer;
    int interval = 1;
};



#endif