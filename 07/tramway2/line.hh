/* Class: Line
 *
 * Represent a tram line in the program
 *  The object stores the information related to a single line in its
 * attributes:
 *  -   stops_: A map has the keys as the stop names and the values as their
 *      corresponding distance.
 *  -   name_: A string that is the name of the line
 *  The object is also able to deal with the data inside their
 * attributes with the public methods.
 * 
 * Program author
 * Name: Minh Tran
 * Student number: 050359358
 * UserID: mmmitr
 * E-Mail: minh.s.tran@tuni.fi
 *
 * */


#ifndef LINE_HH
#define LINE_HH

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

class Line
{
public:
    // Constructor
    Line(std::string name, std::map<std::string, double> stops = {});
    
    // Add the stops to the line
    bool add_stop(const std::string stop_name, const double distance);
    
    // Get the name of the line
    std::string get_name();

    // Print all the stops (command LINE)
    void print_all_stops();

    // Check if the line has a particular stop
    bool has_stop(std::string stop_name);

    // Calculate the distance between 2 stops of the line
    double distance(std::string stop_1, std::string stop_2);

    // Check if the line has a stop with a given distance
    bool has_distance(double distance);

    // Remove a stop from the line
    void remove_stop(std::string stop_name);

private:
    const std::string name_;
    std::map<std::string, double> stops_;
};

#endif // LINE_HH
