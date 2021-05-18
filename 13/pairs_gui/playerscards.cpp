#include "playerscards.hh"
#include "ui_playerscards.h"

PlayersCards::PlayersCards(QWidget *parent, std::vector<Card*> players_cards) :
    QDialog(parent),
    ui(new Ui::PlayersCards),
    players_cards_(players_cards)
{
    ui->setupUi(this);

    QHBoxLayout* hLayout = new QHBoxLayout;

    for (auto card : players_cards_) {
        hLayout->addWidget(card);
        card->show();
    }

    ui->playerCardsGroupBox->setLayout(hLayout);
}

PlayersCards::~PlayersCards()
{
    delete ui;
}
