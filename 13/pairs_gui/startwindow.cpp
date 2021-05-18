#include "startwindow.hh"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMdiSubWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    // Name the window
    QMdiSubWindow::setWindowTitle("Game Information");
}

StartWindow::~StartWindow()
{
    delete ui;
}

int StartWindow::get_numbers_of_cards()
{
    return card_number_;
}

int StartWindow::get_numbers_of_players()
{
    return player_number_;
}

std::vector<std::string> StartWindow::get_player_names()
{
    return player_names_;
}

void StartWindow::reset_line_edits()
{
    ui->numCardsLineEdit->clear();
    ui->numPlayersLineEdit->clear();
}

void StartWindow::on_okPushButton_clicked()
{
    std::string num_player_string = ui->numPlayersLineEdit->text().toUtf8().constData();
    std::string num_card_string = ui->numCardsLineEdit->text().toUtf8().constData();

    player_number_ = stoi_with_check(num_player_string);
    card_number_ = stoi_with_check(num_card_string);

    if (check_input(player_number_, card_number_)) {
        PlayerNameWindow* player_name_window = new PlayerNameWindow(this, player_number_);
        player_name_window->show();

        connect(player_name_window, &PlayerNameWindow::playerNamesCompleted,
                this, &StartWindow::inputPlayerNamesFinished);
    }
}

void StartWindow::inputPlayerNamesFinished(
        PlayerNameWindow* player_name_window)
{
    player_names_ = player_name_window->get_player_names();
    player_name_window->hide();

    emit startWindowCompleted(this);
}

unsigned int StartWindow::stoi_with_check(const std::string& str)
{
    if (str.length() == 0) {
        return 0;
    }

    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

bool StartWindow::check_input(int &player_number, int &card_number)
{
    // Error messages for the Label widget in the UI
    const QString INVALID_INPUT = "Number of cards or number of players must be "
                                  "a number greater than 0.";
    const QString CARD_NUMBER_ODD = "Number of cards must be an even number.";
    const QString CARD_NUMBER_EXCEEDED_MAX = "The maximum number of cards is 52.";

    int MAX_CARD_NUMBER = 52;

    // Check if the user has entered a valid number
    if (player_number == 0 or card_number == 0) {
        ui->errorTextBrowser->setText(INVALID_INPUT);
        return false;
    }

    // Check if the number of cards is divisible by 2
    if (card_number % 2 != 0) {
        ui->errorTextBrowser->setText(CARD_NUMBER_ODD);
        return false;
    }

    // Check if the number of cards have exceeded the maximum number
    if (card_number > MAX_CARD_NUMBER) {
        ui->errorTextBrowser->setText(CARD_NUMBER_EXCEEDED_MAX);
        return false;
    }

    return true;
}

