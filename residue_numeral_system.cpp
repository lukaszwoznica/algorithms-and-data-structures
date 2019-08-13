#include <iostream>

using namespace std;

int * base, *num1, *num2;
int n, dec_num2;

// Funkcja do odwrocenia elementu korzystajac z rozszerzonego algorytmu Euklidesa
int modInverse(int num, int base){
    int m0 = base;
    int y = 0;
    int x = 1;

    if (base == 1)
      return 0;

    while (num > 1){
        int q = num / base;
        int t = base;

        base = num % base;
        num = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
       x += m0;

    return x;
}

void add(){
    for(int i = 0; i < n; i++){
        num1[i] = (num1[i] + num2[i]) % base[i];
    }
}

void sub(){
    for(int i = 0; i < n; i++){
        if(num1[i] - num2[i] < 0)
            num1[i] = ((num1[i] - num2[i]) + base[i]) % base[i];
        else
            num1[i] = (num1[i] - num2[i]) % base[i];
    }
}

void mul(){
    for(int i = 0; i < n; i++){
        num1[i] = num1[i] * num2[i] % base[i];
    }
}

void div(){
    for(int i = 0; i < n; i++){
        num1[i] = num1[i] * modInverse(num2[i], base[i]) % base[i];
    }
}


void pow(int exponent){
    for(int i = 0; i < n; i++){
        if(num1[i] == 1) // 1 do jakiejkolwiek potegi to 1
            continue;
        for(int j = 0; j < exponent -1; j++){  // wykładnik -1 bo mnozymy od num^1
            num1[i] = (num1[i] * num2[i]) % base[i];
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    int m;
    char oper;
    cin >> n >> m;
    base = new int[n];
    num1 = new int[n];
    num2 = new int[n];
    for(int i = 0; i < n; i++)
        cin >> base[i];

    for(int i = 0; i < n; i++){
        cin >> num1[i];
    }

    for(int i = 0; i < m; i++){
        cin >> oper >> dec_num2;

        // Zamiana liczby na system resztowy
        for(int i = 0; i < n; i++){
            num2[i] = dec_num2 % base[i];
        }

        switch(oper){
            case '+':
                add();
                break;

            case '-':
                sub();
                break;

            case '*':
                mul();
                break;

            case '/':
                div();
                break;

            case '^':
                for(int j = 0; j < n; j++) // kopiuje num1 do num2, num2 sie nie zmienia i num1 jest mnozone przez num2 odpowiednia liczbe razy
                    num2[j] = num1[j];
                pow(dec_num2);
                break;

            default:
                break;
        }
    }

    for(int i =0; i < n; i++){
        cout << num1[i] << " ";
    }

    delete [] num1;
    delete [] num2;
    delete [] base;
    return 0;
}