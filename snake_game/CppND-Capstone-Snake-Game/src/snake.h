#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"


class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  //Constructor
  Snake(int grid_width, int grid_height,Snake::Direction direction_)
      : grid_width(grid_width),
        grid_height(grid_height),
        direction(direction_),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  // Deconstroctor
  ~Snake(){}

  //Move assignemtn
  Snake& operator=(Snake&& other){
    if ( this != &other){
      this->direction = std::move(other.direction);
      this->speed = std::move(other.speed);
      this->size = std::move(other.size);
      this->alive = std::move(other.alive);
      this->head_x = std::move(other.head_x);
      this->head_y = std::move(other.head_y);
      this->body = std::move(other.body);
      this->growing = std::move(other.growing);
      this->grid_width = std::move(other.grid_width);
      this->grid_height = std::move(other.grid_height);
    }
    return *this;
  }

  // Move Constructor
  Snake(Snake&& other) noexcept
      : direction(std::move(other.direction)),
        speed(std::move(other.speed)),
        size(std::move(other.size)),
        alive(std::move(other.alive)),
        head_x(std::move(other.head_x)),
        head_y(std::move(other.head_y)),
        body(std::move(other.body)),
        growing(std::move(other.growing)),
        grid_width(std::move(other.grid_width)),
        grid_height(std::move(other.grid_height)) {}
  
  //Copy Assigment
  Snake& operator=(const Snake& other){
    if(this != &other){
      this->direction = other.direction;
     this->speed = other.speed;
      this->size = other.size;
      this->alive = other.alive;
      this->head_x = other.head_x;
      this->head_y = other.head_y;
      this->body = other.body;
      this->growing = other.growing;
      this->grid_width = other.grid_width;
      this->grid_height = other.grid_height;
    }
    return *this;

  }

  Snake(const Snake&& other)
         : direction(other.direction),
        speed(other.speed),
        size(other.size),
        alive(other.alive),
        head_x(other.head_x),
        head_y(other.head_y),
        body(other.body),
        growing(other.growing),
        grid_width(other.grid_width),
        grid_height(other.grid_height) {}

  void Update(const SDL_Rect& obstacle);

  void GrowBody();
  bool SnakeCell(int x, int y);
// Add different directions
  Direction direction;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell,const SDL_Rect& obstacle);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif