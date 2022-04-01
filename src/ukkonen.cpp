#include "main.h"
#include <map>

vector<bool> finalState;
vector<vector<unsigned>> delta;

vector<unsigned> next_col(const string& pat, vector<unsigned> &col, char c) {
    const unsigned patSize = pat.size();
    vector<unsigned> next(patSize + 1, 0);

    for (unsigned i = 1; i <= patSize; ++i)
        next[i] = min(col[i] + 1, min(next[i - 1] + 1, col[i - 1] + (c != pat[i - 1])));

    return next;
}

void buildUK(const string& pat, const unsigned r) {
    const unsigned patSize = pat.size();

    delta.assign(1, vector<unsigned>(AB_SIZE));
    finalState.assign(1, patSize <= r);

    unsigned total_states = 1, next_index;
    map<vector<unsigned>, unsigned> allStates;
    vector<vector<unsigned>> States(1, vector<unsigned>(patSize + 1));

    for (unsigned i = 0; i <= patSize; ++i)
        States[0][i] = i;
    
    vector<pair<vector<unsigned>, unsigned>> q(1, {States[0], 0});

    while (q.size()) {
        auto cur_col   = q.back().first;
        auto cur_index = q.back().second;
        q.pop_back();
        
        for (unsigned c = 0; c < AB_SIZE; ++c) {
            auto next = next_col(pat, cur_col, c);

            if (allStates.find(next) != allStates.end())
                next_index = allStates[next];
            else {
                q.push_back({next, next_index = total_states++});
                finalState.push_back(next[patSize] <= r);
                allStates[next] = next_index;
                delta.push_back(vector<unsigned>(AB_SIZE));
            }

            delta[cur_index][c] = next_index;
        }
    }
}

vector<Occurance> Ukkonen(const string &txt, const string &pat, const unsigned r) {

    vector<Occurance> occ;
    unsigned curState = 0;
    const unsigned txtSize = txt.size();

    for (unsigned i = 0; i < txtSize; ++i) {
        curState = delta[curState][txt[i]];

        if (finalState[curState])
            occ.push_back({i, 0});
    }

    return occ;
}
