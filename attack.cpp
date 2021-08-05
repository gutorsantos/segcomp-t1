#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <vector>
#include<numeric>
#include <algorithm>
#include "file.h"
#define MAX_KEYSIZE 20

using namespace std;

vector<double> frequencies(26);

void freq_analysis(string msg, int key) {
    string t;
    for(int k = 0; k < key; k++) {
        vector<double> alpha_freq(26);
        fill(alpha_freq.begin(), alpha_freq.end(), 0.0);
        
        for(int i = k; i <= msg.size()-(msg.size()%key)-1; i += key) {
            alpha_freq[(int)msg[i]-'A']++;
        }
        cout << "------------" << "Letra " << k+1 << "------------" << endl;
        int total = accumulate(alpha_freq.begin(),alpha_freq.end(),0);
        for(int i = 0; i < 26; i++) {
            alpha_freq[i] = (alpha_freq[i]/total)* 100;
            cout << alpha_freq[i] << " ";
        }
        cout << endl;
        int n_th = 1;
        int max = distance(alpha_freq.begin(), max_element(alpha_freq.begin(), alpha_freq.end()));
        if(alpha_freq[((max-4)%26+26)%26] >= 7) {
            printf("entrei\n");
        }else {
            do {
                vector<double> ord(alpha_freq);
                sort(ord.begin(), ord.end(), greater<int>());
                max = distance(alpha_freq.begin(), find(alpha_freq.begin(), alpha_freq.end(), ord[n_th]));
                printf("entrei 2\n");
                n_th++;
            }while(alpha_freq[((max-4)%26+26)%26] < 7);
        }

        int find_shift = (max - (int)('E'-'A'));
        int shift = (find_shift%26+26)%26;
        t.push_back(((char)((shift)+'A')));
    }
    cout << t << endl;
}

int group_analysis(string msg) {
    int GROUP = 3;
    vector<vector<string>> v;
    int r = 0;
    for(int i = 0; i < msg.size()-(msg.size()%GROUP); i+=GROUP) {
        string t = msg.substr(i, GROUP);
        for(int j = i+GROUP; j < msg.size()-GROUP; j++) {
            if(!t.compare(msg.substr(j, GROUP))) {
                vector<string> row;
                row.push_back(t);
                row.push_back(to_string(j-i));
                v.push_back(row);
                break;
            }else {

            }
        }
    }
    string array[v.size()][MAX_KEYSIZE+1];

    for(int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            array[i][j] = v[i][j];
            for(int k = 2; k < MAX_KEYSIZE+1; k++) {
                if(stoi(v[i][1])%k == 0) {
                    array[i][k] = "X";
                }
                else
                    array[i][k] = "-";
            }
        }
    }

    int min = -10^9;
    int greater = 1;
    int snd = 1;
    for (int i = 2; i < MAX_KEYSIZE+1; i++) {
        int repeat = 0;
        for (int j = 0; j < v.size(); j++) {
            if(!array[j][i].compare("X"))
                repeat++;
        }
        if(repeat > min) {
            snd = greater;
            greater = i;
            min = repeat;
        }

    }

    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < MAX_KEYSIZE+1; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << greater << " " << min << " " << snd << endl;
    cout << "Probably your key is " << greater << " characteres length" << endl;
    return greater;
}

int main() {
    string message;
    int opt = 0;

    printf("Vigenere Chyper Breaker\n");
    do {
        printf("Is the text in Portuguese(1) or English(2)?\n");
        cin >> opt;
        switch(opt){
            case 1:
                frequencies = load_freq("freq_pt.txt");
                break;
            case 2:
                frequencies = load_freq("freq_en.txt");
                break;
            default:
                printf("Invalid option!\n");
                break;
        }
    } while(opt < 1 || opt > 2);
    message = read_input();
    
    int key = group_analysis(message);
    freq_analysis(message, key);
    return 0;
}