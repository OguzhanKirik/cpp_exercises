#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"

#include "snake.h"
#include "settings.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(const Snake& snake, const std::shared_ptr<Snake>& snakePtr,
 SDL_Point const &food, const FoodType& foodType,const bool& is_obstacleON,SDL_Rect& obstacle );

  void UpdateWindowTitle(int score,int scoreSecond, int fps, std::string userName, std::string userNameSecond);

  void UpdateWindowTitle(int score, int fps, std::string userName);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif