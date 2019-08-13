#include <iostream>
#include <utility>

using namespace std;

int MaxDzielnik(pair<int, int> x){
    int max = 1;
    for(int i = x.second/2; i > 1; i--){                    
        if(x.second%i == 0){                                
            max = i;
            break;
        }
    }
    return max;
}

void  Sortuj(pair<int, int>  tab[], int n){
    pair<int ,int> temp;
    for(int i = 1; i < n/2; i++){                                                                              
        temp = tab[i];                                                                                        
        for(int j = i - 1; (j  >= 0) && (tab[j].first >= temp.first); j--){                            
            if(tab[j].first > temp.first){                                                                     
                tab[j + 1] = tab[j];
                tab[j] = temp;
            }
            else if((tab[j].first == temp.first) && MaxDzielnik(tab[j]) < MaxDzielnik(temp)){   
                tab[j + 1]=tab[j];
                tab[j] = temp;
            }
       }
    }
}


int main(){
    int liczba_ciagow;
    int dlugosc_ciagu;

    cin >> liczba_ciagow;

    for(int j = 0; j < liczba_ciagow; j++){
        cin >> dlugosc_ciagu;
        pair<int,int> ciag[dlugosc_ciagu/2];
        for(int i = 0; i < dlugosc_ciagu/2; i ++){
            cin >> ciag[i].first >> ciag[i].second;
        }
        Sortuj(ciag, dlugosc_ciagu);
        for(int i = 0; i < dlugosc_ciagu/2; i++)
           cout << ciag[i].first << " " << ciag[i].second << " ";
    }
    return 0;
}