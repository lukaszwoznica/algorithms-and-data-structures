#include <iostream>

using namespace std;

struct vertex{
        vertex * next, *prev;
        int value;
};

class  List{
private:
    vertex * first, * last;
    unsigned int counter;
public:
    // Konstruktor
    List(){
        first = NULL;
        last = NULL;
        counter  = 0;
    }

    // Destruktor
    ~List(){
        vertex * p;
        while(first){
            p = first->next;
            delete first;
            first = p;
        }
    }

    bool empty(){
        if (counter == 0)
            return  true;
        else
            return  false;
    }

    int front(){
        return  first->value;
    }

    vertex * front_struct(){
        return first;
    }

    int back (){
        return  last->value;
    }

    vertex * back_struct(){
        return last;
    }

    vertex * next_struct(vertex * p) {
		return p->next;
	}

	vertex * prev_struct(vertex * p) {
		return p->prev;
	}

    void push_front(int val){
        vertex * p = new vertex;
        p->next = first;
        p->prev = NULL;
        p->value = val;
        if(first)
            first->prev = p;
        first = p;
        if(!last)
            last = first;
        counter++;
    }

    void push_back(int val){
        vertex * p = new vertex;
        if(last)
            last->next = p;
        p->next = NULL;
        p->prev = last;
        p->value = val;
        last = p;
        if(!first)
            first = last;
        counter++;
    }

    void pop_front(){
        vertex * p;
        if(first){
            p = first;
            first = first->next;
            if(!first)
                last = NULL;
            else
                first->prev = NULL;
            counter--;
            delete p;
        }
    }

    void pop_back(){
        vertex * p;
        if(last){
            p = last;
            if(p == first)
                first = last = NULL;
            else{
              last = last->prev;
              last->next = NULL;
            };
            counter--;
            delete p;
        }
    }

    void show_values(){
        vertex * p;
        p = first;
        while(p){
          cout << p->value << " ";
          p = p->next;
        }
    }
};

void  DFS(int v, List * arr, bool visited[]){
    visited[v] = true;
    List * p = &arr[v];
    vertex * vert = p->front_struct();
    while(vert != NULL){
        if(!visited[vert->value])
            DFS(vert->value, arr, visited);
        vert=p->next_struct(vert);
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int photos_num, vertex_num, edge_num, x, y;
    List * arr;     // Tablica list sasiedztwa
    bool * visited;     // Tablica odwiedzonych wierzcholkow
    cin >> photos_num;
    for(int i = 0; i < photos_num; i++){
        cin >> vertex_num >> edge_num;

        // Jezeli liczba wierzcholkow i krawedzi jest rozna to nie kartofel
        if(vertex_num != edge_num){
            for(int j = 0; j < edge_num; j++){
                cin >> x >> y;
            }
            cout << "TO NIE KARTOFEL" << endl;
        }

        else{
            arr = new List[vertex_num];
            visited = new bool[vertex_num];
            bool is_kartofel = true;
            // Zerowanie tablicy odwiedzin
            for(int k = 0; k < vertex_num; k++)
                visited[k] = false;

            // Wczytywanie wierzcholkow dla krawedzi i zapisanie do tablicy list
            for(int j = 0; j < edge_num; j++){
                cin >> x >> y;
                arr[x].push_back(y);
                arr[y].push_back(x);
            }
            // Przeszukiwanie grafu przez DFS
            DFS(0, arr, visited);
            // Sprawdzenie czy graf jest spojny
            for(int j = 0; j < vertex_num; j++){
                if(!visited[j]){
                    is_kartofel = false;
                    break;
                }
            }
            // Wynik
            if(is_kartofel)
                cout << "TO KARTOFEL" << endl;
            else
                cout << "TO NIE KARTOFEL" << endl;
            // Usuwanie tablic
            delete [] arr;
            arr = NULL;
            delete [] visited;
            visited = NULL;
        }

    }
    return 0;
}