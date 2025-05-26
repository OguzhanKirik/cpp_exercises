#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"



class Controller {
 public:


  //void HandleInputSecond(bool &running, std::shared_ptr<Snake> snakePtr) const ;
  void HandleInput(bool &running, Snake &snake) const;

  void HandleInput(bool &running, Snake &snake, std::shared_ptr<Snake>& snakePtr) const;
 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};


#endif