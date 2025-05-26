#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Allow players to enter their names and save their high scores to a text file.
// Add fixed and moving obstacles to the game.
// Add different types of food to the game.
// Allow players to select the initial speed of the game.
// Add another snake to the game that is controlled by the computer using the A* search algorithm.
struct User{
    std::string username;
    int highestScore; 
};

enum FoodType{
    Square = 0, 
    Triangle = 1,
    Circle = 2
};

class GameSettings{
    
    public:
        bool verify = false;
        float gameSpeed;
        bool obstacle = false;
        int numSnakes = 0;
        bool movingObstacle = false;
        FoodType foodType = FoodType::Square;
        bool addSecondPlayer = false;
        User user;
        User userSecond;
    public:
    GameSettings(){
        this->readGameSettings();
    }
    GameSettings(bool verify){
        this->verify  = verify;
        this->readGameSettings();
    }
    void readGameSettings(){

        std::string line, key, value;
        std::ifstream file("/Users/oguz/Desktop/workspace_cpp/snake_game/CppND-Capstone-Snake-Game/config/config.yml");
        if (file.is_open()) {
            while (std::getline(file, line)) {

                std::replace(line.begin(), line.end(), '=', ' ');
                std::stringstream linestream(line);

                linestream >> key >>value;
                // Assign to variables based on key
                if (key == "username") this->user.username = value;
                else if (key == "gamespeed") this->gameSpeed = std::stof(value);
                else if (key == "obstacle") this->obstacle = (value == "true");
                //else if (key == "numSnakes") this->numSnakes = std::stoi(value);
                //else if (key == "movingObstacle") this->movingObstacle = (value == "true");
                else if (key == "userNameSecond") this->userSecond.username = value;
                else if (key == "addSecondPlayer")this->addSecondPlayer = (value == "true");
                else if (key == "food") {
                    if (value == "Square") this->foodType = FoodType::Square;
                    else if (value == "Circle") this->foodType = FoodType::Circle;
                    else if (value == "Triangle") this->foodType = FoodType::Triangle;
                }
            }
        }else{
            throw std::runtime_error("Error: Could not open config file.");
        }
        file.close();

    if(this->verify){
        // Print to verify
        std::cout << "Username: " << this->user.username << "\n";
        std::cout << "userNameSecond: " << this->userSecond.username << "\n";
        std::cout << "Gamespeed: " << this->gameSpeed << "\n";
        std::cout << "Obstacle: " << this->obstacle << "\n";
        //std::cout << "numSnakes: " << this->numSnakes << "\n";
        std::cout << "MovingObstacle: " << this->movingObstacle << "\n";
        std::cout << "Food: " << foodType << "\n";
        std::cout << "addSecondPlayer: " << addSecondPlayer << "\n";
    }
    }



};





#endif