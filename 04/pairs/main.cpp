/* Pairs
 *
 * Desc:
 *  This program generates a pairs (memory) game. The game has a variant
 * number of cards and players. At the beginning, the program also asks for a
 * seed value, since the cards will be set randomly in the game board.
 *  On each round, the player in turn gives the coordinates of two cards
 * (totally four numbers). After that the given cards will be turned as
 * visible and told if they are pairs or not. If they are pairs, they are
 * removed from the game board, the score of the player is increased, and
 * a new turn is given for the player. If the cards are not pairs, they
 * will be  turned hidden again, and the next player will be in turn.
 *  The program checks if the user-given coordinates are legal. The cards
 * determined by the coordinates must be found in the game board.
 *  After each change, the game board is printed again. The cards are
 * described as letters, starting from A and lasting so far as there are
 * cards. In printing the game board, a visible card is shown as its letter,
 * a hidden one as the number sign (#), and a removed one as a dot.
 *  Game will end when all pairs have been found, and the game board is
 * empty. The program tells who has/have won, i.e. collected most pairs.
 *
 * Program author
 * Name: Minh Tran
 * Student number: 050359358
 * UserID: mmmitr
 * E-Mail: minh.s.tran@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */


#include <player.hh>
#include <card.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Muuntaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan
// (mikä johtaa laittomaan korttiin myöhemmin).
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid card later).
unsigned int stoi_with_check(const string& str)
{
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

// Täyttää pelilaudan (kooltaan rows * columns) tyhjillä korteilla.
//
// Fills the game board, the size of which is rows * columns, with empty cards.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}

// Etsii seuraavan tyhjän kohdan pelilaudalta (g_board) aloittamalla
// annetusta kohdasta start ja jatkamalla tarvittaessa alusta.
// (Kutsutaan vain funktiosta init_with_cards.)
//
// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Aloitetaan annetusta arvosta
    //
    // Starting from the given value
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }
    // Jatketaan alusta
    //
    // Continuing from the beginning
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // Tänne ei pitäisi koskaan päätyä
    //
    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Alustaa annetun pelilaudan (g_board) satunnaisesti arvotuilla korteilla
// annetun siemenarvon (seed) perusteella.
//
// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Arvotaan täytettävä sijainti
    //
    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);
    // Hylätään ensimmäinen satunnaisluku (joka on aina jakauman alaraja)
    //
    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // Jos arvotussa sijainnissa on jo kortti, valitaan siitä seuraava tyhjä paikka.
    // (Seuraava tyhjä paikka haetaan kierteisesti funktion next_free avulla.)
    //
    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Lisätään kaksi samaa korttia (parit) pelilaudalle
        //
        // Adding two identical cards (pairs) in the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Tulostaa annetusta merkistä c koostuvan rivin,
// jonka pituus annetaan parametrissa line_length.
// (Kutsutaan vain funktiosta print.)
//
// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// (Called only by the function print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Tulostaa vaihtelevankokoisen pelilaudan reunuksineen.
//
// Prints a variable-length game board with borders.
void print(const Game_board_type& g_board)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Kysyy käyttäjältä tulon ja sellaiset tulon tekijät, jotka ovat
// mahdollisimman lähellä toisiaan.
//
// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

// Lisää funktioita
// More functions

// Get the names of the players, create Player objects and save them to a vector
std::vector<Player> get_players() {
    // Get the number of players
    int number_of_players = 0;
    while (not (number_of_players > 0)) {
        std::cout << INPUT_AMOUNT_OF_PLAYERS;
        std::string number_of_players_str = "";
        std::getline(std::cin, number_of_players_str);
        number_of_players = stoi_with_check(number_of_players_str);
    }

    // Get the name of the players and create Player objects for them
    std::vector<Player> players_vector;
    std::cout << "List " << number_of_players << " players: ";
    std::string name = "";
    for (int i =  0; i < number_of_players; i++) {
        std::cin >> name;
        players_vector.push_back(Player(name));
    }
    return players_vector;
}

// Print the players' information by looping through the Player vector
// and print each of them using the method in Player class
void print_players_info(vector<Player>& players_vector) {
    for (Player player : players_vector) {
        cout << "*** ";
        player.print();
    }
}

// Check the coordinates from the user to see their validity. Return true if the coordinates are valid
bool get_coordinates(vector<unsigned long int>& coordinates_vector, vector<string>& coordinates_str_vector, Game_board_type& game_board) {
    bool is_valid = true;

    // Turning coordinates in string to integers
    for (std::string coordinate_str : coordinates_str_vector) {
        unsigned long int coordinate = stoi_with_check(coordinate_str);
        coordinates_vector.push_back(coordinate);
    }

    // Check the validity of the coordinates
    if ((coordinates_vector.at(1) == 0 or coordinates_vector.at(1) > game_board.size()) or (coordinates_vector.at(3) == 0 or coordinates_vector.at(3) > game_board.size())) {
        is_valid = false;
    } else if ((coordinates_vector.at(0) == 0 or coordinates_vector.at(0) > game_board.at(0).size()) or (coordinates_vector.at(2) == 0 or coordinates_vector.at(2) > game_board.at(0).size())) {
        is_valid = false;
    } else if (game_board.at(coordinates_vector.at(1)-1).at(coordinates_vector.at(0)-1).get_visibility() == EMPTY or game_board.at(coordinates_vector.at(3)-1).at(coordinates_vector.at(2)-1).get_visibility() == EMPTY) {
        is_valid = false;
    } else if (coordinates_vector.at(0) == coordinates_vector.at(2) and coordinates_vector.at(1) == coordinates_vector.at(3)) {
        is_valid = false;
    } else {
        is_valid = true;
    }

    return is_valid;
}

