#include <iostream>
#include <string>
 
using namespace std;
 
int max_activity;
 
struct Element{
    string name;
    int activity_level, index;
};
 
class Heap{
public:
    int max_size;
    int current_size;
    Element * arr;
 
    void swap(Element  &el1, Element  &el2){
        Element temp = el1;
        el1 = el2;
        el2 = temp;
    }
 
    void bubbleUp(int index){
         while (index != 0 && (arr[(index - 1) / 2].activity_level < arr[index].activity_level) || (arr[(index - 1) / 2].activity_level == arr[index].activity_level && arr[(index - 1) / 2].index > arr[index].index)) {
            swap(arr[(index - 1) / 2], arr[index]);
            index = (index - 1) / 2;
        }
    }
 
    void bubbleDown(int index){
       while((2 * index + 1 < current_size
                    && ((arr[2 * index + 1].activity_level > arr[index].activity_level)
                        || (arr[2 * index + 1].activity_level == arr[index].activity_level && arr[2 * index + 1].index < arr[index].index)))
               || (2 * index + 2 < current_size
                    && ((arr[2 * index + 2].activity_level > arr[index].activity_level)
                        || (arr[2 * index + 2].activity_level == arr[index].activity_level && arr[2 * index + 2].index < arr[index].index)))){
 
            int parentActivityLvl =arr[index].activity_level;
            int leftChildActivityLvl = arr[2 * index + 1].activity_level;
            int rightChildActivityLvl = arr[2 * index + 2].activity_level;
            int parentIndex =arr[index].index;
            int leftChildIndex = arr[2 * index + 1].index;
            int rightChildIndex = arr[2 * index + 2].index;
 
            if( (2 * index + 1 < current_size && leftChildActivityLvl == parentActivityLvl) && (2 * index + 2 < current_size &&rightChildActivityLvl == parentActivityLvl) ){
                if(leftChildIndex < parentIndex && leftChildIndex < rightChildIndex){
                    swap(arr[index], arr[2 * index + 1]);
                    index = 2 * index + 1;
                    continue;
                }
                else if(rightChildIndex < parentIndex && leftChildIndex > rightChildIndex){
                    swap(arr[index], arr[2 * index + 2]);
                    index = 2 * index + 2;
                    continue;
                }
            }
 
            if( (2 * index + 1 < current_size && leftChildActivityLvl > parentActivityLvl) && (2 * index + 2 < current_size &&rightChildActivityLvl > parentActivityLvl) ){
                if(leftChildActivityLvl >rightChildActivityLvl || (leftChildActivityLvl ==rightChildActivityLvl && leftChildIndex < rightChildIndex) ){
                    swap(arr[index], arr[2 * index + 1]);
                    index = 2 * index + 1;
                    continue;
                }
                else if(leftChildActivityLvl <rightChildActivityLvl || (leftChildActivityLvl ==rightChildActivityLvl && leftChildIndex > rightChildIndex) ){
                    swap(arr[index], arr[2 * index + 2]);
                    index = 2 * index + 2;
                    continue;
                }
            }
 
            if(2 * index + 1 < current_size && leftChildActivityLvl > parentActivityLvl){
                swap(arr[index], arr[2 * index + 1]);
                index = 2 * index + 1;
                continue;
            }
 
            if(2 * index + 2 < current_size &&rightChildActivityLvl > parentActivityLvl){
                swap(arr[index], arr[2 * index + 2]);
                index = 2 * index + 2;
                continue;
            }
 
            if(2 * index + 1 < current_size && (leftChildActivityLvl == parentActivityLvl && leftChildIndex < parentIndex) ){
                swap(arr[index], arr[2 * index + 1]);
                index = 2 * index + 1;
                continue;
            }
 
            if(2 * index + 2 < current_size && (rightChildActivityLvl == parentActivityLvl && rightChildIndex < parentIndex) ){
                swap(arr[index], arr[2 * index + 2]);
                index = 2 * index + 2;
                continue;
            }
       }
    }
 
public:
    Heap(int size){
        this->max_size = size;
        arr = new Element[max_size];
        current_size = 0;
    }
 
    void push(Element newEl){
        current_size++;
        int index = current_size - 1;
        arr[index] = newEl;
        bubbleUp(index);
    }
 
    void pop(){
       
        if(arr[0].activity_level <= max_activity){
            max_activity -= arr[0].activity_level;
            cout << arr[0].name << " ";
        }
        arr[0] = arr[current_size - 1];
        --current_size;
        bubbleDown(0);
    }
 
    bool empty(){
        if(current_size != 0)
            return false;
        else
            return true;
    }
};
 
int main(){
    std::ios::sync_with_stdio(false);
    int places_num, activity_level;
    string name;
 
    cin >> places_num;
    Heap heap(places_num);
    for(int i = 0; i < places_num; i++){
        cin >> name >> activity_level;
        Element el;
        el.name = name;
        el.activity_level = activity_level;
        el.index = i;
        heap.push(el);
    }
    cin >> max_activity;
    while(max_activity > 0 && heap.current_size != 0)
        heap.pop();
 
    return 0;
}