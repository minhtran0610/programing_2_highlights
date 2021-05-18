#include "leaderboard.hh"
#include "ui_leaderboard.h"

Leaderboard::Leaderboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Leaderboard)
{
    ui->setupUi(this);

    // Name the window
    QDialog::setWindowTitle("Leaderboard");

    save_results();

    // Set the rows and columns of the table
    ui->leaderboardTableWidget->setRowCount(ROW);
    ui->leaderboardTableWidget->setColumnCount(COLUMN);

    // Set the header of the table
    ui->leaderboardTableWidget->setHorizontalHeaderLabels(HEADER_LIST);

    // Add the data to the table
    add_entries_table();
}

Leaderboard::~Leaderboard()
{
    delete ui;
}

void Leaderboard::save_results()
{
    std::ifstream result_file(RESULT_FILE);

    if (is_empty(result_file)) {
        results_database_ = {};
    } else {
        std::string line = "";

        // Get the data from the file and add it to the database
        while (getline(result_file, line)) {
            std::vector<std::string> info = Leaderboard::split(line, 59);
            gameStruct game_result = {info.at(0), info.at(1),
                                      info.at(2), info.at(3)};
            results_database_.push_back(game_result);
        }

        // Close the file
        result_file.close();

        // Sort the database using the comparison ID
        std::sort(results_database_.begin(), results_database_.end(), compare_point);
    }
}

void Leaderboard::add_entries_table()
{
    if (results_database_.size() < ROW) {
        for (unsigned int i = 0; i < results_database_.size(); i++) {
            create_row(i);
        }
    } else {
        for (unsigned int i = 0; i < ROW; i++) {
            create_row(i);
        }
    }
}

void Leaderboard::create_table_widget_item(unsigned int row, unsigned int column, std::string data)
{
    ui->leaderboardTableWidget->setItem(row, column,
        new QTableWidgetItem(QString::fromStdString(data)));
}

void Leaderboard::create_row(unsigned int row)
{
    gameStruct entry = results_database_.at(row);

    create_table_widget_item(row, 0, entry.time);
    create_table_widget_item(row, 1, entry.card_number);
    create_table_widget_item(row, 2, entry.winner);
    create_table_widget_item(row, 3, entry.winner_point);
}

std::vector<std::string> Leaderboard::split(const std::string& s, const char delimiter,
                               bool ignore_empty){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool Leaderboard::is_empty(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

void Leaderboard::on_resetPushButton_clicked()
{
    std::ofstream file(RESULT_FILE);
    file.close();

    for (unsigned int i = 0; i < ROW; i++) {
        for (unsigned int j = 0; j < COLUMN; j++) {
            ui->leaderboardTableWidget->setItem(i,j, new QTableWidgetItem());
        }
    }
}
