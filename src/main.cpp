#include "main.h"
#include <chrono>
#include <fstream>
#include <iostream>

long long getTime() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

void help() {

}

int main(const int argc, const char *argv[]) {

    bool count = false;
    int edit = 0, counter = 0;
    vector<const char*> TXTfiles;
    const char *patFile = NULL, *algorithm = "auto";
    long long ms_ini = getTime();

    for (int i = 1; i < argc; i++) {
        string flag(argv[i++]);

        if (flag == "-e" || flag == "--edit")
            edit = atoi(argv[i]);
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
                vector<Occurance> occ = ahoCorasick(s, patText);

                if (count)
                    counter += occ.size();
                else
                    for (auto c : occ)
                        printf("Palavra %s encontrada no index %d da linha %d no arquivo %s\n", patText[c.pat_index].c_str(), c.index, l, f);
            }

            file.close();
        }
    }
    else
        for (string pat : patText) {

            if (funct == "knuth-morris-pratt" || funct == "kmp")
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
                    vector<Occurance> occ;

                    if (s.size() < pat.size())
                        continue;

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
                        counter += occ.size();
                    else
                        for (auto c : occ)
                            printf("Palavra %s encontrada no index %d da linha %d no arquivo %s\n", pat.c_str(), c.index, l, f);
                }
                file.close();
            }
        }

    if (count)
        printf("Ao total foram encontrados %d padroes\n", counter);

    printf("Codigo executado em %lldms\n", getTime() - ms_ini);

    return 0;
}
