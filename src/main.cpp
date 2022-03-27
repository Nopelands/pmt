#include "main.h"
#include <vector>
#include <fstream>
#include <iostream>

void help() {

}

int main(const int argc, const char *argv[]) {

    double edit = -1;
    bool count = false;
    vector<const char*> TXTfiles;
    const char *patFile = NULL, *algorithm = "auto";

    for (int i = 1; i < argc; i++) {
        string flag(argv[i++]);

        if (flag == "-e" || flag == "--edit")
            edit = atof(argv[i]);
        else if (flag == "-p" || flag == "--pattern")
            patFile = argv[i];
        else if (flag == "-a" || flag == "--algorithm")
            algorithm = argv[i];
        else if (flag == "-c" || flag == "--count")
            count = true;
        else
            TXTfiles.push_back(argv[--i]);
    }

    if (TXTfiles.size() == 0 || !patFile)
        help();

    vector<string> patText;
    ifstream file(patFile);

    for (string s; getline(file, s);)
        patText.push_back(s);

    file.close();

    for (auto f : TXTfiles) {
        ifstream file(f);
        string txtText(string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>())));
        file.close();

        cout << txtText << endl;

        if ((string)algorithm == "auto")
            for (auto pat : patText)
                cout << ShiftOr(txtText, pat) << endl;
    }    

    return 0;
}