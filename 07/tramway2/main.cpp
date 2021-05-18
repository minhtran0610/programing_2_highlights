/* Class: Line
 *
 * Desription:
 *  This program reads information concerning tramways from the input file,
 * stores them into a suitable data structure, and then permits the user to
 * make searches, insertions, and removals in the data structure in question.
 *  The prgogram can read the information of the lines and the stops through
 * an input text file. Then, the lines are stored as Line objects, with stops
 * and distances are inside the variables of the object. The data of the file
 * are stored in a map with the keys as the line names and the values as the
 * corresponding Line objects.
 *  There are 9 commands the user can interact with the program.
 *  -   QUIT: Quit the command
 *  -   LINES: List the lines in alphabetical order
 *  -   LINE <line>: List the stops and distances of the line in the order
 *      of ascending distance. AN error message will occur if the line
 *      is not in the database.
 *  -   STOPS: List all the stops in alphabetical order
 *  -   STOP <stop>: List the lines that stop at the given stop, in alphabetical
 *      order. If the stop is not found in the database, an error message will
 *      occur.
 *  -   DISTANCE <line> <stop 1> <stop 2>: Calculate the distance of the 2 stops.
 *      An error message will occur if: 1. The line does not exist or 2. The stops
 *      do not exist in the line.
 *  -   ADDLINE <line>: Add a new line (without stops) to the database. An error message
 *      will occur if the line already exists.
 *  -   ADDSTOP <line> <stop> <distance>: Add a new stop with its distance to the line.
 *      An error message will occur if: 1. The line does not exist or 2. The stops
 *      or distance is already in the line.
 *  -   REMOVE <stop>: Remove the given stop from all the lines. An error message will
 *      occur if the stop does not exist.
 *  If the command is unknown, or the command does not contain enough parameters, an error message
 * will occur.
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


#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <cctype>
#include "line.hh"


// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}


// Splits a string with the separator given by the user
// The function takes the string and the separator, then returns
// a vector with the separated parts of that string.
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


// Read the input file and save the information to the database for the
// lines and stops. If the reading of the file is successful, return true.
// Return false otherwise
bool read_file(std::string& file_name, std::map<std::string, Line>& lines_database, std::set<std::string>& all_stop_names_set) {
    std::ifstream file_object(file_name);

    // If the file cannot be opened, print the error message, and return false
    if (not file_object) {
        std::cout << "Error: File could not be read." << std::endl;
        return false;
    }

    // Loop through the lines
    std::string file_line;
    while(getline(file_object, file_line)) {
        std::vector<std::string> stop_data = split(file_line, ';');
        // Check if the line is in valid format
        if ((stop_data.size() != 2 and stop_data.size() != 3) or stop_data.at(1) == "") {
            std::cout << "Error: Invalid format in file." << std::endl;
            return false;
        }
        
        // Get the data from the line and create the lines with the appropriate stops
        // In case the distance is not provided, assume that distance is zero for
        // every stop and change that number when a number different from zero is provided
        std::string line_name = stop_data.at(0);
        std::string stop_name = stop_data.at(1);
        double distance_of_stop = 0;
        if (stop_data.size() == 3 and stop_data.at(2) != "") {
            distance_of_stop = std::stod(stop_data.at(2));
        }
        
        // Check if the line already has a Line_object associated to it. If does, add the stop to
        // the existing line. Else, create a Line object for that line and add the stop.
        if (lines_database.find(line_name) != lines_database.end()) {
            if (not lines_database.at(line_name).add_stop(stop_name, distance_of_stop)) {
                std::cout << "Error: Stop/line already exists." << std::endl;
                return false;
            } else {
                all_stop_names_set.insert(stop_name);
            }
        } else {
            Line new_line_object = Line(line_name);
            new_line_object.add_stop(stop_name, distance_of_stop);
            lines_database.insert({line_name, new_line_object});
            all_stop_names_set.insert(stop_name);
        }
    }
    return true;
}


// Process the parameters that are marked with quotation marks
// The function returns a vector with the parameters processed forq
// the commands
std::vector<std::string> process_quote(std::vector<std::string> parts) {
    // Store all the parameters in a vector
    std::vector<std::string> parameter_lists;
    // Loop through the parts to find the part that starts with a quotation mark. Then
    // continue looping through the parts to find the part that ends with a quotation
    // mark.
    for (unsigned long int i = 1; i < parts.size(); i++) {
        if (parts.at(i).at(0) == '"') {
            std::string parameter = "";
            parts.at(i) = parts.at(i).substr(1);
            for (unsigned long int j = i; j < parts.size(); j++) {
                if (parts.at(j).back() == '"') {
                    // If the part is the end of a parameter, add it to the parameter
                    // string
                    parameter += parts.at(j).substr(0, parts.at(j).length()-1);
                    i = j;
                    break;
                } else {
                    // If the part is in the middle of a parameter, add it to the
                    // parameter with a space for the latter parts
                    parameter += (parts.at(j) + " ");
                }
            }
            // Add the parameter to the vector
            parameter_lists.push_back(parameter);
        } else {
            parameter_lists.push_back(parts.at(i));
        }
    }
    return parameter_lists;
}


// Check if the command provides sufficient parameters. Return false and print the
// error message if the number of parameters is less than the required.
// Return true otherwise
bool parameters_are_sufficient(std::vector<std::string>& parameters_vector, unsigned long int number_of_parameters) {
    if (parameters_vector.size() >= number_of_parameters) {
        return true;
    }
    std::cout << "Error: Invalid input." << std::endl;
    return false;
}


// Check if the given line exists. Return true if the line can be found in the database,
// false otherwise. Also, print the error message.
bool line_is_valid(std::map<std::string, Line>& lines_database, const std::string line_name) {
    if (lines_database.find(line_name) != lines_database.end()) {
        return true;
    }
    std::cout << "Error: Line could not be found." << std::endl;
    return false;
}


// Check if the given stop exists. Return true if the stop can be found in the database, false
// otherwise. When the return is false, print the error message
bool stop_is_valid(std::set<std::string>& all_stop_names_set, const std::string stop_name) {
    if (all_stop_names_set.find(stop_name) != all_stop_names_set.end()){
        return true;
    }
    std::cout << "Error: Stop could not be found." << std::endl;
    return false;
}


// Check if the line already exists or the stop has already available in the line. This
// function is used for the ADDLINE and ADDSTOP command.
// The reason to have another function is to have 2 things checked and give 1 error message.
// Also, this funciton check for the stop in a line, whereas the stop_is_valid() function
// checks the stop in the whole database.
bool line_or_stop_does_not_exists(std::map<std::string, Line>& lines_database, const std::string line_name, const std::string stop_name = "", const double distance = 0) {
    // Boolean variable to keep track of the return of the function
    bool result = true;
    // If the name of the stop is not given, the function
    // will check for the existence of the line.
    if (stop_name == "") {
        if (lines_database.find(line_name) != lines_database.end()) {
            result = false;
        }
    }
    // Else, if the name of the stop is given, check the existence of the
    // stop in the line.
    else {
        if (lines_database.at(line_name).has_stop(stop_name) or lines_database.at(line_name).has_distance(distance)){
            result = false;
        }
    }

    // Return false and print the error message if the line
    // or stop already exists. True otherwise
    if (not result) {
        std::cout << "Error: Stop/line already exists." << std::endl;
    }
    return result;
}


// Short and sweet main.
int main()
{
    print_rasse();

    // Create the database for the lines
    std::map<std::string, Line> lines_database;

    // Create a vector to store all the stops
    std::set<std::string> all_stop_names_set;

    // Get the name of the input file
    std::cout << "Give a name for input file: ";
    std::string file_name;
    getline(std::cin, file_name);

    if (not read_file(file_name, lines_database, all_stop_names_set)) {
        return EXIT_FAILURE;
    }

    // Create a vector that contains the

    // Execute the commands.
    while (true) {
        // Get the command of the user
        std::cout << "tramway> ";
        std::string command_line;
        getline(std::cin, command_line);
        std::vector<std::string> parts = split(command_line,' ');

        // Convert the command to uppercase characters
        std::string command = "";
        for (char c : parts.at(0)) {
            command += toupper(c);
        }

        // Command LINES print the names of the lines in alphabetical order
        if (command == "LINES") {
            std::cout << "All tramlines in alphabetical order:" << std::endl;
            // Print the name in alphabetical order
            for (auto line_pair : lines_database) {
                std::cout << line_pair.first << std::endl;
            }
        }

        // Command LINE <line> prints the stops of the specified line and their distance
        else if (command == "LINE") {
            std::vector<std::string> parameters_vector = process_quote(parts);
            // Check if the command provides sufficient parameters
            if (parameters_are_sufficient(parameters_vector, 1)) {
                std::string line_name = parameters_vector.at(0);
                // Check if the line exists
                if (line_is_valid(lines_database, line_name)) {
                    lines_database.at(line_name).print_all_stops();
                }
            }
        }

        // Command STOPS prints all the stops of the lines in ASCII order.
        else if (command == "STOPS") {
            std::cout << "All stops in alphabetical order:" << std::endl;
            // Loop through the set of stops to print the stop names.
            for (std::string stop_name : all_stop_names_set) {
                std::cout << stop_name << std::endl;
            }
        }

        // Command STOP <stop> search the lines that the has the given stop
        else if (command == "STOP") {
            // Create a vector to store the parameters of the command
            std::vector<std::string> parameters_vector = process_quote(parts);
            // Check if the command provides sufficient parameters
            if (parameters_are_sufficient(parameters_vector, 1)) {
                std::string stop_name = parameters_vector.at(0);
                // Check if the stop is valid
                if (stop_is_valid(all_stop_names_set, stop_name)) {
                    std::cout << "Stop " << stop_name << " can be found on the following lines:" << std::endl;
                    // Loop through the lines to check if that line has the given stop. If does.
                    // print the name of the line
                    for (auto line_pair : lines_database) {
                        if (line_pair.second.has_stop(stop_name)) {
                            std::cout << "- " << line_pair.first << std::endl;
                        }
                    }
                }
            }
        }

        // Command DISTANCE <line> <stop1> <stop2> calculates the distance of the given 2 stops
        // in the line
        else if (command == "DISTANCE") {
            // Create a vector for the parameters of the command
            std::vector<std::string> parameters_vector = process_quote(parts);
            // Check if the command provides sufficient parameters
            if (parameters_are_sufficient(parameters_vector, 3)) {
                std::string line_name = parameters_vector.at(0);
                std::string stop_1 = parameters_vector.at(1);
                std::string stop_2 = parameters_vector.at(2);
                // Check if the line is valid. If not, print the error message
                if (line_is_valid(lines_database, line_name)) {
                    // Check if the stops exist in the line. If not, print the error message.
                    // Else, calculate the distance
                    if (lines_database.at(line_name).has_stop(stop_1) and lines_database.at(line_name).has_stop(stop_2)) {
                        double result = lines_database.at(line_name).distance(stop_1,stop_2);
                        std::cout << "Distance between " << stop_1 <<
                                     " and " << stop_2 << " is " << result << std::endl;
                    } else {
                        std::cout << "Error: Stop could not be found." << std::endl;
                    }
                }
            } 
        }

        // Command ADDLINE <line> add a new line to the database (without stops)
        else if (command == "ADDLINE") {
            // Create a vector to store the parameters of the command
            std::vector<std::string> parameters_vector = process_quote(parts);
            // Check if the command provides sufficient parameters
            if (parameters_are_sufficient(parameters_vector, 1)) {
                std::string line_name = parameters_vector.at(0);
                // Check if the line already exists. If does, print the error
                // message. Else, create a new Line object and add it to the
                // database.
                if (line_or_stop_does_not_exists(lines_database, line_name)) {
                    Line new_line = Line(line_name);
                    lines_database.insert({line_name, new_line});
                    std::cout << "Line was added." << std::endl;
                }
            }
        }

        // Command ADDSTOP <line> <new_stop> <distance> adds a new stop and its
        // distance to the line.
        else if (command == "ADDSTOP") {
            // Create a vector to store the parameters of the command
            std::vector<std::string> parameters_vector = process_quote(parts);
            // Check if the command provides sufficient parameters
            if (parameters_are_sufficient(parameters_vector, 3)) {
                std::string line_name = parameters_vector.at(0);
                std::string stop_name = parameters_vector.at(1);
                double distance = stod(parameters_vector.at(2));
                // Check if the line is valid. If not, print the error message
                if (line_is_valid(lines_database, line_name)) {
                    // Check if the stop or distance already exists in the line. If does,
                    // print the error message
                    if (line_or_stop_does_not_exists(lines_database, line_name, stop_name, distance)) {
                        lines_database.at(line_name).add_stop(stop_name, distance);
                        all_stop_names_set.insert(stop_name);
                        std::cout << "Stop was added." << std::endl;
                    }
                }
            }
        }

        // Command REMOVE <stop> removes the given stop from all the lines
        else if (command == "REMOVE") {
            // Create a vector to store the parameters of the command
            std::vector<std::string> parameters_vector = process_quote(parts);
            // Check if the command provides sufficient parameters
            if (parameters_are_sufficient(parameters_vector, 1)) {
                std::string stop_name = parameters_vector.at(0);
                // Check if the stop is valid
                if (stop_is_valid(all_stop_names_set, stop_name)) {
                    // Loop through the lines and remove the stop
                    auto iter = lines_database.begin();
                    while (iter != lines_database.end()) {
                        iter->second.remove_stop(stop_name);
                        ++iter;
                    }
                    // Remove the stop from the set of stop names
                    all_stop_names_set.erase(stop_name);
                    std::cout << "Stop was removed from all lines." << std::endl;
                }
            }
        }

        // Command QUIT: Quit the program
        else if (command == "QUIT") {
            return EXIT_SUCCESS;
        }

        // Else, print the error message for the invalid command
        else {
            std::cout << "Error: Invalid input." << std::endl;
        }
    }
}
