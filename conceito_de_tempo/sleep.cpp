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
  time_t tempo_real1;
  time_t tempo_real2;
  tempo_real1 = time((time_t *) 0);
  double x = 1;
  // while(1);
  // sleep(10);
  for(int i=0; i<10; i++) {
    sleep(i);
   
  }
  tempo_real2 = time((time_t *) 0);
  // cout << "teste" <<'\n';
  cout << "duracao: " << tempo_real2-tempo_real1 << " segundos" <<'\n';
  return(0);
}

