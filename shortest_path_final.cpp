#include <bits/stdc++.h>
#include <climits>
using namespace std;

const int MAXN = 2005;
const long long INF = LLONG_MAX;

struct Edge {
    int from;
    int to;
    long long weight;

    Edge() {}
    Edge(int from, int to, long long weight){
        this->from = from;
        this-> to = to;
        this->weight = weight;
    }
};


//Vrača !(postoji li negativni ciklus) i mjenja potencijal h.
bool bellmanFord(int V, int source,  vector<Edge> &edges, vector<long long> &h) {
    h[source] = 0;

    for (int i = 0; i < V; ++i) {
        bool updated = false;

        for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
                // Ako je h[v] < h[u] + w
                // Onda h[v] = h[u] + w
            if (h[it->from] < INF && h[it->from] + it->weight < h[it->to]) {
                h[it->to] = h[it->from] + it->weight;
                updated = true;
            }
        }
        
        if (!updated) return true;
    }
    //V puta se promjenila vrijednost -> Postoji negativni ciklus 
    return false; 
}

vector<long long> dijkstra(int n, int source, vector<Edge> &edges, const vector<long long> &h) {
    
    // Izgradnja grafa s reweightanim bridovima
    // Bellman-Ford osigurava nenegativnost težina
    vector<vector<pair<int, long long>>> graph(n + 1);
    for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
        //w' = w + h(u) - h(v)
        long long newWeight = it->weight + h[it->from] - h[it->to];
        graph[it->from].push_back({it->to, newWeight});
    }


    vector<long long> dist(n + 1, INF); //Svi izvori 0 osim source
    vector<bool> visited(n + 1, false);

    //Moramo staviti ovako dugu definiciju pq jer nam najmanji elementi idu na vrh
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>> 
    > pq; 

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        pair<long long, int> top = pq.top();
        pq.pop();

        int u = top.second;

        if (visited[u]) 
            continue;
        visited[u] = true;

        for (vector<pair<int, long long>>::iterator it = graph[u].begin(); it != graph[u].end(); ++it) {
            int v = it->first;
            long long w = it->second;


            if (dist[v] > dist[u] + w ) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Povrat na originalne težine
    for (int i = 1; i <= n; ++i) {
        if (dist[i] < INF) {
            dist[i] -= h[source] - h[i];
        }
    }

    return dist;
}

//Matrica najkračih puteva od čvora i do čvora j
long long answer[MAXN][MAXN];

//Johnsonov algoritam
bool johnson(int n, vector<Edge> &edges) {
    vector<long long> h(n + 1, INF);

    //Step 1: Dodavanje umjetnog čvora 0
    for (int i = 1; i <= n; ++i) {
        edges.push_back(Edge(0, i, 0));
    }


    //Step 2: Bellman-Ford
    if (!bellmanFord(n+1, 0, edges, h)) {
        return false;
    }

   
    

    // Step 3: Uklanjanje bridova s čvorom 0
    for (int i = 1; i <= n; ++i) {
        edges.pop_back();
    }

    // Step 4: Pokretanje Dijkstre iz svakog čvora
    for (int i = 1; i <= n; ++i) {
        vector<long long> dist = dijkstra(n, i, edges, h);

        for (int j = 1; j <= n; ++j) {
            answer[i][j] = dist[j];
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for(int caseNum = 1; caseNum <= t; caseNum++){
        int n, m;
        cin >> n >> m;

        vector<Edge> edges;

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back(Edge(u, v, w));
        }


        if (!johnson(n, edges)) {
            cout << "-inf\n";
            continue;
        }
        long long min = INF;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if(answer[i][j] < min)
                    min = answer[i][j];
            }
            
        }
        cout << min<<endl;
    }

    return 0;
}