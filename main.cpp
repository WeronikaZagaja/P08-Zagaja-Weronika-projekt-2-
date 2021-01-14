// biblioteki
#include <iostream>
#include <fstream>
#include <time.h>
#include<cstdlib>
#include <iomanip>
#include <windows.h>
using namespace std;

//deklaracja czasu
clock_t start, stop;
double czas;

// deklaracja zmiennych
const int N=100;
const int WMIN = 0;
const int WMAX = N;
int d[N];
int d2[N];

void losowe() //implementacja funcji do losowania liczb
{
    fstream output("wylosowane liczby.txt", ios::out);

    // Najpierw wypelniamy tablice d[] liczbami pseudolosowymi
    srand(time(NULL));
    cout<<"Przed sortowaniem: "<<endl;
    output<<"Przed sortowaniem: "<<endl;
    for(int i=0; i<N; i++)
    {
        d[i] = WMIN + rand() % (WMAX - WMIN + 1);
        cout  << d[i]<<" ";
        output << d[i]<<" ";
    }
    cout << endl;

    //przepisanie tablicy d[]
    for(int i=0; i<N; i++)
    {
        d2[i] = WMIN + rand() % (WMAX - WMIN + 1);
    }
    for(int i=0; i<N; i++)
    {
        d2[i]=d[i];
    }

    output.close();
}

void  Insertion_Sort( int *D, int N) //implementacja funcji do sortowania przez wstawianie
{
    //sortujemy przez wstawianie
    int j, i, x;
    {
        for(j = N - 2; j >= 0; j--)
        {
            x = D[j];
            i = j + 1;
            while((i < N) && (x > D[i]))
            {
                D[i - 1] = D[i];
                i++;
            }
            D[i - 1] = x;
        }

    }

}
void bucket_sort(int *D2, int WMIN, int WMAX) //implementacja funkcji do sortownia kubelkowego
{
    // stworzenie wskaznika
    int *lw;
    lw = new int [WMAX - WMIN + 1];
    int i,j;
    {
        // sortujemy kubelkowo

        for(i = WMIN; i <= WMAX; i++) lw[i - WMIN] = 0;
        for(i = 0; i < N; i++) lw[D2[i] - WMIN]++;
        j = 0;
        for(i = WMIN; i <= WMAX; i++) while(lw[i - WMIN]--) D2[j++] = i;
    }
    delete [] lw;
    cout<<endl;
}

void Sort(string inputFile) //funkcja umozliwiajaca sortowanie dla ciagow
                            //opytymistycznych pesymistycznych i oczekiwanych
{
    fstream output("wyniki sortowania.txt",ios::out);
    if(inputFile != "expected")
    {
        int x;
        fstream input(inputFile, ios::in);

        cout << "Przed sortowaniem:" << endl;
        output << "Przed sortowaniem:" << endl;
        int i=0;
        while (input >> x)      // zczytuje posortowane liczby z pliku "optimistyczne.txt"
        {
            d[i] = x;
            cout  << d[i]<<" ";
            output << d[i]<<" ";
            i++;
        }
        cout << endl;
        output << endl;

        input.close();
    }
    else
    {
        losowe();   //wywoluje funkcje "losowoe"
    }
    cout<<endl;
    //liczymy czas sortowania przez wstawianie
    start = clock();
    Insertion_Sort(d, N);

    output<<endl;
    stop = clock();
    czas = (double)(stop-start)/(CLOCKS_PER_SEC/1000); // zliczamy czas w milisekundach

//wypisywanie posortowanej tablicy
    cout << "Po sortowaniu Insertion Sort :" << endl;
       for(int i = 0; i < N; i++){ cout << d[i]<<" ";}
    output << "Po sortowaniu Insertion Sort :" << endl;
       for(int i = 0; i < N; i++) output << d[i]<<" ";
    output<<endl<<endl;

    cout<<endl;

    cout << "Czas sortowania Insertion Sort : " << czas << " msec" << endl;
    cout<<endl;

    //liczymy czas sortowania kubelkowego
    start=clock();
    bucket_sort(d2, WMIN, WMAX);
    stop = clock();
    czas = (double)(stop-start)/(CLOCKS_PER_SEC/1000);

    cout << "Po sortowaniu bucket_sort: "<<endl;
          for(int i = 0; i < N; i++) {cout <<  d[i]<<" ";}
    output<< "Po sortowaniu bucket_sort: ";
          for(int i = 0; i < N; i++) output << d[i]<<" ";
    cout<<endl;

    cout << "Czas sortowania bucket_sort: " << czas << " msec" << endl << endl;
    output.close();
}

int main()
{
    int wybor = 0;
    cout << "1 - optimistic" << endl;
    cout << "2 - pessimistic" << endl;
    cout << "3 - expected" << endl;
    cin >> wybor;

    switch(wybor) //pozwala wybrac plik do sortowania
    {
    case 1:
        cout << "sorting optimistic case..." << endl;
        Sort("optymistyczne.txt");
        break;
    case 2:
        cout << "sorting pessimistic case..." << endl;
        Sort("pesymistyczne.txt");
        break;
    case 3:
        cout << "sorting random set of numbers..." << endl;
        Sort("expected");
        break;
    }
    return 0;
}
