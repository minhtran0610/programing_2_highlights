#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>

class Player
{
public:
    // Constructor
    Player(const std::string& name);
    
    // Getting the name of the player
    std::string get_name();
    
    // Adding the points of the player
    void add_points(int point);
    
    // Getting the points of the player
    int get_points();
    
    // Check if the person has won
    bool has_won();
    
private:
    const std::string& name_;
    int points_;
    bool win_;
};

#endif // PLAYER_HH
