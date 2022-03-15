#include <iostream>
#include "./timer/timer.hpp"

Timer timer;
int i = 0;

void timerTick() {
  i += 1;
  std::cout << "Timer TICK" << std::endl;
  if (i >= 5)  {
    timer.stop();
  }
}

int main() {
  std::cout << "DEMO Timer" << std::endl;
  boost::signals2::connection conn_tick_timer = timer.sigTick.connect(boost::bind(timerTick));
  timer.start(2);
  while(1) {

  }
  return 0;
}