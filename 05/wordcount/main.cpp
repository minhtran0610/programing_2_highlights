#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

// Split the strings with the given separator
std::vector<std::string> split(std::string line, char separator, bool no_empty = false) {
    std::vector<std::string> parts;
    std::string::size_type previous_separator_index = -1;
    std::string::size_type current_separator_index = -1;

    for (std::string::size_type i = 0; i < line.length(); i++) {
        if (line.at(i) == separator) {
            previous_separator_index = current_separator_index;
            current_separator_index = i;
            std::string::size_type part_length = current_separator_index - previous_separator_index - 1;
            if (no_empty) {
                if (line.substr(previous_separator_index+1, part_length) != "") {
                    parts.push_back(line.substr(previous_separator_index+1, part_length));
                }
            } else {
                parts.push_back(line.substr(previous_separator_index+1, part_length));
            }
        }
    }
    parts.push_back(line.substr(current_separator_index+1, line.length()-current_separator_index-1));

    return parts;
}

int main()
{
    // Opening the file
    cout << "Input file: ";
    string file_name;
    cin >> file_name;
    ifstream file_object(file_name);

    // Read the file and store the lines of the file
    vector<string> lines = {};
    if (not file_object) {
        cout << "Error! The file " << file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string line;
        while(getline(file_object,line)) {
            lines.push_back(line);

            if (file_object.eof()) {
                break;
            }
        }
    }
    file_object.close();

    // Count the words
    map<string, vector<unsigned long int>> word_counts;

    for (unsigned long int i = 0; i < lines.size(); i++) {
        string line = lines.at(i);

        vector<string> words_in_line = split(line, ' ');
        set<string> set_words_in_line;

        for (string word : words_in_line) {
            set_words_in_line.insert(word);
        }

        for (auto word : set_words_in_line) {
            if (word_counts.find(word) != word_counts.end()) {
                word_counts.at(word).at(0) += 1;
                word_counts.at(word).push_back(i+1);
            } else {
                word_counts.insert({word, {1, i+1}});
            }
        }
    }

    // Print the result
    map<string, vector<unsigned long int>>::iterator iter = word_counts.begin();
    while (iter != word_counts.end()) {
        cout << iter->first << " " << iter->second.at(0) << ": ";
        if (iter->second.size() == 2) {
            cout << iter->second.at(1) << endl;
        } else {
            for (unsigned long int i = 1; i<iter->second.size()-1; i++) {
                cout << iter->second.at(i) << ", ";
            }
            cout << iter->second.back() << endl;
        }
        ++iter;
    }
    return EXIT_SUCCESS;
}
