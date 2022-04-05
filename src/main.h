#ifndef MAIN_H
#define MAIN_H

#include <bitset>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define AB_SIZE 256

// busca exata
extern void buildBoyer(const string &pat);
extern void buildKMP(const string &pat);
extern void buildShiftOr(const string &pat);
extern void buildAho(const vector<string> &pats);

extern unsigned ahoCorasick(bool count, const string &txt);
extern unsigned BoyerMoore(bool count, const string &txt, const string &pat);
extern unsigned KnuthMorrisPratt(bool count, const string &txt, const string &pat);
extern unsigned ShiftOr(bool count, const string &txt, const string &pat);

// busca aproximada
extern void buildWuManber(const string& pat);
extern void buildUkkonen(const string& pat, const unsigned r);

extern unsigned Sellers(bool count, const string &txt, const string &pat, const unsigned r);
extern unsigned Ukkonen(bool count, const string &txt);
extern unsigned WuManber(bool count, const string &txt, const string &pat, const unsigned r);

#endif
