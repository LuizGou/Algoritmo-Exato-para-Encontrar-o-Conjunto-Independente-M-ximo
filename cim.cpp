#include <bits/stdc++.h>
#include <fstream>

using namespace std;

typedef vector<vector<int>> Lista;

int n;
Lista G;
vector<int> melhor;

bool podeAdicionar(int v, vector<int>& atual) {
    for (int u : atual) {
        for (int viz : G[v]) {
            if (viz == u) return false;
        }
    }
    return true;
}

void backtrack(int v, vector<int>& atual) {
    if (v == n) {
        if (atual.size() > melhor.size()) {
            melhor = atual;
        }
        return;
    }

    if (podeAdicionar(v, atual)) {
        atual.push_back(v);
        backtrack(v + 1, atual);
        atual.pop_back();
    }

    backtrack(v + 1, atual);
}

void leituraGrafo(Lista &G, int m) {
    int a, b;
    while (m--) {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
}

void escritaGrafo(Lista &G) {
    int n = G.size();
    cout << "Lista de Adjacencia:\n";
    for (int u = 0; u < n; u++) {
        cout << u << ": ";
        for (auto v : G[u]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
    ifstream arquivo("grafo.txt");

    if (!arquivo) {
        cout << "Nao deu certo abrir" << endl;
        return 1;
    }

    int m;
    arquivo >> n >> m;

    G.assign(n, vector<int>());

    int a, b;
    while (m--) {
        arquivo >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    arquivo.close();

    escritaGrafo(G);

    vector<int> atual;
    backtrack(0, atual);

    cout << "\nConjunto Independente Maximo:\n";
    for (int v : melhor) {
        cout << v << " ";
    }

    cout << "\nTamanho: " << melhor.size() << endl;

    return 0;
}