// Turn the cards
void turn_cards(Card& card_1, Card& card_2, Game_board_type& game_board) {
    card_1.turn();
    card_2.turn();
    print(game_board);
}

// Check if the cards the user has chosen are a pair.
bool is_pair(Card& card_1, Card& card_2) {
    if (card_1.get_letter() == card_2.get_letter()) {
        return true;
    } else {
        return false;
    }
}

// Empty the cards if the cards are a pair
void empty_cards(Card& card_1, Card& card_2, Game_board_type& game_board) {
    card_1.remove_from_game_board();
    card_2.remove_from_game_board();
    print(game_board);
}

// Check if the game has finished by checking if all the cards are removed
// from the board
bool has_finished(Game_board_type& game_board) {
    for (Game_row_type& row : game_board) {
        for (Card& card : row) {
            if (card.get_visibility() != EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Sort the scores from high to low
void bubble_sort_descend(vector<int>& numbers_vector) {
    bool is_done = false;
    while (not is_done) {
        bool is_swapped = false;
        for (unsigned long int i=0; i < numbers_vector.size()-1; i++) {
            if (numbers_vector.at(i) < numbers_vector.at(i+1)) {
                int temp = numbers_vector.at(i);
                numbers_vector.at(i) = numbers_vector.at(i+1);
                numbers_vector.at(i+1) = temp;
                is_swapped = true;
            } else {
                ;
            }
            if (not is_swapped) {
                is_done = true;
            }
        }
    }
}

// Check the results and print them
void check_results(vector<Player>& players_vector) {
    vector<int> points_vector = {};
    vector<Player> winner = {};

    // Sort the points to find the maximum point
    for (Player player:players_vector) {
        points_vector.push_back((int)player.number_of_pairs());
    }
    int maximum_point = points_vector.at(0);

    // Find the players with the maximum point
    for (Player player:players_vector) {
        if (int(player.number_of_pairs()) == maximum_point) {
            winner.push_back(player);
        }
    }

    // Print the result message
    cout << GAME_OVER << endl;
    if (winner.size() == 1) {
        cout << winner.at(0).get_name() << " has won with " <<
                (int)winner.at(0).number_of_pairs() << " pairs.";
    } else {
        cout << "Tie of " << winner.size() << " players with "
             << maximum_point << " pairs.";
    }
}

// Switch turn
void switch_turn(int& turn, vector<Player> players_vector) {
    unsigned long int number_of_players = players_vector.size();

    turn ++;
    if ((unsigned long int)turn > number_of_players)
        turn -= number_of_players;
}

int main()
{
    Game_board_type game_board;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    // Lisää koodia
    // More code

    // Get the names and create Player objects for them
    vector<Player> players_vector = get_players();

    // Use a bool variable to track if the user quits the program or the program is stopped.
    // The game should start with the first player
    bool has_stopped = false;
    int turn = 1;
    print(game_board);

    // The program should run from here
    while (not has_stopped) {
        Player* in_turn = &players_vector.at(turn-1);
        // Get the coordinates from the user. The format of coordinates is string. If it's quit command, stop the game. If not,
        // check the coordinates.
        //
        // The valid coordinates will be stored in a vector
        std::vector<unsigned long int> coordinates_vector = {};
        vector<string> coordinates_str_vector = {};

        bool is_valid = false;
        while (not has_stopped and not is_valid) {
            cout << in_turn->get_name() << ": " << INPUT_CARDS;
            string coordinate_str = "";
            cin >> coordinate_str;

            // Check if the command is the quit command. If not, continue getting the coordinates.
            // Else, stop the program
            if (coordinate_str == "q") {
                std::cout << GIVING_UP << endl;
                has_stopped = true;
            } else {
                coordinates_vector = {};
                coordinates_str_vector = {};
                coordinates_str_vector.push_back(coordinate_str);
                for (int i = 0; i < 3; i++) {
                    cin >> coordinate_str;
                    coordinates_str_vector.push_back(coordinate_str);
                }
                is_valid = get_coordinates(coordinates_vector, coordinates_str_vector, game_board);
                if (not is_valid) {
                    cout << INVALID_CARD << endl;
                } else {
                    // Turning the cards

                    // First, get the cards from the coordinates that the user have entered
                    Card& card_1 = game_board.at(coordinates_vector.at(1)-1).at(coordinates_vector.at(0)-1);
                    Card& card_2 = game_board.at(coordinates_vector.at(3)-1).at(coordinates_vector.at(2)-1);

                    // Turn the cards and check if the cards are a pair. If they does, add the cards to the player
                    // Then update the table
                    turn_cards(card_1, card_2, game_board);
                    if (is_pair(card_1, card_2)) {
                        cout << FOUND << endl;
                        in_turn->add_card(card_1);
                        in_turn->add_card(card_2);
                        print_players_info(players_vector);
                        empty_cards(card_1, card_2, game_board);
                    } else {
                        cout << NOT_FOUND << endl;
                        print_players_info(players_vector);
                        turn_cards(card_1, card_2, game_board);
                        switch_turn(turn, players_vector);
                    }

                    // Check if the game has finished. If finished, find the winner
                    // If not, switch turn to the next player
                    if (has_finished(game_board)) {
                        check_results(players_vector);
                        has_stopped = true;
                    }
                }
            }
        }


    }

    return EXIT_SUCCESS;
}

