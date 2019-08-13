#include <iostream>

using namespace std;

class  List{
private:
    struct element{
        element * next, *prev;
        int value;
    };
    element * first, * last;
    unsigned int counter;
public:
    List();
    ~List();
    bool empty();            // Sprawdza czy lista jest pusta
    int front();                 // Pierwszy element
    int back();                 // Ostatni element
    void push_front(int);  // Wstaw na poczatek listy
    void push_back(int);  // Wstaw na koniec listy
    void pop_front();       // Usun pierwszy element
    void pop_back();      // Usun ostatni element
    void show_values();  // Wyswietl wszystkie wartosci z listy
};

// Konstruktor
List::List(){
    first = NULL;
    last = NULL;
    counter  = 0;
}

// Destruktor
List::~List(){
    element * p;
    while(first){
        p = first->next;
        delete first;
        first = p;
    }
}

bool List::empty(){
    if (counter == 0)
        return  true;
    else
        return  false;
}

int List::front(){
    return  first->value;
}

int List::back (){
    return  last->value;
}



void List::push_front(int val){
    element * p = new element;
    p->next = first;
    p->prev = NULL;
    p->value = val;
    if(first)
        first->prev = p;
    first = p;
    if(!last)
        last = first;
    counter++;
}


void List::push_back(int val){
    element * p = new element;
    if(last)
        last->next = p;
    p->next = NULL;
    p->prev = last;
    p->value = val;
    last = p;
    if(!first)
        first = last;
    counter++;
}


void List::pop_front(){
    element * p;
    if(first){
        p = first;
        first = first->next;
        if(!first)
            last = NULL;
        else
            first->prev = NULL;
        counter--;
        delete p;
    }
}


void List::pop_back(){
    element * p;
    if(last){
        p = last;
        if(p == first)
            first = last = NULL;
        else{
          last = last->prev;
          last->next = NULL;
        };
        counter--;
        delete p;
    }
}

void List::show_values(){
    element * p;
    p = first;
    while(p){
      cout << p->value << " ";
      p = p->next;
    }
}

int main(){
    List l_hand, r_hand;
    int balls_num, steps, balls_drop, change_num;

    // Wczytywanie danych
    cin >> balls_num >> steps >> balls_drop;
    int * drop_steps = new int[balls_drop];
    for(int i = 0; i < balls_drop; i++)
        cin >> drop_steps[i];
    cin >> change_num;
    int * change_steps = new int[change_num];
    for(int i = 0; i < change_num; i++)
        cin >> change_steps[i];

    // Poczatkowe rozmieszczenie pileczek w dloniach
    for(int i = 1; i <= balls_num; i++){
        if(balls_num%2 != 0){
            if(i <= (balls_num/2) + 1)
                l_hand.push_back(i);
            else
                r_hand.push_back(i);
        }
        else{
            if(i <= balls_num/2)
                l_hand.push_back(i);
           else
                r_hand.push_back(i);
        }
    }

    // Kroki
    int temp;
    bool is_left_throw = true;
    bool is_ball_drop = false;
    int j_ds = 0, j_cs = 0;
    for(int i = 1; i <= steps; i++){

        //Kroki nieparzyste - wyrzucanie pilek
        if(i%2 != 0){
            //Sprawdzenie czy wystepuje zmiana reki
            for(int j = j_cs; j < change_num; j++){
                if(i == change_steps[j]){
                    is_left_throw = !is_left_throw;
                    j_cs++;
                    break;
                }
            }
            // Wyrzut z lewej
            if(is_left_throw && !l_hand.empty()){
                temp = l_hand.back();
                l_hand.pop_back();
            }
            // Wyrzut z prawej
            else if(!r_hand.empty()){
                temp = r_hand.front();
                r_hand.pop_front();
            }
            is_left_throw = !is_left_throw;
        }

        //Kroki parzyste - lapanie lub upuszczanie pilek
        else{
            // Sprawdzenie czy pilka zostaje upuszczona
            for(int j = j_ds; j < balls_drop; j++){
                if(i == drop_steps[j]){
                    is_ball_drop = true;
                    j_ds++;
                    break;
                }
            }

        if(!is_ball_drop){
            // Lapanie do prawej
            if(!is_left_throw ){
                r_hand.push_back(temp);
            }

            //Lapanie do lewej
            else{
                l_hand.push_front(temp);
            }
          }
          is_ball_drop = false;
        }
    }

    // Wynik
    l_hand.show_values();
    r_hand.show_values();
    delete [] drop_steps;
    delete [] change_steps;
    return 0;
}