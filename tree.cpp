#include <iostream>

using namespace std;

struct treeElement{
    char ch;    // Litera na malpce
    int max_children;   // Maksymalna liczba doczepien
    int children_number;    // Faktyczna ilosc dzieci
    treeElement ** children;    // Tablica dzieci

    treeElement(char ch, int max_children){
        this->ch = ch;
        this->max_children = max_children;
        children = new treeElement*[max_children];
        children_number = 0;
    }

    treeElement(){}

    bool addChild(treeElement * t){
        if(children_number < max_children){
            children[children_number] = t;
            children_number++;
            return true;
        }
        else
            return false;
    }
    void  preorder(){
        cout << ch;
        for(unsigned int i = 0; i < children_number; i++)
            children[i]->preorder();
    }

};

int main(){
    int boxes_num, monkeys_num;;    // Liczba pudelek, liczba maplek w pudelku
    int number_on_monkey;   // Numer na malpce
    char char_on_monkey;    // Litera na malpce
    cin >> boxes_num;
    for(int i = 0; i < boxes_num; i++){
        cin >> monkeys_num;
        treeElement **  arr = new treeElement *[monkeys_num];   // Tablica przechowujaca wszystkie elementy drzewa
        for(int j = 0; j < monkeys_num; j++){
            cin >> char_on_monkey >> number_on_monkey;
            arr[j] = new treeElement(char_on_monkey, number_on_monkey);;
        }
        int monkeys_added = 1;  // Liczba malpek dodanych do drzewa
        for(int arr_index = 0; monkeys_added < monkeys_num && arr_index < monkeys_num; arr_index++){
            while( monkeys_added < monkeys_num && arr[arr_index]->addChild(arr[monkeys_added])){
                monkeys_added++;
             }
        }
        if(monkeys_num > 0)
            arr[0]->preorder();
        cout << endl;
        delete [] arr;
    }

    return 0;
}