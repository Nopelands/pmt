#include "main.h"
#include <queue>
#include <unordered_map>

vector<bool> finalState;
vector<unsigned> seeds;
vector<vector<unsigned>> delta;

struct myHash {
    size_t operator()(const vector<unsigned> &v) const {
        size_t ans = 0;

        for (unsigned i = 0; i < v.size(); ++i)
            ans ^= v[i] * seeds[i];

        return ans;
    }
};

vector<unsigned> next_col(const vector<unsigned> &col, const string& pat, char c) {
    const unsigned patSize = pat.size();
    vector<unsigned> next(patSize + 1, 0);

    for (unsigned i = 1; i <= patSize; ++i)
        next[i] = min(col[i] + 1, min(next[i - 1] + 1, col[i - 1] + (c != pat[i - 1])));

    return next;
}

void buildUkkonen(const string& pat, const unsigned r) {
    const unsigned patSize = pat.size();

    seeds.assign(patSize + 1, 0);
    delta.assign(1, vector<unsigned>(AB_SIZE));
    finalState.assign(1, patSize <= r);

    unsigned total_states = 1, next_index;
    unordered_map<vector<unsigned>, unsigned, myHash> allStates;
    vector<vector<unsigned>> States(1, vector<unsigned>(patSize + 1));

    for (unsigned i = 0, seed = 128486587ULL; i <= patSize; ++i) {
        seeds[i] = seed;
        seed ^= seed >> 6, seed ^= seed << 12, seed ^= seed >> 13;
    }

    for (unsigned i = 0; i <= patSize; ++i)
        States[0][i] = i;
    
    queue<pair<vector<unsigned>, unsigned>> q;
    q.push({States[0], 0});

    while (q.size()) {
        auto cur_col   = q.front().first;
        auto cur_index = q.front().second;
        q.pop();
        
        for (unsigned c = 0; c < AB_SIZE; ++c) {
            auto next = next_col(cur_col, pat, c);

            if (allStates.find(next) != allStates.end())
                next_index = allStates[next];
            else {
                q.push({next, next_index = total_states++});
                allStates[next] = next_index;
                finalState.push_back(next[patSize] <= r);
                delta.push_back(vector<unsigned>(AB_SIZE));
            }

            delta[cur_index][c] = next_index;
        }
    }
}

template<bool count>
unsigned Ukkonen(const string &txt) {

    unsigned occ = 0;
    unsigned curState = 0;

    for (uint8_t c : txt) {
        curState = delta[curState][c];

        if (finalState[curState]) [[unlikely]] {
            if constexpr (!count)
                return 1;

            occ++;
        }
    }

    return occ;
}

unsigned Ukkonen(bool count, const string &txt) {
    return count ? Ukkonen< true>(txt)
                 : Ukkonen<false>(txt);
}
