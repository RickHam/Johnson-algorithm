#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge{
    int u,v,w;
};


vector<long long> bellmanFord(int N, vector<Edge>& edges)
{
   vector<long long> h(N+1, 0);
   
   for(int i = 0; i<N-1; i++)
   {
        for(vector<Edge>::iterator it = edges.begin(); it!= edges.end(); ++it)
        {
            if(h[it->v] > h[it->u] + it->w)
            {
               h[it->v] = h[it->u] + it->w;
            }
        }
   }

   return h;
}

bool hasNegativeCycle(int N, vector<Edge>& edges, vector<long long>& h)
{
    for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        if(h[it->v] > h[it->u] + it->w)
            return true;
    }
    return false;
}

vector<long long> dijkstra(int src, int n, vector<pair<int, int>> adj[])
{
    vector<long long> dist(n+1, LLONG_MAX);
    dist[src] = 0;

    //Not scary definicija at all
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>, 
        greater<pair<int,int>>
    > pq;

    pq.push({0, src});

    while(!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if(d > dist[u])
            continue;
        
        for(vector<pair<int, int>>::iterator it = adj[u].begin(); it != adj[u].end(); ++it)
        {
            int v = it->first;
            int w = it->second;

            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }

    }
    return dist;
}

int main(void){
    int test_cases;
    
    cin >> test_cases;

    int n,m;

    for(int i = 0; i < test_cases; i++)
    {
        cin >>n>>m;

        vector<pair<int,int>> adj[n+1];
        vector<Edge> edges;
        for(int j = 0; j < m; j++)
        {
            int u,v,w;
            cin >> u >> v >> w;

            adj[u].push_back({v,w});
            edges.push_back({u,v,w});
        }

        vector<long long> h = bellmanFord(n, edges);

        //Ako ima negativnih ciklusa, očito je najmanji put -inf
        bool provjera = hasNegativeCycle(n, edges, h);
        if(provjera == true)
        {
            cout<<"-inf"<<endl;
        }
        else
        {
            int ans = INT_MAX;

            for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
            {
                int cur = it->w + h[it->u] -h[it->v];
                ans = min(ans,cur);
            }

            cout << ans << endl;
        }

    }
    return 0;
}