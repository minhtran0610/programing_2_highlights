#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    timer_(new QTimer(this)),
    turn_(0),
    number_open_cards_(0)
{
    ui->setupUi(this);

    // Create the start window to get the information of the game
    start_window_ = new StartWindow(this);
    start_window_->show();

    // Set the layout to some of the widgets
    grid_layout_ = new QGridLayout();
    vertical_layout_ = new QVBoxLayout();

    ui->cardsGroupBox->setLayout(grid_layout_);
    ui->playerInformationGroupBox->setLayout(vertical_layout_);

    // Set the window title
    MainWindow::setWindowTitle("Pairs");

    connect(start_window_, &StartWindow::startWindowCompleted,
            this, &MainWindow::finishedStartWindow);

    // Start to create the cards when the players are created
    connect(this, &MainWindow::creatingPlayersFinished,
            this, &MainWindow::createCards);

    // When all the cards are created and the game is ready to be started,
    // start the timer
    connect(this, &MainWindow::creatingCardsFinished,
            this, &MainWindow::startTimer);
    connect(timer_, &QTimer::timeout, this, &MainWindow::onTimerTimeout);

    // Examine the change of players' turns when 2 cards are drawn
    connect(this, &MainWindow::twoCardsDrawn,
            this, &MainWindow::manageTurn);

    // Disable the cards when 2 cards are drawn
    connect(this, &MainWindow::twoCardsDrawn,
            this, &MainWindow::disableAllCards);

    // When a pair of cards are drawn, check if the game has finished
    connect(this, &MainWindow::twoCardsDrawn,
            this, &MainWindow::checkFinishedGame);

    // When the game is finished, stop the timer and show the result
    connect(this, &MainWindow::gameFinished,
            this, &MainWindow::stopTimer);
    connect(this, &MainWindow::gameFinished,
            this, &MainWindow::showResult);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::finishedStartWindow(StartWindow* start_window)
{
    // Get the information provided by the start window
    player_names_ = start_window->get_player_names();
    player_number_ = start_window->get_numbers_of_players();
    card_number_ = start_window->get_numbers_of_cards();

    start_window->hide();

    // Create new PLayerInformation objects
    for (std::string player_name : player_names_) {
        PlayerInformation* player_information = new PlayerInformation(this, player_name);
        player_information->setStyleSheet("background: yellow");
        player_information_objects_.push_back(player_information);

        vertical_layout_->addWidget(player_information);
    }

    // Highlight the turn of the first player. Each player in turn will be
    // highlighted with red color
    in_turn_ = player_information_objects_.at(0);
    in_turn_->setStyleSheet("background: red");

    emit creatingPlayersFinished();
}

void MainWindow::createCards()
{
    std::string card_letters = shuffle_letters(card_number_, ALPHABET);

    // Calculate the dimension of the height and the width
    calculate_factors(card_number_, height_, width_);

    // Create the cards and add them to the layout
    for (int i = 0; i < height_; i++) {
        std::vector<Card*> card_row_vector = {};
        for (int j = 0; j < width_; j++) {
            Card* card = new Card(this, card_letters.at(width_*i+j));
            card_row_vector.push_back(card);
            grid_layout_->addWidget(card, i, j);

            // Connect the opened signals from the cards
            connect(card, &Card::opened,
                    this, &MainWindow::handleCardsPairClicks);
        }
        card_objects_.push_back(card_row_vector);
    }

    // Emit the signal
    emit creatingCardsFinished();
}

void MainWindow::calculate_factors(int& product, int &smaller_factor, int &bigger_factor)
{

    for(int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

std::string MainWindow::shuffle_letters(int &card_number, std::string& alphabet)
{
    int number_letter = card_number/2;

    // Create a string containing the letters for the cards
    std::string card_letters = "";

    for (int i = 0; i < number_letter; i++) {
        card_letters += alphabet.at(i);
        card_letters += alphabet.at(i);
    }

    // Shuffle the string
    std::random_shuffle(card_letters.begin(), card_letters.end());

    return card_letters;
}

std::vector<Card *> MainWindow::find_opened_cards()
{
    std::vector<Card*> currently_open_cards;
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            if (card_objects_.at(i).at(j)->get_visibility() == OPEN) {
                currently_open_cards.push_back(card_objects_.at(i).at(j));
            }
        }
    }

    return currently_open_cards;
}

std::vector<PlayerInformation *> MainWindow::find_winner()
{
    // Find the highest point
    int max_point = 0;

    for (PlayerInformation* player : player_information_objects_) {
        if (player->get_point() >= max_point) {
            max_point = player->get_point();
        }
    }

    // Find the players with the highest points
    std::vector<PlayerInformation*> winners = {};

    for (PlayerInformation* player : player_information_objects_) {
        if (player->get_point() == max_point) {
            winners.push_back(player);
        }
    }

    return winners;
}

std::string MainWindow::get_time(unsigned int &minute, unsigned int &second)
{
    std::string minute_str = "";
    std::string second_str = "";

    if (minute < 10) {
        minute_str = "0" + std::to_string(minute);
    } else {
        minute_str = std::to_string(minute);
    }

    if (second < 10) {
        second_str = "0" + std::to_string(second);
    } else {
        second_str = std::to_string(second);
    }

    return minute_str + ":" + second_str;
}

void MainWindow::check_cards_pair()
{
    if (opened_card_1_->get_letter() == opened_card_2_->get_letter()) {
        is_pair_ = true;
        opened_card_1_->set_visibility(EMPTY);
        opened_card_2_->set_visibility(EMPTY);
    } else {
        is_pair_ = false;
        opened_card_1_->set_visibility(HIDDEN);
        opened_card_2_->set_visibility(HIDDEN);
    }
}

void MainWindow::checkFinishedGame()
{
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            if (card_objects_.at(i).at(j)->get_visibility() != EMPTY) {
                return;
            }
        }
    }

    emit gameFinished();
}

