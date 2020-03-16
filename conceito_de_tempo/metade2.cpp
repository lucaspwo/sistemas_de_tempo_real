#include <time.h>  // time()
#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h>  // para: sleep()
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

void carga(int k){
  float f = 0.999999;
  for(int i=0; i<k; i++)
    {
      f = f*f*f*f*f;
      f = 1.56;
        for(int j=0; j<k; j++)
           {
	     f = sin(f)*sin(f)*f*f*f;

            }
    }

}

long double cont;
long double freq;
bool pausa = false;

int main( ){
  ifstream read;
  read.open("/proc/cpuinfo");
  string sLine = "";
  string delimiter = ": ";
  int line_no = 0;
  while (line_no != 8 && getline(read, sLine)) {
    ++line_no;
  }
  if (line_no == 8) {
    //cout << sLine;
    freq =  stoi(sLine.substr(sLine.find(delimiter)+2));
    freq = freq*1000000;
    cout << "Frequencia do processador (Hz): " << freq << '\n';
    // sLine contains the second line in the file.
  } /**else {
    // The file contains fewer than two lines.
  }**/

  while(1){
    while(cont < freq){
      //  clock_t time_1, time_2;
      //  time_t  real_time_1, real_time_2, delta_real_time;

      //  int saida;
      //  double saida2;

      //  time_1 = clock();
      //  real_time_1 = time(0);
      //carga(1000);
      //sleep(((CLOCKS_PER_SEC/60)/2)/10000);
      //  real_time_2 = time(0);
      //  time_2 = clock();

      //  saida = (int) (time_2) - (time_1);
      //  saida2 = (double) ((saida) / (double) CLOCKS_PER_SEC) ;

      //  delta_real_time = (real_time_2) - (real_time_1);

      //  printf("\n Tempo de uso da CPU em microsegundos: %d \n", saida);
      //  printf(" Tempo de uso da CPU em segundos: %f \n", saida2);

      //  printf(" Tempo Real decorrido em microsegundos: %d \n", (int) delta_real_time);

      //  printf("\n Qual é a diferença entre as funções clock( ) e time( )? \n\n");
        if(pausa == false){
            carga(100);
            cont++;
            pausa = true;
        } else{
            cont++;
            pausa = false;
        }
    }
    pausa = false;
    cont = 0;
  }
  //sleep(1);
  //cout << CLOCKS_PER_SEC;
  exit(1);
}