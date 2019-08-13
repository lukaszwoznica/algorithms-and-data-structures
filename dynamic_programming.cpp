#include <iostream>

using namespace std;

int searchMax(int a, int b){
    if(a >= b) return a;
    else return b;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int rows_num, cols_num;
    cin >> rows_num >> cols_num;
    int mush_num;
    int arr[2][cols_num];
        //Wczytanie do pierwszego wiersza
    for(int i = 0; i < cols_num; i++){
        cin >> arr[0][i];
    }
        //Jezeli jest wiecej niz jeden wiersz wczytuje dalej
    if(rows_num > 1){
        for(int i = 1; i < rows_num; i++){
            for(int j = 0; j < cols_num; j++){
                cin >> mush_num;    // Liczba grzybow w komorce
                if(j == 0){ // Brzegowa lewa kolumna
                    arr[i % 2][j] = mush_num + searchMax(arr[(i + 1) % 2][j], arr[(i + 1) % 2][j + 1]);
                }
                if( j > 0 && j < cols_num - 1){ // Kolumna nie brzegowa
                    arr[i % 2][j] = mush_num + searchMax(arr[(i + 1) % 2][j], searchMax(arr[(i + 1) % 2][j - 1], arr[(i + 1) % 2][j + 1]));
                }
                if(j == cols_num - 1){ // Brzegowa prawa kolumna
                    arr[i % 2][j] = mush_num + searchMax(arr[(i + 1) % 2][j],arr[(i + 1) % 2][j - 1]);
                }
                if(cols_num == 1){  // Jezeli jest jedna kolumna
                    arr[i % 2][j] = mush_num + arr[(i + 1) % 2][j];
                }
            }
        }
    }
    int max = arr[(rows_num - 1) % 2][0];   // Maksymalna liczba zebranych grzybow (wart domyslna)
    int index = 0;
    for(int i = 0; i < cols_num; i++){
         if(arr[(rows_num - 1) % 2][i] > max){  // Wyszukiwanie max w tablicy 
             max = arr[(rows_num - 1) % 2][i];
             index = i;
         }
    }
    cout << index << " " << max << endl;
    return 0;
}