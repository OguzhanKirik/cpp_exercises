#include "renderer.h"
#include <iostream>
#include <string>

#include "helper.cpp"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(const Snake& snake,
  const std::shared_ptr<Snake>& snakePtr,
   SDL_Point const &food, 
   const FoodType& foodType,
   const bool& is_obstacleON,
  SDL_Rect& obstacle) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // // Render food
  // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  // block.x = food.x * block.w;
  // block.y = food.y * block.h;
  // SDL_RenderFillRect(sdl_renderer, &block);

  // Render differnt food types
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);

  switch(foodType){
    case(0):
      block.x = food.x * block.w;
      block.y = food.y * block.h;
      SDL_RenderFillRect(sdl_renderer, &block);
      break;
    case(1):
      SDL_Point p;
      p.x = food.x * block.w;
      p.y = food.y * block.h;
      drawTriangle(sdl_renderer, p, 20);
      //std::cout<< "Triangle" << food.x << "\n";
      break;
    case(2):
      p.x = food.x * block.w;
      p.y = food.y * block.h;
      drawCircle(sdl_renderer, p, 10);
     //std::cout<< "food" << food.x <<  "\n";
      break;
    default:
      throw std::invalid_argument("Wrong food type, try again!");

  }

 ///Obtacle
 if(is_obstacleON){
  obstacle.x = 10 * food.x;   
  obstacle.y = 5 * food.y;   
  obstacle.w = block.w * 5;  
  obstacle.h = block.h * 2;   
  SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);  // Red
  
  SDL_RenderFillRect(sdl_renderer, &obstacle);
 }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);


  if(snakePtr != nullptr){
    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snakePtr->body) {
      block.x = point.x * block.w;
      block.y = point.y * block.h;
      SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snakePtr->head_x) * block.w;
    block.y = static_cast<int>(snakePtr->head_y) * block.h;
    if (snakePtr->alive) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);
  
}



  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

// void Renderer::Render(Snake const snake,
//    SDL_Point const &food, 
//    const FoodType& foodType,
//    const bool& is_obstacleON,
//   SDL_Rect& obstacle) {
//   SDL_Rect block;
//   block.w = screen_width / grid_width;
//   block.h = screen_height / grid_height;

//   // Clear screen
//   SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
//   SDL_RenderClear(sdl_renderer);

//   // // Render food
//   // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
//   // block.x = food.x * block.w;
//   // block.y = food.y * block.h;
//   // SDL_RenderFillRect(sdl_renderer, &block);

//   // Render differnt food types
//   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);

//   switch(foodType){
//     case(0):
//       block.x = food.x * block.w;
//       block.y = food.y * block.h;
//       SDL_RenderFillRect(sdl_renderer, &block);
//       break;
//     case(1):
//       SDL_Point p;
//       p.x = food.x * block.w;
//       p.y = food.y * block.h;
//       drawTriangle(sdl_renderer, p, 20);
//       //std::cout<< "Triangle" << food.x << "\n";
//       break;
//     case(2):
//       p.x = food.x * block.w;
//       p.y = food.y * block.h;
//       drawCircle(sdl_renderer, p, 10);
//      //std::cout<< "food" << food.x <<  "\n";
//       break;
//     default:
//       throw std::invalid_argument("Wrong food type, try again!");

//   }

//  ///Obtacle
//  if(is_obstacleON){
//   obstacle.x = 10 * food.x;   
//   obstacle.y = 5 * food.y;   
//   obstacle.w = block.w * 5;  
//   obstacle.h = block.h * 2;   
//   SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);  // Red
  
//   SDL_RenderFillRect(sdl_renderer, &obstacle);
//  }

//   // Render snake's body
//   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//   for (SDL_Point const &point : snake.body) {
//     block.x = point.x * block.w;
//     block.y = point.y * block.h;
//     SDL_RenderFillRect(sdl_renderer, &block);
//   }

//   // Render snake's head
//   block.x = static_cast<int>(snake.head_x) * block.w;
//   block.y = static_cast<int>(snake.head_y) * block.h;
//   if (snake.alive) {
//     SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
//   } else {
//     SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
//   }
//   SDL_RenderFillRect(sdl_renderer, &block);

//   // Update Screen
//   SDL_RenderPresent(sdl_renderer);
// }

void Renderer::UpdateWindowTitle(int score,int scoreSecond, int fps, std::string userName, std::string userNameSecond) {
  std::string title{"Player1: "+ userName + " Snake Score: " + std::to_string(score) + "  ####  Player2: "+ userNameSecond + " Snake Score: " + std::to_string(scoreSecond) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}


void Renderer::UpdateWindowTitle(int score, int fps, std::string userName) {
  std::string title{"Player1: "+ userName + " Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

