#include <mpi.h>
#include <stdio.h>


int main(int argc, char **argv) {
  int aashra;
  double m;
  double c;
  double p;
  double q;
  
  if(argc != 3) {
    fprintf(stderr, "You need to specify a slope and intercept\n");
    return 1;
  }

  sscanf(argv[1], "%lf", &m);
  sscanf(argv[2], "%lf", &c);

  for(aashra=0; aashra<100; aashra++) {
    p = aashra;
    q = (m * p) + c;
    printf("%0.2lf,%0.2lf\n", p, q);
  }
  
  return 0;
}

