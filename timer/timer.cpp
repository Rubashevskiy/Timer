#include "timer.hpp"

Timer::Timer() {}

Timer::Timer(const int interval_sec) : interval(interval_sec) {}

Timer::~Timer() {
  stopTimer();
}

void Timer::start() {
  startTimer();
}

void Timer::start(const int interval_sec) {
  interval = interval_sec;
  startTimer();
}

void Timer::stop() {
  reset();
}

void Timer::setInterval(const int interval_sec) {
  interval = interval_sec;
}

void Timer::startTimer() {
  io_service.reset(new boost::asio::io_service());
  timer.reset(new boost::asio::deadline_timer(*io_service));
  timer->expires_from_now(boost::posix_time::seconds(interval));
  timer->async_wait(boost::bind(&Timer::tickTimer, this));
  io_thread.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, io_service)));
  io_service->run();
}

void Timer::stopTimer() {
  reset();
}

void Timer::tickTimer() {
  if (nullptr == timer) {
    return;
  }
  timer->expires_from_now(boost::posix_time::seconds(interval));
  timer->async_wait(boost::bind(&Timer::tickTimer, this));
  sigTick();
}

void Timer::reset() {
  if (nullptr != io_service) {
    io_service.reset();
  }
  if (nullptr != timer) {
    timer.reset();
  }
  if (nullptr != io_thread) {
    io_thread.reset();
  }
}