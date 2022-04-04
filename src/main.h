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

extern unsigned ahoCorasick(const string &txt);
extern unsigned BoyerMoore(const string &txt, const string &pat);
extern unsigned KnuthMorrisPratt(const string &txt, const string &pat);
extern unsigned ShiftOr(const string &txt, const string &pat);

// busca aproximada
extern void buildWuManber(const string& pat);
extern void buildUkkonen(const string& pat, const unsigned r);

extern unsigned Sellers(const string &txt, const string &pat, const unsigned r);
extern unsigned Ukkonen(const string &txt, const string &pat);
extern unsigned WuManber(const string &txt, const string &pat, const unsigned r);

#endif
