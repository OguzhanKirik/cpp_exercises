#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : 
      snake(grid_width, grid_height,Snake::Direction::kUp),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)){
  

    gameSettings_.readGameSettings();  
    snake.speed = gameSettings_.gameSpeed;
    // one snake has already been started
    if (gameSettings_.addSecondPlayer == true){
      snakePtr = std::make_shared<Snake>(grid_width,grid_height,Snake::Direction::kLeft);
    }
    PlaceFood();

  }

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {

    
    frame_start = SDL_GetTicks();
    
    // Input, Update, Render - the main game loop.
    //controller.HandleInput(running, snake); // needs to be modified
    //controller.HandleInput(running, snake);
    if (snakePtr != nullptr) {
      controller.HandleInput(running, snake, snakePtr);
      auto future = std::async(std::launch::async, [&]() {
      UpdateSecond();  // Background-safe logic
      });

      Update();

      future.get();
    }else{
      controller.HandleInput(running,snake);
          Update();

    }
    //   auto future = std::async(std::launch::async, [&]() {
    //   controller.HandleInputSecond(running, snakePtr);});
    //   // Wait for async task to complete
    //   future.get();
    //   UpdateSecond();
    // }
    //  thread: Handle input
    //controller.HandleInputSecond(running, snakePtr);

    renderer.Render(snake, snakePtr,food, gameSettings_.foodType,gameSettings_.obstacle,obstacle);

    // Autonomous snake
    //calculate path
   //Controller.A
    //render the snake
    // move
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      if(snakePtr != nullptr){
        renderer.UpdateWindowTitle(score,scoreSecond ,frame_count, gameSettings_.user.username,gameSettings_.userSecond.username);
      }else{
        renderer.UpdateWindowTitle(score,frame_count, gameSettings_.user.username);
      }
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

// void Game::Run(Controller const &controller, Renderer &renderer,
//                std::size_t target_frame_duration) {
//   Uint32 title_timestamp = SDL_GetTicks();
//   Uint32 frame_start;
//   Uint32 frame_end;
//   Uint32 frame_duration;
//   int frame_count = 0;
//   bool running = true;

//   while (running) {
//     frame_start = SDL_GetTicks();

//     // Input, Update, Render - the main game loop.
//     //controller.HandleInput(running, snake); // needs to be modified
//     controller.HandleInput(running, snake);
    
//     Update();
//     renderer.Render(snake, food, gameSettings_.foodType,gameSettings_.obstacle,obstacle);

//     frame_end = SDL_GetTicks();

//     // Keep track of how long each loop through the input/update/render cycle
//     // takes.
//     frame_count++;
//     frame_duration = frame_end - frame_start;

//     // After every second, update the window title.
//     if (frame_end - title_timestamp >= 1000) {
//       renderer.UpdateWindowTitle(score, frame_count, gameSettings_.user.username);
//       frame_count = 0;
//       title_timestamp = frame_end;
//     }

//     // If the time for this frame is too small (i.e. frame_duration is
//     // smaller than the target ms_per_frame), delay the loop to
//     // achieve the correct frame rate.
//     if (frame_duration < target_frame_duration) {
//       SDL_Delay(target_frame_duration - frame_duration);
//     }
//   }
// }

// void Game::PlaceFood() {
//   int x, y;
//   while (true) {
//     x = random_w(engine);
//     y = random_h(engine);
//     // Check that the location is not occupied by a snake item before placing
//     // food.
//     if (!snake.SnakeCell(x, y)) {
//       food.x = x;
//       food.y = y;
//       return;
//     }
//   }
// }

void Game::Update() {
  if (!snake.alive) return;

  snake.Update(obstacle);

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}
void Game::UpdateSecond() {
  if(!snakePtr->alive) return;
  snakePtr->Update(obstacle);

  int new_x = static_cast<int>(snakePtr->head_x);
  int new_y = static_cast<int>(snakePtr->head_y);
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    scoreSecond++;
    PlaceFood();
    // Grow snake and increase speed.
    snakePtr->GrowBody();
    snakePtr->speed += 0.02;
  }
}


// void Game::Update() {
//   if (!snake.alive) return;

//   snake.Update(obstacle);

//   int new_x = static_cast<int>(snake.head_x);
//   int new_y = static_cast<int>(snake.head_y);
//   // Check if there's food over here
//   if (food.x == new_x && food.y == new_y) {
//     score++;
//     PlaceFood();
//     // Grow snake and increase speed.
//     snake.GrowBody();
//     snake.speed += 0.02;
//   }
// }

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

// MY Code
//My Code
