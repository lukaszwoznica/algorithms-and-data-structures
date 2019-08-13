<iostream>
#include <queue>
#include <cmath>

using namespace std;

struct Details{
    string name;
    double ratio;
    int position;
};

struct Compare{
    bool operator ()( Details & el1, Details & el2){
        if(el1.ratio < el2.ratio)
            return true;
        if(el1.ratio > el2.ratio)
            return false;
        if(el1.position < el2.position)
            return true;
        if(el1.position > el2.position)
            return false;

        return false;
    }
};


struct Node{
    int price;
    Node *left, *right;
    priority_queue<Details, vector<Details>, Compare> p_que;

    Node(int price, Details new_el){
        left = right = NULL;
        this->price = price;
        p_que.push(new_el);
    }

    void print(){
        cout << p_que.top().name << endl;
    }
};

class BST{
public:
    Node *root;

    BST(){
        root = NULL;
    }

    Node * search(int key){
        Node *v = root;

        while(v != NULL && v->price != key){
            if(v->price  < key)
                v = v->right;
            else
                v = v->left;
        }

        return v;
    }

    void insert(int price, Details new_el) {
        if(!root)
            root = new Node(price, new_el);

        else{
            Node *current = root;
            Node *parent = NULL;

            while(current){
                if (current->price == price){
                    current->p_que.push(new_el);
                    return;
                }
                if (current->price > price) {
                    parent = current;
                    current = current->left;
                }
                else {
                    parent = current;
                    current = current->right;
                }
            }

            current = new Node(price, new_el);

            if (parent->price > current->price)
                parent->left = current;
            else
                parent->right = current;
        }
    }

    void remove(Node *remove_el){
        if (!remove_el->p_que.empty())
            remove_el->p_que.pop();
    }
};

int main(){
    int operations_num, voices, price;
    float avg, ratio;
    string name;
    char oper_type;
    BST tree;
    Details new_element;

    cin >> operations_num;

    for(int i = 0; i < operations_num; i++){
        cin >> oper_type;

        if(oper_type == 'A'){
            cin >> avg >> voices >> price >> name;
            new_element.name = name;
            new_element.ratio = avg / 5 * floor(voices / 1000);
            new_element.position = i;
            tree.insert(price, new_element);
        }

        else if(oper_type == 'S'){
            cin >> price >> ratio;
            Node *temp = tree.search(price);

            if(!temp || temp->p_que.empty() || temp->p_que.top().ratio < ratio)
                cout << "-" << endl;
            else{
                temp->print();
                tree.remove(temp);
            }
        }
    }

    return 0;
}