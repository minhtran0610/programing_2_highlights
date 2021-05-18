#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


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

void print_network(std::map<std::string, std::vector<std::string>>& network_data, std::string& id, int increment = 0) {
    if (network_data.find(id) == network_data.end()) {
        for (int i = 0; i < 2*increment; i++) {
            std::cout << '.';
        }
        std::cout << id << std::endl;
    } else {
        for (int i = 0; i < 2*increment; i++) {
            std::cout << '.';
        }
        std::cout << id << std::endl;
        increment ++;
        for (std::string id2 : network_data.at(id)) {
            print_network(network_data, id2, increment);
        }
    }
}

void count_network(std::map<std::string, std::vector<std::string>>& network_data, std::string& id, int& result) {
    if (network_data.find(id) == network_data.end()) {
        result ++;
    } else {
        result ++;
        for (std::string id2 : network_data.at(id)) {
            count_network(network_data, id2, result);
        }
    }
}

void depth_network(std::map<std::string, std::vector<std::string>>& network_data, std::string& id, int& depth, int temp = 1) {
    if (network_data.find(id) == network_data.end()) {
        if (temp > depth) {
            depth = temp;
        }
    } else {
        temp ++;
        for (std::string id2 : network_data.at(id)) {
            depth_network(network_data, id2, depth, temp);
        }
    }
}

int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string, std::vector<std::string>> network_data;


    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            if (network_data.find(id1) != network_data.end()) {
                network_data.at(id1).push_back(id2);
            } else {
                network_data.insert({id1, {id2}});
            }

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print_network(network_data, id);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int result = -1;
            count_network(network_data, id, result);
            std::cout << result << std::endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int depth = 1;
            depth_network(network_data, id, depth);
            std::cout << depth << std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
