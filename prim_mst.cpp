#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

struct Edge{
    int  dest;
    double weight;
    Edge(){}
    Edge(int dest, double weight){
        this->dest = dest;
        this->weight = weight;
    }
};

struct Vertex {
    vector<Edge> edges;
};

struct Compare{
    bool operator ()( Edge & e1, Edge & e2){
        if(e1.weight < e2.weight)
            return true;
        if(e1.weight > e2.weight)
            return false;

        return false;
    }
};

class Graph{
public:
    vector<Vertex> adj_list;
    int vertex_num;

    Graph(int vertex_num){
        this->vertex_num = vertex_num;
         for(int i = 0; i < vertex_num; i++)
            adj_list.push_back(Vertex());
    }

    double primMST(){
        priority_queue<Edge, vector<Edge>, Compare> p_que;
        Edge e;
        double weights = 1;
        bool * visited = new bool[vertex_num];

        for(int i = 0; i < vertex_num; i++){
            visited[i] = false;
        }

        int v = 0;
        visited[v] = true;

        for(int i = 1; i < vertex_num; i++){

            for(int j = 0; j < adj_list[v].edges.size(); j++){
                e = adj_list[v].edges[j];
                if(!visited[e.dest]){
                    p_que.push(e);
                }
            }

            do{
                e = p_que.top();
                p_que.pop();
            }
            while(visited[e.dest]);

            weights = weights * e.weight;
            visited[e.dest] = true;
            v = e.dest;
        }

        delete [] visited;
        visited = NULL;

        return weights;
    }
};


int main(){
    std::ios_base::sync_with_stdio(false);
    int vertex_num, edges_num, v1, v2;
    double weight;

    cin >> vertex_num >> edges_num;

    Graph g(vertex_num);

    for(int i = 0; i < edges_num; i++){
        cin >> v1 >> v2 >> weight;
        Edge e1(v1, weight);
        g.adj_list[v2].edges.push_back(e1);
        Edge e2(v2, weight);
        g.adj_list[v1].edges.push_back(e2);
    }

    cout << setprecision(3) << fixed << g.primMST() << endl;

    return 0;
}