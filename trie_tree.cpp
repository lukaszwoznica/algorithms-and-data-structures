#include <iostream>

using namespace std;

const int SIZE = 10;

struct Node {
    Node *children[SIZE];
    bool isLeaf;
    string name;

    Node(){
        isLeaf = false;
        for (int i = 0; i < SIZE; i++)
            children[i] = nullptr;
    }
};

class Trie{
private:
    Node *root;

public:
    Trie(){
        root = new Node();
    }
    void insert(string key, string name) {
        Node *current = root;

        for (int i = 0; i < key.length(); i++) {
            int index = (int)key[i] - (int)'0';
            if (!current->children[index])
                current->children[index] = new Node;

            current = current->children[index];
        }

        current->name = name;
        current->isLeaf = true;
    }

    void search(string key) {
        Node *current = root;

        for (int i = 0; i < key.length(); i++) {
            int index = (int)key[i] - (int)'0';
            if (!current->children[index]) {
                cout << "-" << endl;
                return;
            }
            current = current->children[index];
        }

        if (current != nullptr && current->isLeaf)
            cout << current->name << endl;
        else
            cout << "-" << endl;
    }

};

int main() {
    int operations_num;
    char operation_type;
    string number, name;
    Trie *tree = new Trie;
    cin >> operations_num;
    for(int i = 0; i < operations_num; i++){
        cin >> operation_type;

        if(operation_type == 'A'){
            cin >> number >> name;
            tree->insert(number, name);
        }

        else if(operation_type == 'S'){
            cin >> number;
            tree->search(number);
        }
    }
    return 0;
}