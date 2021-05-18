/* The definition of the methods declared in the Header file
 *
 * Program author
 * Name: Minh Tran
 * Student number: 050359358
 * UserID: mmmitr
 * E-Mail: minh.s.tran@tuni.fi
 *
 * */


#include "line.hh"


// Constructor
Line::Line(const std::string name, std::map<std::string, double> stops):
    name_(name), stops_(stops){}


// Add a stop to the line
bool Line::add_stop(const std::string stop_name, const double distance) {
    // Check the validity of the stop
    // If the stop already exists, the addition of the stop fails
    if (stops_.find(stop_name) != stops_.end()) {
        return false;
    }
    // If the distance is duplicated, the adddition of the stop fails
    auto iter = stops_.begin();
    while (iter != stops_.end()) {
        if (iter->second == distance) {
            return false;
        }
        ++iter;
    }
    // Add the stop to the line
    stops_.insert({stop_name, distance});
    return true;
}


// Get the name of the line
std::string Line::get_name() {
    return name_;
}


// Print all the stops of the line in ascending order of the distance
void Line::print_all_stops() {
    std::cout << "Line " << get_name() << " goes through these stops in the order they are listed:" << std::endl;

    // Create a map that has the key as the value of the map of stops and vice versa.
    // The idea here is to invert the map so that we can sort it using the values of the
    // original map
    std::map<double, std::string> inverted_stops_map = {};

    //Add the pairs to the new map
    for (auto stop_pair : stops_) {
        inverted_stops_map.insert({stop_pair.second, stop_pair.first});
    }

    // Print the stops in ascending order of the distance
    for (auto stop_pair : inverted_stops_map) {
        std::cout << "- " << stop_pair.second << " : " << stop_pair.first << std::endl;
    }
}


// Check if the line has a particular stop
bool Line::has_stop(std::string stop_name) {
    if (stops_.find(stop_name) != stops_.end()) {
        return true;
    } else {
        return false;
    }
}


// Calculate the distance between 2 stops of the line, and print the
// message. The availability of the stops will be checked in the
// main function.
// Return the distance between the 2 stops (in positive value)
double Line::distance(std::string stop_1, std::string stop_2) {
    // Calculate the distance of the 2 stops
    double result = stops_.at(stop_1) - stops_.at(stop_2);
    // Return the absolute value of the result
    if (result < 0) {
        return -result;
    }
    return result;
}


// Check if the line has a stop with the given distance. Return true if that
// distance exists. False otherwise.
bool Line::has_distance(double distance) {
    for (auto stop_pair : stops_) {
        if (stop_pair.second == distance) {
            return true;
        }
    }
    return false;
}


// Remove a stop from the line
void Line::remove_stop(std::string stop_name) {
    stops_.erase(stop_name);
}

