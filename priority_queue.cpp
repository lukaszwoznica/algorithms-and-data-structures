#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

struct Vase{
    int index;
    int flowers_num;

    Vase(int index, int flowers_num){
        this->index = index;
        this->flowers_num = flowers_num;
    }
    bool isEmpty(){
        if(flowers_num == 0) return true;
        else return false;
    }
};

// Struktura do porownywania w kolejce priorytetowej
struct Compare{
    bool operator ()( Vase & v1, Vase & v2){
        // Liczba kwiatow - malejaco
        if(v1.flowers_num < v2.flowers_num)
            return true;
        if(v1.flowers_num > v2.flowers_num)
            return false;
        // Index wazonu - rosnaco
        if(v1.index > v2.index)
            return true;
        if(v1.index < v2.index)
            return false;

        return false;
    }
};

typedef priority_queue < Vase, vector <Vase>, Compare > VaseQueue;

void arrangeFlowers(VaseQueue  v_q, int flowers_sum){
    Vase temp1(0,0), temp2(0,0);
    if(v_q.top().flowers_num > ceil(flowers_sum/2.0)){
      cout << "NIE";
    }
    else{
        for(int i = 0; i < flowers_sum; i++){
            cout << v_q.top().index << " ";
            if(temp1.isEmpty()){
                temp1 = v_q.top();
                v_q.pop();
                temp1.flowers_num--;
            }
            else{
                temp2 = v_q.top();
                v_q.pop();
                temp2.flowers_num--;
                v_q.push(temp1);
                temp1 = temp2;
           }
        }
    }
    cout << endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int rows_num, vase_num, flowers_num;

    cin >> rows_num; // Liczba rzedow
    for(int i = 0; i < rows_num; i++){
        VaseQueue v_queue;
        int flowers_sum = 0; // Suma kwiatow w wazonie
        cin >> vase_num; // Liczba wazonow
        for(int j = 0; j < vase_num; j++){
            cin >> flowers_num;
            v_queue.push(Vase(j, flowers_num));
            flowers_sum += flowers_num;
        }
        arrangeFlowers(v_queue, flowers_sum);
    }
    return 0;
}