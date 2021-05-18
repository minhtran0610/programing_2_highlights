/* Class PlayerNameWindow
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for getting the name of the players.
 *
 * The class is based on QMdiSubWindow object, which features a FormLayout to
 * get the players' names from the user.
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef PLAYERNAMEWINDOW_HH
#define PLAYERNAMEWINDOW_HH

#include <QWidget>
#include <QMdiSubWindow>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class PlayerNameWindow;
}

class PlayerNameWindow : public QMdiSubWindow
{
    Q_OBJECT

public: signals:
    void playerNamesCompleted(PlayerNameWindow* self);

public:
    explicit PlayerNameWindow(QWidget *parent = nullptr, int player_number = 1);
    ~PlayerNameWindow();

    // Getters
    std::vector<std::string> get_player_names();

private slots:
    void on_okPushButton_clicked();

private:
    Ui::PlayerNameWindow *ui;

    // Attributes to store the player numbers and player names
    int player_number_;
    std::vector<std::string> player_names_;
    std::vector<QLineEdit*> player_name_line_edits_;

    // Create the player LineEdit widgets for the user to enter the players'
    // names
    void init_player_name_widgets();
};

#endif // PLAYERNAMEWINDOW_HH
