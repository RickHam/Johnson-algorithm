#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>

int WHITE = 0, GREY = 1, BLACK = 2;

struct vertex{
    int color, d, prev,  component;

    vertex(){
        this->color = WHITE;
        this->d = INT_MAX;
        this->prev = -1;
        this -> component = WHITE;
    }

    vertex(int color, int d, int prev, int component){
        this->color= color;
        this->d = d;
        this->prev = prev;
        this->component = component;

    }
};

int bfs(std::vector<int> adj,int s, int n)
{
    vertex vrhovi[n+1];
    
    return 0;
}


int main(void){
    std::cout<<"Hello World!"<<std::endl;

    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> adj[n+1];

    for(int i = 0; i<m; i++){
        int e1, e2;
        std::cin>>e1>>e2;
        adj[e1].push_back(e2);
        adj[e2].push_back(e1);
    }

    std::cout<<"Ispis susjednih bridova"<<std::endl;

    for(int i = 1; i <=n; i++)
    {
        for(auto it = adj[i].begin(); it != adj[i].end(); ++it)
        {
            std::cout<<*it<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}