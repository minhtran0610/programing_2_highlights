#include "player.hh"
#include <iostream>

// Lisää luokan toteutus tähän.
// Kuhunkin julkiseen metodiin pitäisi riittää 1-2 koodiriviä.

// Add class implementation here.
// It should be enough to write only 1-2 code lines in each public method.

Player::Player(const std::string& name):
    name_(name), cards({ })  {}

// Return the player's name
std::string Player::get_name() const {
    return name_;
}

// Return the number of pairs the player have
unsigned int Player::number_of_pairs() const {
    return cards.size()/2;
}

// Add the player's recently collected card
void Player::add_card(Card &card) {
    cards.push_back(card);
}

// Print the information (number of pairs) of the players
void Player::print() const {
    std::cout << name_ << " has " << cards.size()/2 << " pair(s)." << std::endl;
}