void MainWindow::showResult()
{
    // Retrieve the information of the game
    // Get the time
    unsigned int minute = ui->lcdNumberMin->intValue();
    unsigned int second = ui->lcdNumberSec->intValue();

    std::string game_time = get_time(minute, second);

    // Get the winners' name and points
    std::vector<PlayerInformation*> winners = find_winner();

    std::string winners_name = "";
    for (PlayerInformation* winner : winners) {
        winners_name += winner->get_name() + ", ";
    }
    winners_name = winners_name.substr(0, winners_name.length()-2);

    int point = winners.at(0)->get_point();

    // Create a dialog with the results
    Result* result = new Result(this, winners_name, game_time, point);
    result ->show();

    // Save the result to the record file
    std::ofstream result_file(RESULT_FILE, std::ios_base::app | std::ios_base::out);

    std::string result_line = game_time + ";" + std::to_string(card_number_) + ";"
            + winners_name + ";" + std::to_string(point);

    result_file << result_line << std::endl;

    result_file.close();
}

void MainWindow::disableAllCards()
{
    for (std::vector<Card*> row : card_objects_) {
        for (Card* card : row) {
            card->disable_card();
        }
    }

    QTimer::singleShot(DELAY, this, SLOT(waitAndEnableCard()));
}

void MainWindow::waitAndEnableCard()
{
    for (std::vector<Card*> row : card_objects_) {
        for (Card* card : row) {
            card->enable_card();
        }
    }
}

void MainWindow::handleCardsPairClicks()
{
    number_open_cards_++;

    if (number_open_cards_ == 2) {
        std::vector<Card*> currently_opened_cards = find_opened_cards();
        if (currently_opened_cards.size() == 1) {
            // If the user click 1 card twice, don't do anything
            number_open_cards_ = 1;
        } else {
            // Process the card pair
            opened_card_1_ = currently_opened_cards.at(0);
            opened_card_2_ = currently_opened_cards.at(1);


            check_cards_pair();
            emit twoCardsDrawn();
            number_open_cards_ = 0;

            // Carry out action on the card
            QTimer::singleShot(DELAY, this, SLOT(cardAction()));

            return;
        }
    }
}

void MainWindow::manageTurn()
{
    if (not is_pair_) {
        in_turn_->setStyleSheet("background: yellow");
        turn_ += 1;
        in_turn_ = player_information_objects_.at(turn_%player_number_);
        in_turn_->setStyleSheet("background: red");
    } else {
        in_turn_->add_point();
        in_turn_->collect_card(opened_card_1_);
    }
}

void MainWindow::startTimer()
{
    timer_->start(DELAY);
}

void MainWindow::stopTimer()
{
    timer_->stop();
}

void MainWindow::onTimerTimeout()
{
    int current_minute = ui->lcdNumberMin->intValue();
    int current_second = ui->lcdNumberSec->intValue();

    if (current_second == 59) {
        ui->lcdNumberMin->display(current_minute + 1);
        ui->lcdNumberSec->display(0);
    } else {
        ui->lcdNumberSec->display(current_second + 1);
    }
}

void MainWindow::cardAction()
{
    if (is_pair_) {
        opened_card_1_->empty_card();
        opened_card_2_->empty_card();
    } else {
        opened_card_1_->hide_card();
        opened_card_2_->hide_card();
    }
}

void MainWindow::on_leaderboardsPushButton_clicked()
{
    Leaderboard* leaderboard = new Leaderboard(this);
    leaderboard->show();
}

void MainWindow::on_replayPushButton_clicked()
{
    start_window_->show();
    start_window_->reset_line_edits();

    for (auto item : player_information_objects_) {
        delete item;
    }
    player_information_objects_.clear();

    for (auto row : card_objects_) {
        for (auto item : row) {
            delete item;
        }
        row.clear();
    }
    card_objects_.clear();

    timer_->stop();
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);

    // player_names_.clear();

}
