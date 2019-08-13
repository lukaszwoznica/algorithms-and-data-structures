#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int main(){
    std::ios::sync_with_stdio(false);
    int juice_num, pair_num;    // liczba sokow / liczba par sokow
    string juice_name;
    map<string, int> name_to_id;
    map<int, string> id_to_name;
    pair<string, string> juice_pair;
    vector < vector<int> > neighbours;  // lista sasiedztwa
    vector<int> attach_num; // liczba przypiec
    cin >> juice_num >> pair_num;
    // Wczytanie sokow
    for(int i = 0; i < juice_num; i++){
        cin >> juice_name;
        name_to_id[juice_name] = i;
        id_to_name[i] = juice_name;
        neighbours.push_back(vector<int>());    // Dodanie nowego elementu do list sasiedztwa
        attach_num.push_back(0);    // Dodawanie i zerowanie vectora z liczba przypiec
    }
    // Wczytanie par sokow
    for(int i = 0; i < pair_num; i++){
        cin >> juice_pair.first >> juice_pair.second;
        int id_from_first = name_to_id[juice_pair.first];
        int id_from_second = name_to_id[juice_pair.second];
        attach_num[id_from_second]++;
        neighbours[id_from_first].push_back(id_from_second);
    }
    // Kolejka w ktorej znajdowac sie bedzie sok z najmniejsza iloscia przypiec
    priority_queue < int, vector < int >, greater < int > > que;
    for(int i = 0; i < juice_num; i++){
        if(attach_num[i] == 0)
            que.push(i);
    }
    for(int i = 0; i < juice_num; i++){
        int min = que.top();    // Index soku z najmniejsza iloscia przypiec
        que.pop();
        for(int i = 0; i <  neighbours[min].size(); i++){   // Petla po sasiadach soku z minimum przypiec
            int neighbour_id = neighbours[min][i];  // Index i-tego sasiada
            --attach_num[neighbour_id]; // Zmniejszamy liczbe przypiec
            if(attach_num[neighbour_id] == 0)
                que.push(neighbour_id); // Jezeli liczba przypiec sasiada = 0 to wrzucamy na kolejke
        }
        cout << id_to_name[min] << endl;
    }
    return 0;
}