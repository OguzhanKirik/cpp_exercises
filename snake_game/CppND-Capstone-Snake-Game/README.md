########Loops, Functions, I/O - meet at least 2 criteria

1. The project accepts user input and processes the input.In addition to controlling the snake, the game can also receive new types of input from the player

--> gamesettings class enables to customize the snake game 

2.The project reads data from a file and process the data, or the program writes data to a file. The project reads data from an external file or writes data to a file as part of the necessary operation of the program.

--> in gamesettings class, readGameSettings reads the enter user inputs.

#########Object Oriented Programming - meet at least 3 criteria

1.One or more classes are added to the project with appropriate access specifiers for class members.Classes are organized with attributes to hold data and methods to perform tasks.All class data members are explicitly specified as public, protected, or private. Member data that is subject to an invariant is hidden from the user and accessed via member methods.

--> in the Game, rederer and Snake classes, there have been several changes,namely adding new class members, and methods accordingly.

2.Class constructors utilize member initialization lists.All class members that are set to argument values are initialized through member initialization lists.

--> Snake contructor is extended with a initial direction, and started with initilizer list.

3. Overloaded functions allow the same function to operate on different parameters.One function is overloaded with different signatures for the same function name.

-->  2 overloaded functions:
 void UpdateWindowTitle(int score,int scoreSecond, int fps, std::string userName, std::string userNameSecond);
  void UpdateWindowTitle(int score, int fps, std::string userName);

  void HandleInput(bool &running, Snake &snake) const;
  void HandleInput(bool &running, Snake &snake, std::shared_ptr<Snake>& snakePtr) const;


####Memory Management - meet at least 3 criteria

1.The project follows the Rule of 5.For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.

--> See snake classes

2.The project makes use of references in function declarations.At least two variables are defined as references, or two functions use pass-by-reference in the project code.
--> almost all funcitons 
example:  void HandleInput(bool &running, Snake &snake, std::shared_ptr<Snake>& snakePtr) const;

3.The project uses smart pointers instead of raw pointers.The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr.
used a shared_ptr object for second snake
  -->>> see game classes: std::shared_ptr<Snake> snakePtr = nullptr;


####Concurrency - meet at least 2 criteria

1.The project uses multithreading.The project uses multiple threads or async tasks in the execution.
--> using async
see game.cpp line 40 onwards

2.A promise and future is used in the project.A promise and future is used to pass data from a worker thread to a parent thread in the project cod

--> see line 48


🐍 Snake Game with Configurable Settings
This is an enhanced version of the classic Snake game, now featuring user customization and dynamic settings via a YAML configuration file. Players can tailor their experience by adjusting gameplay options before starting.

A GameSettings class reads values from config.yml at startup, allowing flexible control over various aspects of the game. Changes made in the config file are immediately reflected during gameplay.

🎮 Features & Customization Options
👤 Username Display
Players can enter their name in the config.yml file.

The username is displayed on the game window during play.

🧱 Optional Obstacles
Enable or disable dynamic obstacles via configuration.

Adds challenge and variety to the classic gameplay.

⚡ Adjustable Snake Speed
Customize snake speed based on your skill level.

Choose from slower, normal, or faster movement speeds.

🍎 Selectable Food Shape
Choose your food item shape:
Square, Circle, or Triangle.

Shapes are rendered using helper functions from helper.cpp.

🧑‍🤝‍🧑 Two-Player Mode
Enable a second player in the config file.

The second player can:

Enter a unique username.

Play using the W, A, S, D keys.




# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
