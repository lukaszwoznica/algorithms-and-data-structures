#include <iostream>
#include <vector>

using namespace std;

struct Edge{
    int src, dest;
    double weight_s_d, weight_d_s;
    Edge(int src, int dest, double weight1, double weight2){
        this->src = src;
        this->dest = dest;
        this->weight_s_d = weight1;
        this->weight_d_s = weight2;
    }
};

class Graph{
public:
    vector <Edge> edges;
    double * dist;
    int v;

    Graph(int vertex_num){
        dist = new double[vertex_num];
        v = vertex_num;
    }

    void ford_bellman(){
        for(int j = 1; j < v - 1; j++){

            bool test = false;

            for(int i = 0; i < edges.size(); i++){
                if(dist[edges[i].dest] < dist[edges[i].src] - dist[edges[i].src] * edges[i].weight_s_d){
                    test = true;
                    dist[edges[i].dest] = dist[edges[i].src] - dist[edges[i].src] * edges[i].weight_s_d;
                }
                if(dist[edges[i].src] < dist[edges[i].dest] - dist[edges[i].dest] * edges[i].weight_d_s){
                    test = true;
                    dist[edges[i].src] = dist[edges[i].dest] - dist[edges[i].dest] * edges[i].weight_d_s;
                }
            }
            if(!test)
                break;

        }
    }

};


int main(){
    std::ios_base::sync_with_stdio(false);
    int exchanges_num, has_bc, edges_num, v1, v2, start;
    double weight1, weight2, max;
    bool negative_cycle = false;
    vector <int> bajtcoin_list;

    cin >> exchanges_num;
    Graph g(exchanges_num);

    for(int i = 0; i < exchanges_num; i++){
        cin >> has_bc;
        if(has_bc == 1)
            bajtcoin_list.push_back(i);
        g.dist[i] = 0.0;
    }

    cin >> edges_num;

    for(int i = 0; i < edges_num; i++){
        cin >> v1 >> v2 >> weight1 >> weight2;
        Edge e(v1, v2, weight1, weight2);
        g.edges.push_back(e);
        if(weight1 + weight2 < 0)
            negative_cycle = true;
    }

    cin >> start;

    if(negative_cycle){
        cout << "MATEUSZU NIE KOMBINUJ!" << endl;
        return 0;
    }

    g.dist[start] = 100000.0;

    g.ford_bellman();

    for(int i = 0; i < bajtcoin_list.size(); i++){
        g.dist[ bajtcoin_list[i] ] = 1.2 * g.dist[ bajtcoin_list[i] ];
    }

    g.ford_bellman();

    max = g.dist[start];

    cout << static_cast<int>(max) << endl;

    return 0;
}