#include "main.h"
#include <fstream>

void help() {
    ifstream file("../doc/help.txt");
    for (string s; getline(file, s);)
        printf("%s\n", s.c_str());
    file.close();
}

void usage() {
    printf("Usage: pmt [options] pattern textfile [textfile...]\nTry 'pmt --help' for more information.\n");
}

string select_alg(const vector <string> &patVector) {
    if (patVector.size() > 1)
        return "ac";
    else if (patVector[0].size() <= 8)
        return "so";
    else
        return "bm";
}

int main(const int argc, const char *argv[]) {

    bool count = false;
    int edit = 0, counter = 0;
    vector<const char*> TXTfiles;
    const char *patFile = NULL, *algorithm = "auto";
    vector<string> patText;

    for (int i = 1; i < argc; i++) {
        string flag(argv[i]);

        if (flag == "-e" || flag == "--edit")
            edit = atoi(argv[++i]);
        else if (flag == "-p" || flag == "--pattern")
            patFile = argv[++i];
        else if (flag == "-a" || flag == "--algorithm")
            algorithm = argv[++i];
        else if (flag == "-c" || flag == "--count")
            count = true;
        else if (flag == "-h" || flag == "--help") {
            help();
            return 0;
        }
        else
            TXTfiles.push_back(argv[i]);
    }

    if (TXTfiles.size() <= 0 + !patFile) {
        usage();
        return 1;
    }

    if (patFile) {
        ifstream file(patFile);

        for (string s; getline(file, s);)
            if (s.size())
                patText.push_back(s);

        file.close();
    } else {
        patText.push_back(TXTfiles[0]);
        TXTfiles.assign(TXTfiles.begin() + 1, TXTfiles.end());
    }


    string funct = algorithm;

    if (funct == "auto")
        funct = select_alg(patText);

    if (funct == "aho-corasick" || funct == "ac") {
        buildAho(patText);

        for (auto f : TXTfiles) {
            int l = 0;
            ifstream file(f);

            for (string s; getline(file, s); l++) {
                unsigned occ = ahoCorasick(count, s);

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

            if (funct == "boyer-moore" || funct == "bm")
                buildBoyer(pat);
            else if (funct == "knuth-morris-pratt" || funct == "kmp")
                buildKMP(pat);
            else if (funct == "shift-or" || funct == "so")
                buildShiftOr(pat);
            else if (funct == "ukkonen" || funct == "uk")
                buildUkkonen(pat, edit);
            else if (funct == "wu-manber" || funct == "wm")
                buildWuManber(pat);

            for (auto f : TXTfiles) {

                ifstream file(f);
                for (string s; getline(file, s);) {
                    unsigned occ;

                    if (funct == "boyer-moore" || funct == "bm")
                        occ = BoyerMoore(count, s, pat);
                    else if (funct == "knuth-morris-pratt" || funct == "kmp")
                        occ = KnuthMorrisPratt(count, s, pat);
                    else if (funct == "sellers" || funct == "sl")
                        occ = Sellers(count, s, pat, edit);
                    else if (funct == "shift-or" || funct == "so")
                        occ = ShiftOr(count, s, pat);
                    else if (funct == "ukkonen" || funct == "uk")
                        occ = Ukkonen(count, s);
                    else if (funct == "wu-manber" || funct == "wm")
                        occ = WuManber(count, s, pat, edit);
                    else {
                        usage();
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
