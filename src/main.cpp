#include "main.h"
#include <fstream>

void help() {

printf("\
Usage: pmt [options] pattern textfile [textfile...]\n\
Search for pattern in each textfile.\n\
Example: pmt 'test' text.txt\n\
\n\
Pattern selection and interpretation:\n\
  -a, --algorithm       force usage of selected algorithm. Option:\n\
                            auto (it chooses the best fit algorithm to seach)\n\
                            ac,  aho-corasick\n\
                            bm,  boyer-moore\n\
                            kmp, knuth-morris-pratt\n\
                            sl,  sellers\n\
                            so,  shift-or  (limited the size of pattern up to %d char)\n\
                            uk,  ukkonen\n\
                            wm,  wu-manber (limited the size of pattern up to %d char)\n\
  -e, --edit            set maximum error for approximated search (must be used with sl, uk and wm)\n\
  -p, --pattern         use pattern file instead of pattern string\n\
\n\
Miscellaneous:\n\
  -h, --help            display this help text and exit\n\
\n\
Output control:\n\
  -c, --count           print only a count of pattern occurrences\n\
\n\
Report bugs to: /dev/null\n\
pmt home page: https://github.com/Nopelands/pmt\n", maxBinarySize, maxBinarySize);

}

void usage() {
    printf("Usage: pmt [options] pattern textfile [textfile...]\nTry 'pmt --help' for more information.\n");
}

void alg_warning() {
    printf("Unknown algorithm\nTry 'pmt --help' for more information.\n");
}

void edit_warning() {
    printf("Missing --edit flag or its value is negative\nTry 'pmt --help' for more information.\n");
}

void size_warning(const string &pat) {
    printf("Pattern %s is ignored due to its size.\nPlease, keep pattern size less than %d characters.\n", pat.c_str(), maxBinarySize + 1);
}

string select_alg(const string &pat, int edit) {
    if (edit > 0) {
        if (pat.size() > 128)
            return "sl";
        else if (pat.size() > 12)
            return "wm";
        else
            return "uk";
    } else {
        if (pat.size() > 6)
            return "bm";
        else
            return "so";
    }
}

int main(const int argc, const char *argv[]) {

    bool count = false;
    int edit = -1, counter = 0;
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
    string funct = algorithm;
    string alg = funct;

    if (TXTfiles.size() <= 0 + !patFile) {
        usage();
        return 1;
    }

    if (edit < 0 && (    funct == "uk"     || funct == "sl"      || funct == "wm"
                      || funct == "ukkonen"|| funct == "sellers" || funct == "wu-manber")) {
        edit_warning();
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

    if ( funct == "aho-corasick" || funct == "ac"
    ||  (funct == "auto" && edit <= 0 && patText.size() > 1)) {
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

            if (alg == "auto")
                funct = select_alg(pat, edit);

            if (funct == "boyer-moore" || funct == "bm")
                buildBoyer(pat);
            else if (funct == "knuth-morris-pratt" || funct == "kmp")
                buildKMP(pat);
            else if (funct == "shift-or" || funct == "so") {
                if (pat.size() > maxBinarySize) {
                    size_warning(pat);
                    continue;
                }

                buildShiftOr(pat);
            }
            else if (funct == "ukkonen" || funct == "uk")
                buildUkkonen(pat, edit);
            else if (funct == "wu-manber" || funct == "wm") {
                if (pat.size() > maxBinarySize) {
                    size_warning(pat);
                    continue;
                }

                buildWuManber(pat);
            }

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
                        alg_warning();
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
