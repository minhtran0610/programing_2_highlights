#include "cards.hh"

// TODO: Implement the methods here
// Initialize the card
Cards::Cards(): top_(nullptr) {}

// Cards object destructor
Cards::~Cards() {
    while (top_ != nullptr) {
        Card_data* card_to_be_deleted = top_;
        top_ = top_->next;

        delete card_to_be_deleted;
    }
}

// Adds a new card with the given ID as the topmost position
void Cards::add(int id) {
    Card_data* new_card = new Card_data{id, nullptr};

    if (top_ == nullptr) {
        top_ = new_card;
    } else {
        new_card->next = top_;
        top_ = new_card;
    }
}

void Cards::print_from_bottom_to_top(std::ostream &s) {
    recursive_print(top_, s);
}

void Cards::print_from_top_to_bottom(std::ostream &s) {
    Card_data* card_to_be_printed = top_;
    int running_number = 1;

    while (card_to_be_printed != nullptr) {
        s << running_number << ": " << card_to_be_printed->data << std::endl;
        ++running_number;
        card_to_be_printed = card_to_be_printed->next;
    }
}

bool Cards::remove(int &id) {
    if (top_ == nullptr) {
        return false;
    }

    Card_data* card_to_be_removed = top_;
    id = card_to_be_removed->data;

    top_ = top_->next;
    delete card_to_be_removed;
    return true;

}

bool Cards::bottom_to_top() {
    if (top_ == nullptr) {
        return false;
    }

    if (top_->next == nullptr) {
        return true;
    }

    // Find the last card
    Card_data* card_to_be_moved = top_;
    while (card_to_be_moved->next != nullptr) {
        card_to_be_moved = card_to_be_moved->next;
    }

    // Remove the last card
    Card_data* temp = top_;
    while (temp->next != card_to_be_moved) {
        temp = temp->next;
    }
    temp->next = nullptr;

    // Add the card to the top
    card_to_be_moved->next = top_;
    top_ = card_to_be_moved;

    // Return true
    return true;
}

bool Cards::top_to_bottom() {
    if (top_ == nullptr) {
        return false;
    }

    if (top_->next == nullptr) {
        return true;
    }

    Card_data* card_to_be_moved = top_;
    Card_data* temp = top_;

    // Loop to the end of the deck
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    // Move the card to the bottom
    temp->next = card_to_be_moved;

    // Delete the first card
    top_ = top_->next;
    card_to_be_moved->next = nullptr;

    // Return
    return true;
}

void Cards::recursive_print(Card_data *top, std::ostream &s) {
    if (top->next != nullptr) {
       recursive_print(top->next, s);
    }
    s << increment_ << ": " << top->data << std::endl;
    increment_++;
}
