#include <stdio.h>


int main(int argc, char **argv) {
  int i;
  double m;
  double c;
  double x;
  double y;
  
  if(argc != 3) {
    fprintf(stderr, "You need to specify a slope and intercept\n");
    return 1;
  }

  sscanf(argv[1], "%lf", &m);
  sscanf(argv[2], "%lf", &c);

  for(i=0; i<100; i++) {
    x = i;
    y = (m * x) + c;
    printf("%0.2lf,%0.2lf\n", x, y);
  }
  
  return 0;
}

