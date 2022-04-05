#include "main.h"
#include <set>

unsigned f[AB_SIZE];
vector<unsigned> out;
vector<vector<int>> g;

void buildAho(const vector<string> &pats) {

    out.assign(1, 0);
    vector<set<unsigned>> aux(1);
    g.assign(1, vector<int>(AB_SIZE, -1));
    memset(f, -1, AB_SIZE * sizeof(f[0]));

    for (unsigned i = 0, states = 1; i < pats.size(); ++i) {
        int currentState = 0;

        for (uint8_t c : pats[i]){
            if (g[currentState][c] == -1) {

                aux.push_back(set<unsigned>());
                g.push_back(vector<int>(AB_SIZE, -1));

                g[currentState][c] = states++;
            }
            
            currentState = g[currentState][c];
        }

        aux[currentState].insert(i);
    }

    vector<int> q;

    for (auto &s : g[0])
        if (s != 0) {
            if (s == -1) {
                s = 0;
                continue;
            }

            f[s] = 0;
            q.push_back(s);
        }

    while (!q.empty()) {
        int state = q.back(); q.pop_back();

        for (int i = 0; i < AB_SIZE; ++i)
            if (g[state][i] != -1) {
                int failure = f[state];

                while (g[failure][i] == -1)
                    failure = f[failure];
                
                f[g[state][i]] = failure = g[failure][i];
                aux[g[state][i]].insert(aux[failure].begin(), aux[failure].end());

                q.push_back(g[state][i]);
            }
    }

    out.resize(aux.size());
    for (unsigned i = 0; i < aux.size(); ++i)
        out[i] = aux[i].size();
}

inline unsigned findNextState(unsigned currentState, char nextInput) {

    while (g[currentState][(uint8_t)nextInput] == -1)
        currentState = f[currentState];

    return g[currentState][(uint8_t)nextInput];
}

template<bool count>
unsigned ahoCorasick(const string &txt) {

    unsigned occ = 0, currentState = 0;

    for (uint8_t c : txt) {
        currentState = findNextState(currentState, c);

        if (out[currentState]) [[unlikely]] {
            if constexpr (!count)
                return 1;

            occ += out[currentState];
        }
    }

    return occ;
}

unsigned ahoCorasick(bool count, const string &txt) {
    return count ? ahoCorasick< true>(txt)
                 : ahoCorasick<false>(txt);
}
