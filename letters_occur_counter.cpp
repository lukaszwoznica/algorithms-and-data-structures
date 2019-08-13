#include <iostream>

using namespace std;

void Zliczanie(char z, int tab[]){
    if(z >= 65 && z <= 90)
        tab[z+32]++;
    else if(z >= 97 && z<= 122)
        tab[z]++;
}

void Litera(int tab[]){
    int max = 0;
    int max_kod = 97;
    for(int i = 97; i <= 122; i++){
        if(tab[i] > max){
            max = tab[i];
            max_kod = i;
        }
    }
    char max_znak = max_kod;

    int min = max ;
    int min_kod = max_kod;
    for(int i = 97; i <= 122; i++){
        if(tab[i] > 0 && tab[i] < min){
            min = tab[i];
            min_kod = i;
        }
    }
    char min_znak = min_kod;

    cout << max_znak << " " << min_znak << endl;
}

int main(){
    char znak;
    int ilosc[256];
    int i;

    for(int i = 0; i < 256; i++){
        ilosc[i] = 0;
    }

    while(znak != '^'){
        cin >> znak;
        Zliczanie(znak, ilosc);
    }

    Litera(ilosc);
    return 0;
}