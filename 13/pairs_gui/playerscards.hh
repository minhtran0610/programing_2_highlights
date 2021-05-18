/* Class Leaderboard
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for showing the cards the player has collected
 *
 * The class will show the cards the players have collected inside a QGroupBox object.
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef PLAYERSCARDS_HH
#define PLAYERSCARDS_HH

#include <QDialog>
#include <card.hh>
#include <QHBoxLayout>

namespace Ui {
class PlayersCards;
}

class PlayersCards : public QDialog
{
    Q_OBJECT

public:
    explicit PlayersCards(QWidget *parent = nullptr, std::vector<Card*> = {});
    ~PlayersCards();

private:
    Ui::PlayersCards *ui;

    // The player's cards
    std::vector<Card*> players_cards_;
};

#endif // PLAYERSCARDS_HH
