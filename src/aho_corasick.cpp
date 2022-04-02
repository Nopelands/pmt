#include "main.h"
#include <queue>

vector<BitInt> out;
unsigned f[AB_SIZE];
vector<vector<int>> g;

void buildAho(const vector<string> &pats) {

    memset(f, -1, AB_SIZE * sizeof(f[0]));
    g.assign(1, vector<int>(AB_SIZE, -1));
    out.assign(1, 0ULL);

    int states = 1;

    for (unsigned i = 0; i < pats.size(); ++i) {
        int currentState = 0;

        for (char c : pats[i]){
            if (g[currentState][(uint8_t)c] == -1) {

                g.push_back(vector<int>(AB_SIZE, -1));
                out.push_back(0ULL);

                g[currentState][(uint8_t)c] = states++;
            }
            
            currentState = g[currentState][(uint8_t)c];
        }

        out[currentState] |= (1 << i);
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

                out[g[state][i]] |= out[failure];

                q.push(g[state][i]);
            }
    }
}

inline unsigned findNextState(unsigned currentState, char nextInput) {

    while (g[currentState][(uint8_t)nextInput] == -1)
        currentState = f[currentState];

    return g[currentState][(uint8_t)nextInput];
}

vector<Occurance> ahoCorasick(const string &txt, const vector<string> &pats) {

    vector<Occurance> occ;
    const unsigned txtSize = txt.size();
    const unsigned patsSize = pats.size();

    for (unsigned i = 0, currentState = 0; i < txtSize; ++i) {
        currentState = findNextState(currentState, txt[i]);

        if (!out[currentState])
            continue;

        for (unsigned j = 0; j < patsSize; ++j)
            if (out[currentState] & (1 << j))
                occ.push_back({i, j});
    }

    return occ;
}
