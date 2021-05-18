#include "result.hh"
#include "ui_result.h"

Result::Result(QWidget *parent, std::string winner,
               std::string game_time, int winner_points) :
    QDialog(parent),
    ui(new Ui::Result),
    winner_(winner),
    game_time_(game_time),
    winner_points_(winner_points)
{
    ui->setupUi(this);

    // Name the window
    QDialog::setWindowTitle("Result");

    // Print the information
    ui->winnerLabel->setText(QString::fromStdString(winner_));
    ui->timeLabel->setText(QString::fromStdString(game_time_));
    ui->pointsLabel->setText(QString::number(winner_points_));
}

Result::~Result()
{
    delete ui;
}
