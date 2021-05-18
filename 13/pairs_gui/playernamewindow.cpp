#include "playernamewindow.hh"
#include "ui_playernamewindow.h"

PlayerNameWindow::PlayerNameWindow(QWidget *parent, int player_number) :
    QMdiSubWindow(parent),
    ui(new Ui::PlayerNameWindow),
    player_number_(player_number)
{
    ui->setupUi(this);

    // Name the window
    QMdiSubWindow::setWindowTitle("Players' Names");

    // Create the dialog for the user to enter the players' names.
    // Using the QFormLayout to create the dialogs

    QFormLayout* formLayout = new QFormLayout;

    // Using a for loop to create the lineEdit widgets
    for (int i = 0; i < player_number_; i++) {
        QLineEdit* playerNameLineEdit = new QLineEdit(this);
        const QString prompt = "Enter the name of player " + QString::number(i+1);
        formLayout->addRow(prompt, playerNameLineEdit);
        player_name_line_edits_.push_back(playerNameLineEdit);
    }

    ui->playerNameDialogGroupBox->setLayout(formLayout);
}

PlayerNameWindow::~PlayerNameWindow()
{
    delete ui;
}

std::vector<std::string> PlayerNameWindow::get_player_names()
{
    return player_names_;
}


void PlayerNameWindow::on_okPushButton_clicked()
{
    for (int i = 0; i < player_number_; i++) {
        player_names_.push_back(
                    player_name_line_edits_.at(i)->text().toUtf8().constData());
    }

    emit playerNamesCompleted(this);
}
