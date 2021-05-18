#include "card.hh"
#include "ui_card.h"

Card::Card(QWidget *parent, char letter) :
    QWidget(parent),
    ui(new Ui::Card),
    letter_(letter),
    visibility_(HIDDEN)
{
    ui->setupUi(this);

    // Set the color of the card
    ui->cardPushButton->setStyleSheet("background: green");
    // ui->cardPushButton->setIcon("pattern.png");
    QPixmap pattern(QString::fromStdString("pattern.png"));
    ui->cardPushButton->setIcon(pattern);
    ui->cardPushButton->setIconSize(pattern.size()/RATIO);
}

Card::~Card()
{
    delete ui;
}

void Card::on_cardPushButton_clicked()
{
    // Remove the icon
    ui->cardPushButton->setIcon(QIcon());

    // Print the letter on the card
    ui->cardPushButton->setText(QString(QChar(letter_)));

    // Change the color of the card
    ui->cardPushButton->setStyleSheet("background: blue");

    // Change the status of the button
    visibility_ = OPEN;

    // Emit the signal
    emit opened();
}

Visibility_type Card::get_visibility()
{
    return visibility_;
}

void Card::set_visibility(Visibility_type visibility)
{
    visibility_ = visibility;
}

char Card::get_letter()
{
    return letter_;
}

void Card::empty_card()
{
    this->hide();
}

void Card::hide_card()
{
    ui->cardPushButton->setText("");
    ui->cardPushButton->setStyleSheet("background: green");

    QPixmap pattern(QString::fromStdString("pattern.png"));
    ui->cardPushButton->setIcon(pattern);
    ui->cardPushButton->setIconSize(pattern.size()/RATIO);
}

void Card::disable_card()
{
    ui->cardPushButton->setEnabled(false);
}

void Card::enable_card()
{
    ui->cardPushButton->setEnabled(true);
}
