#include <iostream>
#include <string>
#include <map>
using namespace std;

string gen_keystream(string key, string msg) {
    string keystream;
    int non_alphabetic = 0;
    for(int i = 0; i < msg.size(); i++) {
        if((int)msg[i] >= (int)'A' &&  (int)msg[i] <= (int)'Z')
            keystream.push_back(key[(i-non_alphabetic) % key.size()]);
        else
            non_alphabetic++;
    }
    cout << "KEYSTREAM: ";
    cout << keystream << endl;
    return keystream;
}

string insert_key() {
    string key;
    cout << "Insert the key: ";
    cin >> key;
    return key;
}

string insert_message() {
    string message;
    cout << "Insert the message: ";
    cin.ignore();
    getline(cin, message);
    return message;
}

string get_decrypt() {
    string key = insert_key();
    string encrypted = insert_message();
    string keystream = gen_keystream(key, encrypted);
    string decrypted;

    int non_alphabetic = 0;
    for(int i = 0; i < encrypted.size(); i++) {
        if((int)encrypted[i] >= (int)'A' &&  (int)encrypted[i] <= (int)'Z') {
            char c_new = (char)(((int) ((encrypted[i] - 'A')-(keystream[i-non_alphabetic] - 'A')+26)) % 26 + 'A');
            decrypted.push_back(c_new);
        }else {
            decrypted.push_back(encrypted[i]);
            non_alphabetic++;
        }
    }
    cout << decrypted << endl;

    return key;
}

string get_encrypt() {
    string key = insert_key();
    string original = insert_message();
    string keystream = gen_keystream(key, original);
    string encrypted;

    int non_alphabetic = 0;
    for(int i = 0; i < original.size(); i++) {
        if((int)original[i] >= (int)'A' &&  (int)original[i] <= (int)'Z') {
            char c_new = (char)(((int) ((original[i] - 'A')+(keystream[i-non_alphabetic] - 'A'))) % 26 + 'A' );
            encrypted.push_back(c_new);
        }else {
            encrypted.push_back(original[i]);
            non_alphabetic++;
        }
    }
    cout << encrypted << endl;

    return key;
}

int main() {
    int opt = 0;
    printf("Vigenere Chyper\n1. Encryptor\n2. Decryptor\n");
    do {
        printf("Choose an option: ");
        cin >> opt;
        switch(opt){
            case 1:
                get_encrypt();
                break;
            case 2:
                get_decrypt();
                break;
            default:
                printf("Invalid option!\n");
                break;
        }
    } while(opt < 1 || opt > 2);
    return 0;
}