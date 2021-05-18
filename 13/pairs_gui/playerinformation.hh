/* Class Player
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a player in the game.
 *
 * The class Card resembles a player in the pair game
 *
 * This class is based on a QWidget object. This class includes a GUI for
 * the players' card decks, points and names, as well as process the actions
 * of adding points for the player.
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef PLAYERINFORMATION_HH
#define PLAYERINFORMATION_HH

#include <QWidget>
#include <playerscards.hh>

namespace Ui {
class PlayerInformation;
}

class PlayerInformation : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInformation(QWidget *parent = nullptr, std::string player_name  = "Player");
    ~PlayerInformation();

    // Getters
    int get_point();
    std::string get_name();

    // Add a point to player when the player find 1 pair
    void add_point();

    // Collect the card the player has won
    void collect_card(Card* card);

private slots:
    void on_showCardsPushButton_clicked();

private:
    Ui::PlayerInformation *ui;

    // Attributes to store player's name and points
    std::string player_name_;
    int player_points_;
    std::vector<Card*> players_cards_ = {};
};

#endif // PLAYERINFORMATION_HH
