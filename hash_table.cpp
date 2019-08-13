#include <iostream>
#include <vector>

using namespace std;

int TABLE_SIZE;

struct HashElement{
    string name, place;
};

class HashTable{
private:
    vector<HashElement> *map;

    int hashFunction(string key){
        int sum = 0;
        for(int i = 0; i < key.length(); i++)
            sum = sum + int(key[i]);
        return  sum % TABLE_SIZE;
    }
public:
    HashTable(){
        map = new vector<HashElement>[TABLE_SIZE];
    }

    void insert(string name, string place){
        HashElement new_el;
        new_el.name = name;
        new_el.place = place;
        int i = hashFunction(name);
        map[i].push_back(new_el);
    }

    void search(string name){
        int i = hashFunction(name);
        bool found = false;
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j].name == name){
                found = true;
                cout << map[i][j].place << endl;
                break;
            }
        }
        if(!found)
            cout << "-" << endl;
    }

};

int main() {
    int operations_num;
    char operation_type;
    string name, place;
    cin >> operations_num;
    TABLE_SIZE = operations_num;
    HashTable h_table;

    for(int i = 0; i < operations_num; i++){
        cin >> operation_type;
        if(operation_type == 'A'){
            cin >> name >> place;
            h_table.insert(name, place);
        }
        else if(operation_type == 'S'){
            cin >> name;
            h_table.search(name);
        }
    }

    return 0;
}