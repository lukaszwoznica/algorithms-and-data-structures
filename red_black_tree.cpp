#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Details {
    string name;
    double ratio;
    int position;
};

struct Compare {
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


struct Node {
    int price;
    Node *left, *right, *parent;
    char color;
    priority_queue<Details, vector<Details>, Compare> p_que;

    void print(){
        cout << p_que.top().name << endl;
    }
};

class RBTree {
private:
    Node *sentinel;
    Node *root;

public:
    RBTree() {
        sentinel = new Node;
        sentinel->parent = sentinel;
        sentinel->left = sentinel;
        sentinel->right = sentinel;
        sentinel->color = 'B';
        root = sentinel;
    }

    void rotateLeft(Node *new_node) {
        Node *right = new_node->right;

        if(right != sentinel) {
            Node *parent = new_node->parent;
            new_node->right = right->left;

            if (new_node->right != sentinel)
                new_node->right->parent = new_node;

            right->parent = parent;
            right->left = new_node;
            new_node->parent = right;

            if (parent == sentinel)
                root = right;

            else {
                if (parent->left == new_node)
                    parent->left = right;
                else
                    parent->right = right;
            }
        }
    }

    void rotateRight(Node *new_node) {
        Node *left = new_node->left;

        if(left != sentinel) {
            Node *parent = new_node->parent;
            new_node->left = left->right;

            if(new_node->left != sentinel)
                new_node->left->parent = new_node;

            left->parent = parent;
            left->right = new_node;
            new_node->parent = left;

            if(parent == sentinel)
                root = left;

            else {
                if(parent->left == new_node)
                    parent->left = left;
                else
                    parent->right = left;
            }
        }
    }

    void insert(int price, Details new_element) {
        Node *new_node = new Node;
        new_node->left = new_node->right = sentinel;
        new_node->parent = root;
        new_node->price = price;
        new_node->p_que.push(new_element);

        Node *uncle, *grand_parent;

        if(new_node->parent == sentinel)
            root = new_node;
        else {
            while (true) {
                if (price < new_node->parent->price) {
                    if (new_node->parent->left == sentinel) {
                        new_node->parent->left = new_node;
                        break;
                    }
                    new_node->parent = new_node->parent->left;
                }
                else {
                    if (new_node->parent->right == sentinel) {
                        new_node->parent->right = new_node;
                        break;
                    }
                    new_node->parent = new_node->parent->right;
                }
            }
        }
        new_node->color = 'R';
        while((new_node != root) && (new_node->parent->color == 'R')) {
            grand_parent = new_node->parent->parent;
            if(new_node->parent == grand_parent->left) {
                uncle = grand_parent->right;

                if(uncle->color == 'R') {
                    new_node->parent->color = 'B';
                    uncle->color = 'B';
                    grand_parent->color = 'R';
                    new_node = grand_parent;
                    continue;
                }

                if(new_node == new_node->parent->right) {
                    new_node = new_node->parent;
                    rotateLeft(new_node);
                }

                new_node->parent->color = 'B';
                grand_parent->color = 'R';
                rotateRight(grand_parent);
                break;
            }
            else {
                uncle = grand_parent->left;

                if(uncle->color == 'R') {
                    new_node->parent->color = 'B';
                    uncle->color = 'B';
                    grand_parent->color = 'R';
                    new_node = grand_parent;
                    continue;
                }

                if(new_node == new_node->parent->left) {
                    new_node = new_node->parent;
                    rotateRight(new_node);
                }

                new_node->parent->color = 'B';
                grand_parent->color = 'R';
                rotateLeft(grand_parent);
                break;
            }
        }
        root->color = 'B';
    }

    Node *search(int key){
        Node *v = root;
        if (root == sentinel){
            return nullptr;
        }
        while(v != sentinel && v->price != key){
            if(v->price  < key)
                v = v->right;
            else
                v = v->left;
        }
        if(v->price != key)
            return nullptr;
        return v;
    }
};


int main() {
    int operations_num, voices, price;
    float avg, ratio;
    string name;
    char operation_type;
    RBTree tree;
    Details new_element;
    Node *temp;

    cin >> operations_num;

    for(int i = 0; i < operations_num; i++){
        cin >> operation_type;

        if(operation_type == 'A'){
            cin >> avg >> voices >> price >> name;
            new_element.name = name;
            new_element.ratio = avg / 5 * floor(voices / 1000);
            new_element.position = i;

            temp = tree.search(price);

            if (!temp)
                tree.insert(price, new_element);
            else
                temp->p_que.push(new_element);
        }

        else if(operation_type == 'S'){
            cin >> price >> ratio;
            temp = tree.search(price);

            if(!temp || temp->p_que.empty() || temp->p_que.top().ratio < ratio)
                cout << "-" << endl;
            else
                temp->print();
        }
    }

    return 0;
}