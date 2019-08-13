#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Edge{
    int v;
    double weight1, weight2;
    Edge(int v1, double w1, double w2){
        v = v1;
        weight1 = w1;
        weight2 = w2;
    }
};

struct Vertex{
    double dist1, dist2;
    vector<Edge> edges;
};

class Graph{
public:
    vector<Vertex> adj_list;

    Graph(int size){
        for(int i = 0; i < size; i++)
            adj_list.push_back(Vertex());
    }

    void dijkstraFirst(int start){
        set <int>  vertex_set;

        for(int i = 0; i < adj_list.size(); i++){
            vertex_set.insert(i);
            adj_list[i].dist1 = 0;
        }

        adj_list[start].dist1 = 1;

        while(!vertex_set.empty()){
            int min_dist = -1;

            for (int i : vertex_set)
                if (min_dist == -1 || adj_list[min_dist].dist1 < adj_list[i].dist1)
                    min_dist = i;

            vertex_set.erase(min_dist);

            for(Edge q : adj_list[min_dist].edges){
                double dist = q.weight1 * adj_list[min_dist].dist1;
                if (dist > adj_list[q.v].dist1)
                    adj_list[q.v].dist1 = dist;
            }
        }
    }

    void dijkstraSecond(int start){
         set <int>  vertex_set;

        for(int i = 0; i < adj_list.size(); i++){
            vertex_set.insert(i);
            adj_list[i].dist2 = 0;
        }

        adj_list[start].dist2 = 1;

        while(!vertex_set.empty()){
            int min_dist = -1;

            for (int i : vertex_set)
                if (min_dist == -1 || adj_list[min_dist].dist2 < adj_list[i].dist2)
                    min_dist = i;

            vertex_set.erase(min_dist);

            for(Edge q : adj_list[min_dist].edges){
               double dist = q.weight2 * adj_list[min_dist].dist2;
                if (dist > adj_list[q.v].dist2)
                    adj_list[q.v].dist2 = dist;
            }
        }
    }
};


int main(){
    std::ios_base::sync_with_stdio(false);
    int exchanges_num, has_bc, edges_num, v1, v2, start;
    double weight1, weight2, max;
    vector <int> bajtcoin_list;

    cin >> exchanges_num;
    Graph g(exchanges_num);

    for(int i = 0; i < exchanges_num; i++){
        cin >> has_bc;
        if(has_bc == 1)
            bajtcoin_list.push_back(i);
    }

    cin >> edges_num;

    for(int i = 0; i < edges_num; i++){
        cin >> v1 >> v2 >> weight1 >> weight2;
        Edge e1(v1, 1 - weight1, 1 - weight2);
        g.adj_list[v2].edges.push_back(e1);
        Edge e2(v2, 1 - weight1, 1 - weight2);
        g.adj_list[v1].edges.push_back(e2);
    }
    cin >> start;

    g.dijkstraFirst(start);
    g.dijkstraSecond(start);

    max = 1.2 * (g.adj_list[bajtcoin_list[0]].dist1 * g.adj_list[bajtcoin_list[0]].dist2);

    for(int i = 1; i < bajtcoin_list.size(); i++){
        int j = bajtcoin_list[i];
        if (1.2 * (g.adj_list[j].dist1 * g.adj_list[j].dist2) > max)
                max = 1.2 * (g.adj_list[j].dist1 * g.adj_list[j].dist2);
    }

    cout << 100000 * max << endl;

    return 0;
}