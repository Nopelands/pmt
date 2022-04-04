#include "main.h"
#include <fstream>
#include <iostream>

void help() {
    printf("help message\n");
}

int main(const int argc, const char *argv[]) {

    bool count = false;
    int edit = 0, counter = 0;
    vector<const char*> TXTfiles;
    const char *patFile = NULL, *algorithm = "auto";

    for (int i = 1; i < argc; i++) {
        string flag(argv[i++]);

        if (flag == "-e" || flag == "--edit")
            edit = atoi(argv[i]);
        else if (flag == "-p" || flag == "--pattern")
            patFile = argv[i];
        else if (flag == "-a" || flag == "--algorithm")
            algorithm = argv[i];
        else if (flag == "-c" || flag == "--count")
            count = true, --i;
        else
            TXTfiles.push_back(argv[--i]);
    }

    if (TXTfiles.size() == 0 || !patFile)
        help();

    vector<string> patText;
    ifstream file(patFile);

    for (string s; getline(file, s);)
        if (s.size())
            patText.push_back(s);

    file.close();

    string funct = algorithm;

    if (funct == "aho-corasick") {
        buildAho(patText);

        for (auto f : TXTfiles) {
            int l = 0;
            ifstream file(f);

            for (string s; getline(file, s); l++) {
                unsigned occ = ahoCorasick(s);

                if (count)
                    counter += occ;
                else if (occ)
                    printf("%s\n", s.c_str());
            }

            file.close();
        }
    }
    else
        for (string pat : patText) {

            if (funct == "boyer-moore")
                buildBoyer(pat);
            else if (funct == "knuth-morris-pratt" || funct == "kmp")
                buildKMP(pat);
            else if (funct == "shift-or")
                buildShiftOr(pat);
            else if (funct == "ukkonen")
                buildUkkonen(pat, edit);
            else if (funct == "wu-mamber")
                buildWuMamber(pat);

            for (auto f : TXTfiles) {

                int l = 0;
                ifstream file(f);
                for (string s; getline(file, s); l++) {
                    unsigned occ;

                    if (funct == "boyer-moore")
                        occ = BoyerMoore(s, pat);
                    else if (funct == "knuth-morris-pratt" || funct == "kmp")
                        occ = KnuthMorrisPratt(s, pat);
                    else if (funct == "sellers")
                        occ = Sellers(s, pat, edit);
                    else if (funct == "shift-or")
                        occ = ShiftOr(s, pat);
                    else if (funct == "ukkonen")
                        occ = Ukkonen(s, pat, edit);
                    else if (funct == "wu-mamber")
                        occ = WuMamber(s, pat, edit);
                    else {
                        help();
                        return 1;
                    }

                    if (count)
                        counter += occ;
                    else if (occ)
                        printf("%s\n", s.c_str());
                }
                file.close();
            }
        }

    if (count)
        printf("%d\n", counter);

    return 0;
}
