/* Class Card
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a card in the game.
 *
 * The class Card resembles a card in the pair game
 *
 * The class is based on QWidget object, which has a push button acts like
 * a real card. The Card object contains an UI, a letter and the state of
 * the card.
 *
 * The card can be "clicked" to turn the card. The hidden state of the class
 * is green color with pattern, and the open state is blue color with its
 * letter.
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef CARD_HH
#define CARD_HH

#include <QWidget>

// The enum type to store the states of the cards
enum Visibility_type {OPEN, HIDDEN, EMPTY};

namespace Ui {
class Card;
}

class Card : public QWidget
{
    Q_OBJECT

public: signals:
   void opened();

public:
    explicit Card(QWidget *parent = nullptr, char letter = 0);
    ~Card();

   // Get the visibility of the card
   Visibility_type get_visibility();

   // Set the visibility of the card
   void set_visibility(Visibility_type visibility);

   // Get the character of the card
   char get_letter();

   // Empty the card when they are a pair
   void empty_card();

   // Hide the card when they are not a pair
   void hide_card();

   // Disable the card
   void disable_card();

   // Enable the card
   void enable_card();

private slots:
    void on_cardPushButton_clicked();

private:
    Ui::Card *ui;

    // Attribute to store the letter and the visibility of the card
    char letter_;
    Visibility_type visibility_;

    // Ratio of icon and PNG image
    int RATIO = 15;
};

#endif // CARD_HH
