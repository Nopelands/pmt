#include "main.h"
#include <queue>
#include <set>

unsigned f[AB_SIZE];
vector<unsigned> out;
vector<vector<int>> g;

void buildAho(const vector<string> &pats) {

    out.assign(1, 0);
    vector<set<unsigned>> aux(1);
    g.assign(1, vector<int>(AB_SIZE, -1));
    memset(f, -1, AB_SIZE * sizeof(f[0]));

    unsigned states = 1;
    for (unsigned i = 0; i < pats.size(); ++i) {
        int currentState = 0;

        for (char c : pats[i]){
            if (g[currentState][(uint8_t)c] == -1) {

                aux.push_back(set<unsigned>());
                g.push_back(vector<int>(AB_SIZE, -1));

                g[currentState][(uint8_t)c] = states++;
            }
            
            currentState = g[currentState][(uint8_t)c];
        }

        aux[currentState].insert(i);
    }

    queue<int> q;

    for (int i = 0; i < AB_SIZE; ++i)
        if (g[0][i] != 0) {
            if (g[0][i] == -1) {
                g[0][i] = 0;
                continue;
            }

            f[g[0][i]] = 0;
            q.push(g[0][i]);
        }

    while (!q.empty()) {
        int state = q.front(); q.pop();

        for (int i = 0; i < AB_SIZE; ++i)
            if (g[state][i] != -1) {
                int failure = f[state];

                while (g[failure][i] == -1)
                    failure = f[failure];
                
                f[g[state][i]] = failure = g[failure][i];
                aux[g[state][i]].insert(aux[failure].begin(), aux[failure].end());

                q.push(g[state][i]);
            }
    }

    out.resize(states);
    for (unsigned i = 0; i < states; ++i)
        out[i] = aux[i].size();
}

inline unsigned findNextState(unsigned currentState, char nextInput) {

    while (g[currentState][(uint8_t)nextInput] == -1)
        currentState = f[currentState];

    return g[currentState][(uint8_t)nextInput];
}

unsigned ahoCorasick(const string &txt) {

    unsigned occ = 0;
    const unsigned txtSize = txt.size();

    for (unsigned i = 0, currentState = 0; i < txtSize; ++i) {
        currentState = findNextState(currentState, txt[i]);

        if (out[currentState]) [[unlikely]]
            occ += out[currentState];
    }

    return occ;
}
