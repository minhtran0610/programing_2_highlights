#include <iostream>
#include <vector>
#include <string>

using namespace std;

const std::vector<char> OPERATORS = {'+', '-', '*', '/'};
const std::vector<char> OPERANDS = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const int NUM_OF_ITEMS = 25;

// Split the string according to the given separator
/*
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
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
*/


// Check if a part in the command is an operator
bool is_operator(char part) {
    for (unsigned long int i = 0; i < OPERATORS.size(); i++) {
        if (part == OPERATORS[i]) {
            return true;
        }
    }
    return false;
}


// Check if a part in the command is an operand
bool is_operand(char part) {
    for (unsigned long int i = 0; i < OPERANDS.size(); i++) {
        if (part == OPERANDS[i]) {
            return true;
        }
    }
    return false;
}

// Check the errors of the command is valid
bool is_valid_command(std::string command) {
    if (not is_operand(command.at(0))) {
        cout << "Error: Expression must start with a number" << endl;
        return false;
    }

    int num_of_operands = 0;
    int num_of_operators = 0;

    for (char c : command) {
        if (c == '#') {
            break;
        } else if (c == ' ') {
            ;
        } else if (not is_operand(c) and not is_operator(c)) {
            cout << "Error: Unknown character" << endl;
            return false;
        } else if (is_operand(c)) {
            num_of_operands++;
        } else {
            num_of_operators++;
        }
    }

    if (num_of_operands > num_of_operators+1) {
        cout << "Error: Too few operators" << endl;
        return false;
    } else if (num_of_operands <= num_of_operators) {
        cout << "Error: Too few operands" << endl;
        return false;
    }

    return true;
}

// Carry out the computation
bool polish_notation_calculation(std::string command) {
    int num_array[NUM_OF_ITEMS] = {};

    // Pointer to the first element
    int* pointer = num_array;

    for (char c : command) {
        if (is_operand(c)) {
            *pointer = c - 48;
            ++pointer;
        } else if (c == ' ') {
            ;
        } else if (c == '#') {
            break;
        } else {
            // If the character is an operator, first, get the operands
            --pointer;
            int second_operand = *pointer;
            --pointer;
            int first_operand = *pointer;

            // Calculate the result
            if (c == '+') {
                *pointer = first_operand + second_operand;
                ++pointer;
            } else if (c == '-') {
                *pointer = first_operand - second_operand;
                ++pointer;
            } else if (c == '*') {
                *pointer = first_operand * second_operand;
                ++pointer;
            } else {
                if (second_operand == 0) {
                    cout << "Error: Division by zero" << endl;
                    return false;
                } else {
                    *pointer = first_operand/second_operand;
                    ++pointer;
                }
            }
        }
    }

    --pointer;
    cout << "Correct: " << *pointer << " is the result" << endl;
    return true;
}


int main()
{
    std::cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    string command = "";
    getline(cin, command);

    // Carry out the computation
    if (is_valid_command(command)) {
        if (polish_notation_calculation(command)) {
            return EXIT_SUCCESS;
        } else {
            return EXIT_FAILURE;
        }
    } else {
        return EXIT_FAILURE;
    }

}
