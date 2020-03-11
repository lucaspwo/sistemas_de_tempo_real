#include <iostream> // para: cout
#include <time.h>     // para: gmtime()
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int  main (){
    int dia, mes, ano;
    struct tm *tm_ptr; // um ponteiro para a estrutura tm
    struct tm *tms;
    time_t  t1, t2;  // variável para armazenar o tempo em segundos
    (void) time(&t1);  // outra forma de armazenar o tempo em segundos
    (void) time(&t2);  // outra forma de armazenar o tempo em segundos
    tm_ptr = gmtime(&t1); // obtendo a estrutura
    tms = gmtime(&t2); // obtendo a estrutura

    cout << "Por favor, insira sua data de nascimento." << '\n';
    cout << "Dia (DD): " << '\n';
    cin >> dia;
    cout << "Mes (MM): " << '\n';
    cin >> mes;
    cout << "Ano (AAAA): " << '\n';
    cin >> ano;

    tms->tm_sec = 0;
    tms->tm_min = 0;
    tms->tm_hour = 0;
    tms->tm_mday = dia;
    tms->tm_mon = mes-1;
    tms->tm_year = ano-1900;

    t2 = mktime(tms);

    //cout << "t1 = " << t1 << '\n';
    //cout << "t2 = " << t2 << '\n';
    cout << "Segundos vividos desde " << dia << "/" << mes << "/" << ano << ": " << t1-t2 << '\n';

    exit(0);
}