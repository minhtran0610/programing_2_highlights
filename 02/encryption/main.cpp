#include <iostream>

using namespace std;
#include <string>
#include <cctype>

int main()
{
    // input for the string
    cout << "Enter the encryption key: ";
    string enc_key = "";
    cin >> enc_key;

    // check if the input is valid

    // check if the key contains 26 characters
    if (enc_key.length() !=  26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return 1;
    }

    // check if the key contains lower-case English characters
    for (char c : enc_key) {
        if (isupper(c)) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return 1;
        } else if (not isalpha(c)) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return 1;
        }
    }

    // check if the key contains ALL characters
    char temp = 1;
    for (char c : enc_key) {
        if (c == temp) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return 1;
        } else {
            temp = c;
        }
    }

    // getting the text to be encrypted from the user
    cout << "Enter the text to be encrypted: ";
    string text_to_be_encrypted = "";
    cin >> text_to_be_encrypted;

    // encrypt the text
    string encrypted_text = "";
    for (char c : text_to_be_encrypted) {
        encrypted_text += enc_key.at(c-97);
    }

    // print the encrypted key
    cout << "Encrypted text: " << encrypted_text << endl;
    return 0;
}
