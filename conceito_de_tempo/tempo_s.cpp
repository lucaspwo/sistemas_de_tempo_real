/////\// UFRN-CT-DCA
// Disciplina: Sistemas Operacionais
// Programa: sleep.c


#include <iostream> // para: cout
#include <stdio.h>
#include <time.h>
#include <unistd.h> // para: sleep()


using std::cout;

//using namespace std;


int main ( )
{
  time_t tempo_real;
  
  int numero;

//   tempo_real = time( (time_t *) 0);

  time_t tempo_real1;
  time_t tempo_real2;
  tempo_real1 = time((time_t *) 0);
//   double x = 1;
  // while(1);
  // sleep(10);
  for(int i=0; i<6; i++) {
    sleep(i);
    tempo_real = time( (time_t *) 0);
    cout << "Já se passaram  " << tempo_real << " segundos desde 0:00:00 de 01/01/1970 " << '\n';
  }
  tempo_real2 = time((time_t *) 0);
  // cout << "teste" <<'\n';
  cout << "duracao: " << tempo_real2-tempo_real1 << " segundos" <<'\n';
  return(0);
}

