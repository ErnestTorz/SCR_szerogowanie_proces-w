

#include <iostream>
#include <string>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

// g++ linefeeder.cpp -o lf
// ./lf ./szer 6 2 2 <sched4.in
unsigned int czas = 0;
unsigned int obecny_kwant = 0;
struct proces
{
    double moment_zaladowania = INT_MAX;
    double czas_potrzebny_na_wyk = 0;
    double czas_odbytej_pracy = 0;
    double priorytet = INT_MAX;
    int numer = INT_MAX;
};

queue<proces> kolejkaprocesow;

///////////////////////////////////////////////////
///////////////////BOUBLE SORT/////////////////////
//////////////////////////////////////////////////
void swap(proces *xp, proces *yp)
{
    proces temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void swapint(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(proces *procesory, int *stan_procesorow, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            // cout<<"|" <<procesory[j].numer<< " > "    <<procesory[j+1].numer<<"|";
            if (procesory[j].numer > procesory[j + 1].numer)
            {
                swap(&procesory[j], &procesory[j + 1]);
                swapint(&stan_procesorow[j], &stan_procesorow[j + 1]);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////QUEUE SORT BY PRIRITY///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void insertMinToRear(queue<proces> &q, int min_index)
{
    proces min_val;
    int n = q.size();
    for (int i = 0; i < n; i++)
    {
        proces curr = q.front();
        q.pop();
        if (i != min_index)
            q.push(curr);
        else
            min_val = curr;
    }
    q.push(min_val);
}

int minIndex(queue<proces> &q, int sortedIndex)
{
    int min_index = -1;
    double min_val = INT_MAX;
    int n = q.size();
    for (int i = 0; i < n; i++) // popujemy wszysykie elementy na koniec przy okazji szukajac najmniejszego na coraz mniejszym zakresie, najmaniejszy element w danym zakresie bedzie wypchany na koniec
    {
        proces curr = q.front();
        q.pop();
        if (curr.priorytet < min_val && i <= sortedIndex)
        {
            min_index = i;
            min_val = curr.priorytet;
        }
        q.push(curr);
    }
    return min_index;
}

void sortQueueByPriority(queue<proces> &q)
{
    for (int i = 1; i <= q.size(); i++)
    {
        int min_index = minIndex(q, q.size() - i);
        insertMinToRear(q, min_index);
    }
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////SORT QUEUE BY FULL WORK TIME////////////////////////////
////////////////////////////////////////////////////////////////////////////

int minFULLWORKTIME(queue<proces> &q, int sortedIndex)
{
    int min_index = -1;
    double min_val = INT_MAX;
    int n = q.size();
    for (int i = 0; i < n; i++) // popujemy wszysykie elementy na koniec przy okazji szukajac najmniejszego na coraz mniejszym zakresie, najmaniejszy element w danym zakresie bedzie wypchany na koniec
    {
        proces curr = q.front();
        q.pop();
        if (curr.czas_potrzebny_na_wyk < min_val && i <= sortedIndex)
        {
            min_index = i;
            min_val = curr.czas_potrzebny_na_wyk;
        }
        q.push(curr);
    }
    return min_index;
}
void sortQueueByFULLWorkTIME(queue<proces> &q)
{
    for (int i = 1; i <= q.size(); i++)
    {
        int min_index = minFULLWORKTIME(q, q.size() - i);
        insertMinToRear(q, min_index);
    }
}
////////////////////////////////////////////////////////////////////////////
/////////////////////////SORT QUEUE BY REMAINING WORK TIME////////////////////////////
////////////////////////////////////////////////////////////////////////////
int minREMAININGWORKTIME(queue<proces> &q, int sortedIndex)
{
    int min_index = -1;
    double min_val = INT_MAX;
    int n = q.size();
    for (int i = 0; i < n; i++) // popujemy wszysykie elementy na koniec przy okazji szukajac najmniejszego na coraz mniejszym zakresie, najmaniejszy element w danym zakresie bedzie wypchany na koniec
    {
        proces curr = q.front();
        q.pop();
        if ((curr.czas_potrzebny_na_wyk - curr.czas_odbytej_pracy) < min_val && i <= sortedIndex)
        {
            min_index = i;
            min_val = curr.czas_potrzebny_na_wyk - curr.czas_odbytej_pracy;
        }
        q.push(curr);
    }
    return min_index;
}

void sortQueueByREMAININGWorkTIME(queue<proces> &q)
{
    for (int i = 1; i <= q.size(); i++)
    {
        int min_index = minREMAININGWORKTIME(q, q.size() - i);
        insertMinToRear(q, min_index);
    }
}
////////////////////////////////////////////////////////////////////////////
/////////////////////////SORT QUEUE BY COME////////////////////////////
////////////////////////////////////////////////////////////////////////////
int minCOMETIME(queue<proces> &q, int sortedIndex)
{
    int min_index = -1;
    double min_val = INT_MAX;
    int n = q.size();
    for (int i = 0; i < n; i++) // popujemy wszysykie elementy na koniec przy okazji szukajac najmniejszego na coraz mniejszym zakresie, najmaniejszy element w danym zakresie bedzie wypchany na koniec
    {
        proces curr = q.front();
        q.pop();
        if (curr.moment_zaladowania < min_val && i <= sortedIndex)
        {
            min_index = i;
            min_val = curr.moment_zaladowania;
        }
        q.push(curr);
    }
    return min_index;
}

void sortQueueByCOMETIME(queue<proces> &q)
{
    for (int i = 1; i <= q.size(); i++)
    {
        int min_index = minCOMETIME(q, q.size() - i);
        insertMinToRear(q, min_index);
    }
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////SORT QUEUE BY NUMBER////////////////////////////
////////////////////////////////////////////////////////////////////////////
int minNUMBER(queue<proces> &q, int sortedIndex)
{
    int min_index = -1;
    double min_val = INT_MAX;
    int n = q.size();
    for (int i = 0; i < n; i++) // popujemy wszysykie elementy na koniec przy okazji szukajac najmniejszego na coraz mniejszym zakresie, najmaniejszy element w danym zakresie bedzie wypchany na koniec
    {
        proces curr = q.front();
        q.pop();
        if (curr.numer < min_val && i <= sortedIndex)
        {
            min_index = i;
            min_val = curr.numer;
        }
        q.push(curr);
    }
    return min_index;
}

void sortQueueByNUMBER(queue<proces> &q)
{
    for (int i = 1; i <= q.size(); i++)
    {
        int min_index = minNUMBER(q, q.size() - i);
        insertMinToRear(q, min_index);
    }
}

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////PLANOWANIE/////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void planowanie(int strategia, int liczba_procesorow, int kwant_czasu, proces *procesory, int *stan_procesorow)
{
    cout << czas << " ";
    //FCFS
    if (strategia == 0)
    {
        sortQueueByNUMBER(kolejkaprocesow);
        sortQueueByCOMETIME(kolejkaprocesow);


        for (int i = 0; i < liczba_procesorow; i++)
        {

            if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
            {
                procesory[i] = kolejkaprocesow.front();
                kolejkaprocesow.pop();
                stan_procesorow[i] = 1;
            }

            if (stan_procesorow[i] != -1)
            {
                if (procesory[i].czas_odbytej_pracy == procesory[i].czas_potrzebny_na_wyk)
                {
                    stan_procesorow[i] = -1;
                    procesory[i].czas_odbytej_pracy = 0;
                    procesory[i].czas_potrzebny_na_wyk = 0;
                    procesory[i].moment_zaladowania = INT_MAX;
                    procesory[i].numer = INT_MAX;
                    procesory[i].priorytet = INT_MAX;
                    if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 1;
                    }
                }
            }
        }
        bubbleSort(procesory, stan_procesorow, liczba_procesorow);
        for (int i = 0; i < liczba_procesorow; i++)
        {
            if (stan_procesorow[i] != -1 && procesory[i].czas_odbytej_pracy < procesory[i].czas_potrzebny_na_wyk)
            {

                cout << procesory[i].numer << " ";
                procesory[i].czas_odbytej_pracy++;
            }
            if (stan_procesorow[i] == -1)
            {
                cout << "-1 ";
            }
        }
    }
    //SJF
    if (strategia == 1)
    {
        sortQueueByNUMBER(kolejkaprocesow);
        sortQueueByFULLWorkTIME(kolejkaprocesow);

        for (int i = 0; i < liczba_procesorow; i++)
        {

            if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
            {
                procesory[i] = kolejkaprocesow.front();
                kolejkaprocesow.pop();
                stan_procesorow[i] = 1;
            }

            if (stan_procesorow[i] != -1)
            {
                if (procesory[i].czas_odbytej_pracy == procesory[i].czas_potrzebny_na_wyk)
                {
                    stan_procesorow[i] = -1;
                    procesory[i].czas_odbytej_pracy = 0;
                    procesory[i].czas_potrzebny_na_wyk = 0;
                    procesory[i].moment_zaladowania = INT_MAX;
                    procesory[i].numer = INT_MAX;
                    procesory[i].priorytet = INT_MAX;
                    if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 1;
                    }
                }
            }
        }
        bubbleSort(procesory, stan_procesorow, liczba_procesorow);
        for (int i = 0; i < liczba_procesorow; i++)
        {
            if (stan_procesorow[i] != -1 && procesory[i].czas_odbytej_pracy < procesory[i].czas_potrzebny_na_wyk)
            {

                cout << procesory[i].numer << " ";
                procesory[i].czas_odbytej_pracy++;
            }
            if (stan_procesorow[i] == -1)
            {
                cout << "-1 ";
            }
        }
    }

    //SRTF
    if (strategia == 2)
    {   proces pom;
    //cout<<"|"<<kwant_czasu<<" ";
        sortQueueByNUMBER(kolejkaprocesow);
        sortQueueByREMAININGWorkTIME(kolejkaprocesow);
              for (int i = 0; i < liczba_procesorow; i++)
        {

            if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
            {   sortQueueByNUMBER(kolejkaprocesow);
                sortQueueByREMAININGWorkTIME(kolejkaprocesow);
                procesory[i] = kolejkaprocesow.front();
                kolejkaprocesow.pop();
                stan_procesorow[i] = 0;
            }
            if (stan_procesorow[i] == kwant_czasu)
            {   
                kolejkaprocesow.push(procesory[i]);
                stan_procesorow[i]=-1;
                procesory[i].czas_odbytej_pracy = 0;
                procesory[i].czas_potrzebny_na_wyk = 0;
                procesory[i].moment_zaladowania = INT_MAX;
                procesory[i].numer = INT_MAX;
                procesory[i].priorytet = INT_MAX;
                sortQueueByNUMBER(kolejkaprocesow);
                sortQueueByREMAININGWorkTIME(kolejkaprocesow);
                 if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {   
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 0;
                    }

            }
            
                if (stan_procesorow[i] != -1 &&(procesory[i].czas_odbytej_pracy == procesory[i].czas_potrzebny_na_wyk))
                { 
                    stan_procesorow[i] = -1;
                    procesory[i].czas_odbytej_pracy = 0;
                    procesory[i].czas_potrzebny_na_wyk = 0;
                    procesory[i].moment_zaladowania = INT_MAX;
                    procesory[i].numer = INT_MAX;
                    procesory[i].priorytet = INT_MAX;
                    if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {   sortQueueByNUMBER(kolejkaprocesow);
                        sortQueueByREMAININGWorkTIME(kolejkaprocesow);
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 0;
                    }
                }
            
        }

        bubbleSort(procesory, stan_procesorow, liczba_procesorow);
        for (int i = 0; i < liczba_procesorow; i++)
        {
            if (stan_procesorow[i] != -1 && procesory[i].czas_odbytej_pracy < procesory[i].czas_potrzebny_na_wyk)
            {

                cout << procesory[i].numer << " ";
                procesory[i].czas_odbytej_pracy++;
                stan_procesorow[i]++;
            }
            if (stan_procesorow[i] == -1)
            {
                cout << "-1 ";
            }
        }
    }
    //RR
    if(strategia==3){
     

        for (int i = 0; i < liczba_procesorow; i++)
        {

            if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
            {
                procesory[i] = kolejkaprocesow.front();
                kolejkaprocesow.pop();
                stan_procesorow[i] = 0;
            }
           
            
            

            if (stan_procesorow[i] != -1)
            {
                if (procesory[i].czas_odbytej_pracy == procesory[i].czas_potrzebny_na_wyk)
                {
                    stan_procesorow[i] = -1;
                    procesory[i].czas_odbytej_pracy = 0;
                    procesory[i].czas_potrzebny_na_wyk = 0;
                    procesory[i].moment_zaladowania = INT_MAX;
                    procesory[i].numer = INT_MAX;
                    procesory[i].priorytet = INT_MAX;
                    if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 0;
                    }
                }
            }
        }
                for (int i = 0; i < liczba_procesorow; i++)
        {
                   if (stan_procesorow[i] == kwant_czasu)
            {   if(procesory[i].czas_odbytej_pracy<procesory[i].czas_potrzebny_na_wyk){
                kolejkaprocesow.push(procesory[i]);
                }
                stan_procesorow[i]=-1;
                procesory[i].czas_odbytej_pracy = 0;
                procesory[i].czas_potrzebny_na_wyk = 0;
                procesory[i].moment_zaladowania = INT_MAX;
                procesory[i].numer = INT_MAX;
                procesory[i].priorytet = INT_MAX;
                 if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {   
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 0;
                    }

            }
        }
        bubbleSort(procesory, stan_procesorow, liczba_procesorow);
        for (int i = 0; i < liczba_procesorow; i++)
        {
 

            if (stan_procesorow[i] != -1 && procesory[i].czas_odbytej_pracy < procesory[i].czas_potrzebny_na_wyk)
            {

                cout <<procesory[i].numer<<" ";
                procesory[i].czas_odbytej_pracy++;
                 stan_procesorow[i]++;
            }
            if (stan_procesorow[i] == -1)
            {
                cout << "-1 ";
            }
            
        }

    }
    //priorytwtowe z wywlaszczaniem, te same priorytety FCFS
    
    if (strategia == 4)
    {   proces pom;
    
             sortQueueByNUMBER(kolejkaprocesow);
             sortQueueByCOMETIME(kolejkaprocesow);
             sortQueueByPriority(kolejkaprocesow);
              for (int i = 0; i < liczba_procesorow; i++)
        {

            if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
            {   
                sortQueueByNUMBER(kolejkaprocesow);
                sortQueueByCOMETIME(kolejkaprocesow);
                sortQueueByPriority(kolejkaprocesow);
                procesory[i] = kolejkaprocesow.front();
                kolejkaprocesow.pop();
                stan_procesorow[i] = 0;
            }
            if (stan_procesorow[i] == kwant_czasu)
            {   
                kolejkaprocesow.push(procesory[i]);
                stan_procesorow[i]=-1;
                procesory[i].czas_odbytej_pracy = 0;
                procesory[i].czas_potrzebny_na_wyk = 0;
                procesory[i].moment_zaladowania = INT_MAX;
                procesory[i].numer = INT_MAX;
                procesory[i].priorytet = INT_MAX;
                sortQueueByNUMBER(kolejkaprocesow);
                sortQueueByCOMETIME(kolejkaprocesow);
                sortQueueByPriority(kolejkaprocesow);
                 if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {   
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 0;
                    }

            }
            
                if (stan_procesorow[i] != -1 &&(procesory[i].czas_odbytej_pracy == procesory[i].czas_potrzebny_na_wyk))
                { 
                    stan_procesorow[i] = -1;
                    procesory[i].czas_odbytej_pracy = 0;
                    procesory[i].czas_potrzebny_na_wyk = 0;
                    procesory[i].moment_zaladowania = INT_MAX;
                    procesory[i].numer = INT_MAX;
                    procesory[i].priorytet = INT_MAX;
                    if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {   
                        sortQueueByNUMBER(kolejkaprocesow);
                        sortQueueByCOMETIME(kolejkaprocesow);
                        sortQueueByPriority(kolejkaprocesow);
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 0;
                    }
                }
            
        }

        bubbleSort(procesory, stan_procesorow, liczba_procesorow);
        for (int i = 0; i < liczba_procesorow; i++)
        {
            if (stan_procesorow[i] != -1 && procesory[i].czas_odbytej_pracy < procesory[i].czas_potrzebny_na_wyk)
            {

                cout << procesory[i].numer << " ";
                procesory[i].czas_odbytej_pracy++;
                stan_procesorow[i]++;
            }
            if (stan_procesorow[i] == -1)
            {
                cout << "-1 ";
            }
        }
    }

    //priorytetowe z wywlaszczaniem, te same priorytety SRTF

    if (strategia == 5)
    {   proces pom;
    
             sortQueueByNUMBER(kolejkaprocesow);
             sortQueueByREMAININGWorkTIME(kolejkaprocesow);
             sortQueueByPriority(kolejkaprocesow);
              for (int i = 0; i < liczba_procesorow; i++)
        {

            if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
            {   
                sortQueueByNUMBER(kolejkaprocesow);
                sortQueueByREMAININGWorkTIME(kolejkaprocesow);
                sortQueueByPriority(kolejkaprocesow);
                procesory[i] = kolejkaprocesow.front();
                kolejkaprocesow.pop();
                stan_procesorow[i] = 0;
            }
            if (stan_procesorow[i] == kwant_czasu)
            {   
                kolejkaprocesow.push(procesory[i]);
                stan_procesorow[i]=-1;
                procesory[i].czas_odbytej_pracy = 0;
                procesory[i].czas_potrzebny_na_wyk = 0;
                procesory[i].moment_zaladowania = INT_MAX;
                procesory[i].numer = INT_MAX;
                procesory[i].priorytet = INT_MAX;
                sortQueueByNUMBER(kolejkaprocesow);
                sortQueueByREMAININGWorkTIME(kolejkaprocesow);
                sortQueueByPriority(kolejkaprocesow);
                 if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {   
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 0;
                    }

            }
            
                if (stan_procesorow[i] != -1 &&(procesory[i].czas_odbytej_pracy == procesory[i].czas_potrzebny_na_wyk))
                { 
                    stan_procesorow[i] = -1;
                    procesory[i].czas_odbytej_pracy = 0;
                    procesory[i].czas_potrzebny_na_wyk = 0;
                    procesory[i].moment_zaladowania = INT_MAX;
                    procesory[i].numer = INT_MAX;
                    procesory[i].priorytet = INT_MAX;
                    if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {   
                        sortQueueByNUMBER(kolejkaprocesow);
                        sortQueueByREMAININGWorkTIME(kolejkaprocesow);
                        sortQueueByPriority(kolejkaprocesow);
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 0;
                    }
                }
            
        }

        bubbleSort(procesory, stan_procesorow, liczba_procesorow);
        for (int i = 0; i < liczba_procesorow; i++)
        {
            if (stan_procesorow[i] != -1 && procesory[i].czas_odbytej_pracy < procesory[i].czas_potrzebny_na_wyk)
            {

                cout << procesory[i].numer << " ";
                procesory[i].czas_odbytej_pracy++;
                stan_procesorow[i]++;
            }
            if (stan_procesorow[i] == -1)
            {
                cout << "-1 ";
            }
        }
    }
    
    //priorytetyowa bez wywlaszczen, te same priorytety FCFS
     if (strategia == 6)
    {           sortQueueByNUMBER(kolejkaprocesow);
                sortQueueByCOMETIME(kolejkaprocesow);
                sortQueueByPriority(kolejkaprocesow);

        for (int i = 0; i < liczba_procesorow; i++)
        {

            if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
            {
                procesory[i] = kolejkaprocesow.front();
                kolejkaprocesow.pop();
                stan_procesorow[i] = 1;
            }

            if (stan_procesorow[i] != -1)
            {
                if (procesory[i].czas_odbytej_pracy == procesory[i].czas_potrzebny_na_wyk)
                {
                    stan_procesorow[i] = -1;
                    procesory[i].czas_odbytej_pracy = 0;
                    procesory[i].czas_potrzebny_na_wyk = 0;
                    procesory[i].moment_zaladowania = INT_MAX;
                    procesory[i].numer = INT_MAX;
                    procesory[i].priorytet = INT_MAX;
                    if (stan_procesorow[i] == -1 && !kolejkaprocesow.empty())
                    {
                        procesory[i] = kolejkaprocesow.front();
                        kolejkaprocesow.pop();
                        stan_procesorow[i] = 1;
                    }
                }
            }
        }
        bubbleSort(procesory, stan_procesorow, liczba_procesorow);
        for (int i = 0; i < liczba_procesorow; i++)
        {
            if (stan_procesorow[i] != -1 && procesory[i].czas_odbytej_pracy < procesory[i].czas_potrzebny_na_wyk)
            {

                cout << procesory[i].numer << " ";
                procesory[i].czas_odbytej_pracy++;
            }
            if (stan_procesorow[i] == -1)
            {
                cout << "-1 ";
            }
        }
    }
        
    
    
    if (strategia == 7)
    {

        proces pom;
        int dlugosc = kolejkaprocesow.size();

        for (int i = 0; i < dlugosc; i++)
        {
            cout << kolejkaprocesow.front().numer << "_" << kolejkaprocesow.front().priorytet << " ";
            pom = kolejkaprocesow.front();
            kolejkaprocesow.pop();
            kolejkaprocesow.push(pom);
        }
        cout << "                       ";
        sortQueueByPriority(kolejkaprocesow);
        for (int i = 0; i < dlugosc; i++)
        {
            cout << kolejkaprocesow.front().numer << "_" << kolejkaprocesow.front().priorytet << " ";
            pom = kolejkaprocesow.front();
            kolejkaprocesow.pop();
            kolejkaprocesow.push(pom);
        }
    }


    cout << endl;
    czas++;
    obecny_kwant++;
}

int main(int argc, char **argv)
{
    string token;
    proces pom;
    int strategia = 0;
    int liczba_procesorow = 1;
    int kwant_czasu = 1; //dla strategi z wywlaszczaniem

    if (argc == 2)
    {
        strategia = atoi(argv[1]);
    }
    else if (argc == 3)
    {
        strategia = atoi(argv[1]);
        liczba_procesorow = atoi(argv[2]);
    }
    else if (argc == 4)
    {
        strategia = atoi(argv[1]);
        liczba_procesorow = atoi(argv[2]);
        kwant_czasu = atoi(argv[3]);
    }
    else
    {
        cout << "BLAD WYWOLANIA, POPRAWNA FORMA ./a.out strategia l_procesorow kwant_czasu" << endl;
        return 1;
    }

    proces *procesory = new proces[liczba_procesorow];
    int *stan_procesorow = new int[liczba_procesorow];
    for (int i = 0; i < liczba_procesorow; i++)
    {
        stan_procesorow[i] = -1;
    }

    for (string dane; getline(cin, dane);)
    {
        stringstream iss(dane);
        iss >> token;
        pom.moment_zaladowania = stod(token);
        while (iss >> token)
        {
            pom.numer = stod(token);

            iss >> token;
            pom.priorytet = stod(token);

            iss >> token;
            pom.czas_potrzebny_na_wyk = stod(token);

            kolejkaprocesow.push(pom);
        }

        planowanie(strategia, liczba_procesorow, kwant_czasu, procesory, stan_procesorow);
    }


    return 0;
}