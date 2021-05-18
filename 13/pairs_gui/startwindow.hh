/* Class StartWindow
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for getting the game information of the game
 *
 * The class is based on QMdiSubWindow object, which lets the user
 * enter the number of players and number of cards
 *
 * The class also has a QTextBrowser object to display the errors of
 * the input: the number of cards and players is not a number greater than 0,
 * the number of cards is odd, the number of cards exceeds 52.
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH

#include <playernamewindow.hh>
#include <QWidget>
#include <QMdiSubWindow>
#include <iostream>
#include <string>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMdiSubWindow
{
    Q_OBJECT

public: signals:
    void startWindowCompleted(StartWindow* self);

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

    // Getters
    int get_numbers_of_cards();
    int get_numbers_of_players();
    std::vector<std::string> get_player_names();

    // Reset all the line edits
    void reset_line_edits();

private slots:
    void on_okPushButton_clicked();

    // This slot represents the moment the name input by the user is done
    void inputPlayerNamesFinished(PlayerNameWindow* player_name_window);

private:
    Ui::StartWindow *ui;

    // The attributes to store the number of cards and players
    int card_number_;
    int player_number_;
    std::vector<std::string> player_names_;

    // Converts the given numeric string to the corresponding integer
    // (by calling stoi).
    // If the given string is not numeric, returns 0
    // (which leads to an invalid card later).
    unsigned int stoi_with_check(const std::string& str);

    //Check if an user's input is valid (number of cards or number of players
    // is a number. Print the error message to the label in the window
    bool check_input(int& player_number, int& card_number);
};

#endif // STARTWINDOW_HH
