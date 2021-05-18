/* Class Result
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for showing the result of the game
 *
 * The class is based on QDialog object, which has labels to show the result
 * of the game: game time, winner and winners' points.
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef RESULT_HH
#define RESULT_HH

#include <QDialog>
#include <string>

namespace Ui {
class Result;
}

class Result : public QDialog
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = nullptr, std::string winner = "Player0",
                    std::string game_time = "00:00", int winner_points = 0);
    ~Result();

private:
    Ui::Result *ui;

    // Attributes to store the information of the game
    std::string winner_;
    std::string game_time_;
    int winner_points_;

};

#endif // RESULT_HH
