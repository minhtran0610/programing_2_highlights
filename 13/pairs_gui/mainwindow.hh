/* Class MainWindow
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for the main window of the game
 *
 * The class manage the GUI of the whole application. It controls
 * the input of game information, player names, handle the cards, show the time,
 * show the result and save the data of the game.
 *
 * More explanation of the functionalities of the class (and also other classes)
 * will be described in the documentation, as it is mainly the same as the
 * main functions of the whole application.
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <startwindow.hh>
#include <playerinformation.hh>
#include <card.hh>
#include <result.hh>
#include <leaderboard.hh>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include <ios>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private: signals:
    void creatingPlayersFinished();
    void creatingCardsFinished();

    // Signal to check if 2 cards has been drawn
    void twoCardsDrawn();

    // Signal that the game has finished
    void gameFinished();

private slots:
    void finishedStartWindow(StartWindow* start_window);

    void createCards();

    // Handle the click of 2 cards
    void handleCardsPairClicks();

    // Manage the turns of the players
    void manageTurn();

    // Start the timer
    void startTimer();

    // Stop the timer
    void stopTimer();

    // Slot for the Timeout signal, this is used for changing the LCD clock
    void onTimerTimeout();

    // Turn or empty the card depends on if they are a pair or not
    void cardAction();

    // Check if the game has finished. If does, emit the finished signal
    void checkFinishedGame();

    // Find the winner and print the result after the game
    void showResult();

    // Disable all buttons when 2 cards are drawn
    void disableAllCards();

    // Wait 1 second to enable the cards again
    void waitAndEnableCard();

    // When the Leaderboards button clicked
    void on_leaderboardsPushButton_clicked();

    void on_replayPushButton_clicked();

private:
    Ui::MainWindow *ui;

    // Start window to get the information of the game
    StartWindow* start_window_;

    // Layouts to use in the window
    QVBoxLayout* vertical_layout_;
    QGridLayout* grid_layout_;

    // QTimer attribute for time management
    QTimer* timer_;
    // An attribute representative of 1 second
    int DELAY = 1000;

    // Attributes for information on players and cards
    int player_number_;
    int card_number_;
    std::vector<std::string> player_names_;

    // The container PlayerInformation and Card objects
    std::vector<PlayerInformation*> player_information_objects_;
    std::vector<std::vector<Card*>> card_objects_;

    // The alphabet for the letters
    std::string ALPHABET =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // The dimensions of the board
    int width_;
    int height_;

    // Attributes to keep track of the turns of the players
    int turn_;
    PlayerInformation* in_turn_;

    // Attributes to keep track of the currently opened cards
    Card* opened_card_1_;
    Card* opened_card_2_;

    // Boolean variable to check if a player has drawn a pair
    bool is_pair_;

    // Calculate the number of rows and columns according
    // to the number of cards
    void calculate_factors(int& product, int& smaller_factor, int& bigger_factor);

    // An attribute to keep track of the number of cards is opened at a time
    int number_open_cards_;

    // File to save the results
    std::string RESULT_FILE = "results.record";

    // Shuffle the letters and decide the letters for each card
    std::string shuffle_letters(int& card_number, std::string& alphabet);

    // Find the opened cards
    std::vector<Card*> find_opened_cards();

    // Check if 2 open cards has the same character. If so, hide the cards.
    // Else, close the cards
    void check_cards_pair();

    // Find the winner
    // Return more than 1 player if the game is drawn between some players
    std::vector<PlayerInformation*> find_winner();

    // Get the time in std::string
    std::string get_time(unsigned int& minute, unsigned int& second);
};
#endif // MAINWINDOW_HH
