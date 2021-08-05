#ifndef FILE_H_
#define FILE_H_
#include <fstream>
using namespace std;

    std::vector<double> load_freq(std::string filename) {
        vector<double> v(26);
        fill(v.begin(), v.end(), 0);
        std::ifstream file;
        file.open(filename);
        std::string str;
        int n = 0;
        while (std::getline(file, str)) {
            v[n] = stod(str);
            n++;
        }
        return v;
    }

    string read_input() {
        std::ifstream file;
        file.open("test.in");
        std::string str;
        string s;
        while (std::getline(file, str)) {
            s.append(str);
        }

        remove(s.begin(), s.end(), ' ');
        s.erase(remove_if(s.begin(), s.end(), [](char c) { return !isalpha(c); } ), s.end());
        transform(s.begin(), s.end(),s.begin(), ::toupper);
        cout << s << endl;

        return s;
    }

#endif