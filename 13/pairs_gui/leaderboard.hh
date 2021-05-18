/* Class Leaderboard
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for showing the leaderboard of the game
 *
 * The class is based on QDialog object, which mainly features a QTableWidget
 * to store the results of the previous games.
 *
 * The leaderboard will show the five games with the highest winner score.
 * The information of previous games is saved in a text file.
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef LEADERBOARD_HH
#define LEADERBOARD_HH

#include <QDialog>
#include <QStringList>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace Ui {
class Leaderboard;
}

class Leaderboard : public QDialog
{
    Q_OBJECT

public:
    explicit Leaderboard(QWidget *parent = nullptr);
    ~Leaderboard();

private slots:
    void on_resetPushButton_clicked();

private:
    Ui::Leaderboard *ui;

    // Name of the result file
    std::string RESULT_FILE = "results.record";

    // Data structure for a single game
    struct gameStruct {
        std::string time;
        std::string card_number;
        std::string winner;
        std::string winner_point;
    };

    std::vector<gameStruct> results_database_;

    // Save the result from the file into the database
    void save_results();

    // Number of rows and columns
    unsigned int ROW = 5;
    unsigned int COLUMN = 4;

    // Header list
    QStringList HEADER_LIST = {"Time", "Number of cards", "Winner", "Winner's points"};

    // Add the entries to the table
    void add_entries_table();

    // Create a TableWidgetItem for a cell
    // The function takes 3 arguments for the number of rows, the number of
    // columns and the data
    void create_table_widget_item(unsigned int row, unsigned int column, std::string data);

    // Create a row for 1 entry. The function takes 1 argument: number of rows
    void create_row(unsigned int row);

    // Split function
    std::vector<std::string> split(const std::string& s, const char delimiter,
                                   bool ignore_empty = false);

    // Static comparison ID
    static bool compare_point(const gameStruct& game_1, const gameStruct& game_2) {
        return std::stoi(game_1.winner_point) > std::stoi(game_2.winner_point);
    }

    // Check if the input file is empty
    bool is_empty(std::ifstream& pFile);

};

#endif // LEADERBOARD_HH
