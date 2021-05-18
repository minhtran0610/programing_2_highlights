#include "playerinformation.hh"
#include "ui_playerinformation.h"

PlayerInformation::PlayerInformation(QWidget *parent, std::string player_name) :
    QWidget(parent),
    ui(new Ui::PlayerInformation),
    player_name_(player_name),
    player_points_(0),
    players_cards_({})
{
    ui->setupUi(this);

    ui->playerNameLabel->setText(QString::fromStdString(player_name_));
    ui->pointsLabel->setText(QString::number(player_points_));
}

PlayerInformation::~PlayerInformation()
{
    delete ui;
}

std::string PlayerInformation::get_name()
{
    return player_name_;
}

int PlayerInformation::get_point()
{
    return player_points_;
}

void PlayerInformation::add_point()
{
    player_points_ += 1;
    ui->pointsLabel->setText(QString::number(player_points_));
}

void PlayerInformation::collect_card(Card* card)
{
    players_cards_.push_back(card);
}

void PlayerInformation::on_showCardsPushButton_clicked()
{
    PlayersCards* players_cards_dialog = new PlayersCards(this, players_cards_);
    players_cards_dialog->show();
}
