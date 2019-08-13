#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Dish{
    string name;
    int units, tens;    // Liczba jednosci i dziesiatek z kalorii

    void Init(string name, int units, int tens){
        this->name = name;
        this->units = units;
        this->tens = tens;
    }
};

void sort(Dish * arr, int n){
    int i;
    // Tablice do zliczania jednosci i dziesatek
    int * units_count = new int[n];
    int * tens_count = new int[n];
    Dish * output_arr = new Dish[n];    // Tablica wyjsciowa
    memset(units_count, 0, sizeof(int) * n);    // Zerowanie tablic
    memset(tens_count, 0, sizeof(int) * n);
    // Zliczanie wystapien
    for(i = 0; i < n; i++){
        units_count[arr[i].units]++;
        tens_count[arr[i].tens]++;
    }

	units_count[0]--;
	tens_count[0]--;

    // Dodawianie do elementow tablic wartosc z poprzedniego elementu
	for(int i = 1; i < n; i++){
        units_count[i] = units_count[i] + units_count[i - 1];
        tens_count[i] = tens_count[i] + tens_count[i - 1];
	}
    // Przypisuje watrosc z tablicy wejsciowej do tablicy pomocniczej do miejsca na ktore wskazuje wartosc z tablicy jednosci;
    for(i = n - 1; i >= 0; i--){
        output_arr[units_count[arr[i].units]] = arr[i];
        units_count[arr[i].units]--;
    }
     // Przypisuje watrosc z tablicy wejsciowej do tablicy pomocniczej do miejsca na ktore wskazuje wartosc z tablicy dziesiatek;
    for(i = n - 1; i >= 0; i--){
        arr[tens_count[output_arr[i].tens]] = output_arr[i];
        tens_count[output_arr[i].tens]--;
    }

    delete [] units_count;
    delete [] tens_count;
    delete [] output_arr;
}

int main(){
    std::ios::sync_with_stdio(false);
    int n, cals;
    string name;
    cin >> n;
    Dish * arr = new Dish[n];

    for(int i = 0; i < n; i++){
        cin >> name >> cals;
        arr[i].Init(name, cals % n, cals / n); // Dodanie elementu do tablicy z obilczonymi jednosciami i dziesiatkami
    }

    sort(arr, n);

    for(int i = 0; i < n; i++){
        cout << arr[i].name << " ";
    }
    delete [] arr;
    return 0;
}