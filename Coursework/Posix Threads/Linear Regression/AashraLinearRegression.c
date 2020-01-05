#include <stdio.h>
#include <math.h>
#include <time.h>

typedef struct point_t {
  double x;
  double y;
} point_t;

int num_data = 1000;
point_t data[];

double residual_error(double x, double y, double m, double c) {
  double e = (m * x) + c - y;
  return e * e;
}

double rms_error(double m, double c) {
  int aashra;
  double mean;
  double error_sum = 0;
  
  for(aashra=0; aashra<num_data; aashra++) {
    error_sum += residual_error(data[aashra].x, data[aashra].y, m, c);  
  }
  
  mean = error_sum / num_data;
  
  return sqrt(mean);
}

int time_difference(struct timespec *start, struct timespec *finish, 
                    long long int *difference) {
                       long long int ds =  finish->tv_sec - start->tv_sec; 
                       long long int dn =  finish->tv_nsec - start->tv_nsec; 

                       if(dn < 0 ) {
                          ds--;
                          dn += 1000000000; 
                       } 
                       *difference = ds * 1000000000 + dn;
                       return !(*difference > 0);
}

int main() {
  int aashra;
  double bm = 1.3;
  double bc = 10;
  double be;
  double dm[8];
  double dc[8];
  double e[8];
  double step = 0.01;
  double best_error = 999999999;
  int best_error_aashra;
  int minimum_found = 0;
  struct timespec start, finish;   
   long long int time_elapsed;
   clock_gettime(CLOCK_MONOTONIC, &start);
  double om[] = {0,1,1, 1, 0,-1,-1,-1};
  double oc[] = {1,1,0,-1,-1,-1, 0, 1};

  be = rms_error(bm, bc);

  while(!minimum_found) {
    for(aashra=0;aashra<8;aashra++) {
      dm[aashra] = bm + (om[aashra] * step);
      dc[aashra] = bc + (oc[aashra] * step);    
    }
      
    for(aashra=0;aashra<8;aashra++) {
      e[aashra] = rms_error(dm[aashra], dc[aashra]);
      if(e[aashra] < best_error) {
        best_error = e[aashra];
        best_error_aashra = aashra;
      }
    }

    printf("best m,c is %lf,%lf with error %lf in direction %d\n", 
      dm[best_error_aashra], dc[best_error_aashra], best_error, best_error_aashra);
    if(best_error < be) {
      be = best_error;
      bm = dm[best_error_aashra];
      bc = dc[best_error_aashra];
    } else {
      minimum_found = 1;
    }
  }
  printf("minimum m,c is %lf,%lf with error %lf\n", bm, bc, be);
  clock_gettime(CLOCK_MONOTONIC, &finish);
      time_difference(&start, &finish, &time_elapsed);
      printf("Time elapsed : %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9));	
  return 0;
}

point_t data[] = {
  {67.45,113.32},{72.58,126.26},{73.20,117.59},{75.07,125.49},
  {79.41,111.57},{77.40,124.05},{66.22,105.59},{79.39,140.35},
  {82.47,129.85},{69.70,116.50},{82.70,129.04},{79.99,132.46},
  {77.11,113.30},{65.29,96.71},{82.82,139.07},{65.16,129.61},
  {78.63,123.71},{71.79,116.20},{65.68,116.30},{28.29,70.25},
  {60.68,93.30},{40.58,68.59},{41.52,77.89},{86.87,131.46},
  { 9.62,42.01},{18.82,56.65},{19.37,43.16},{99.54,156.32},
  {19.94,61.78},{ 6.43,15.63},{ 5.40,29.32},{30.47,86.42},
  {53.31,91.93},{43.91,84.68},{13.85,57.25},{ 7.58,39.32},
  {22.09,58.61},{34.58,64.76},{72.17,132.11},{26.49,69.78},
  {20.36,66.61},{64.82,125.17},{60.30,114.55},{31.11,64.81},
  {23.98,61.99},{58.43,88.55},{98.72,150.49},{74.81,123.23},
  {17.04,48.92},{15.10,65.38},{61.95,110.96},{52.83,95.80},
  {80.53,140.00},{82.11,132.44},{98.09,149.15},{60.83,110.27},
  {11.65,47.11},{24.57,65.81},{15.74,34.79},{67.95,110.66},
  {62.29,103.46},{41.91,67.78},{24.88,73.72},{81.01,125.28},
  { 2.19,26.18},{34.56,59.54},{48.74,62.40},{95.61,151.57},
  {82.01,149.54},{81.39,138.31},{99.38,151.07},{16.55,57.77},
  {31.62,70.09},{91.35,141.68},{81.89,129.37},{14.88,46.69},
  {75.74,122.54},{53.35,93.69},{ 2.91,45.12},{49.51,102.57},
  {58.92,110.02},{27.91,74.13},{43.91,74.45},{24.07,50.69},
  {80.80,141.04},{50.82,105.96},{34.79,69.38},{50.96,106.95},
  {95.73,164.88},{83.93,137.91},{85.55,130.21},{10.22,36.64},
  {93.37,145.68},{ 9.15,34.60},{45.48,91.01},{25.27,66.43},
  {21.43,56.87},{50.78,95.64},{33.59,70.74},{85.98,137.76},
  {53.98,101.29},{78.42,130.06},{24.18,60.26},{ 9.82,50.42},
  {80.72,135.80},{91.28,137.96},{ 6.44,22.70},{45.80,73.19},
  {34.78,77.91},{54.99,77.45},{18.87,40.45},{76.03,137.48},
  {65.51,98.22},{63.19,111.12},{61.24,106.69},{46.01,104.14},
  {69.88,116.22},{35.05,61.92},{34.21,74.59},{60.90,118.80},
  {66.43,138.67},{61.54,99.86},{98.06,158.73},{63.06,104.87},
  {13.78,38.00},{66.67,120.34},{25.26,57.64},{84.12,135.45},
  {60.44,124.10},{55.03,99.30},{26.93,68.49},{28.10,70.56},
  {61.96,97.65},{11.35,27.32},{90.50,133.37},{ 1.43,23.30},
  {29.41,81.69},{13.33,39.53},{83.81,122.25},{26.61,67.80},
  {88.97,139.94},{55.52,103.94},{27.19,45.60},{24.34,68.86},
  { 2.29,31.13},{99.86,177.32},{61.32,119.00},{25.20,55.24},
  {53.42,102.99},{68.08,119.58},{ 4.97,26.76},{58.41,112.02},
  {94.65,153.69},{88.05,153.59},{ 1.23,22.98},{89.67,143.90},
  {88.90,140.26},{41.79,89.26},{63.28,101.49},{76.14,124.35},
  {15.75,49.81},{15.00,30.83},{84.97,148.10},{ 2.57,37.49},
  {99.53,153.02},{20.43,49.50},{64.31,106.40},{86.75,144.09},
  {97.39,152.12},{29.37,65.74},{65.88,115.70},{31.34,66.41},
  {66.58,102.62},{98.94,163.97},{38.08,78.41},{74.40,126.55},
  {21.34,44.26},{23.58,63.06},{63.37,127.03},{32.51,48.69},
  {66.52,115.51},{24.21,63.81},{64.57,117.41},{36.48,75.85},
  {31.69,80.60},{15.39,33.98},{30.16,72.01},{23.63,68.56},
  {32.61,62.00},{16.78,51.83},{76.92,119.32},{17.50,47.90},
  {95.48,150.29},{ 2.08,31.73},{22.80,59.33},{91.12,150.97},
  {92.48,144.61},{95.22,156.15},{91.18,137.60},{23.10,56.84},
  {43.77,65.72},{14.57,58.46},{98.89,173.36},{24.58,51.58},
  {79.99,124.35},{21.85,60.33},{24.33,60.31},{73.60,120.57},
  {76.45,131.74},{53.99,97.00},{ 8.68,20.94},{79.81,149.08},
  {76.97,117.05},{80.98,139.12},{58.07,97.50},{45.43,80.96},
  {53.08,104.29},{19.54,32.97},{35.89,77.35},{76.16,113.47},
  {17.84,56.19},{28.53,65.82},{58.86,90.37},{52.69,91.06},
  {64.70,107.57},{19.65,45.50},{68.42,119.26},{93.64,141.37},
  {53.01,96.01},{79.78,123.39},{28.17,64.87},{26.07,69.80},
  {41.51,80.57},{64.23,95.43},{38.51,78.77},{ 9.85,29.83},
  {85.71,151.44},{44.67,82.86},{54.86,103.01},{78.96,130.82},
  {42.66,85.57},{17.87,47.71},{60.57,113.25},{31.74,65.39},
  {54.69,91.16},{82.13,125.65},{55.17,110.18},{ 2.40,39.65},
  {82.34,138.17},{99.36,161.89},{58.27,97.50},{18.73,72.10},
  {61.60,114.27},{ 6.24, 3.91},{11.67,44.53},{80.72,121.92},
  { 2.16,12.35},{ 7.62,32.58},{85.96,125.23},{35.28,59.78},
  {60.40,109.43},{11.41,43.20},{59.42,114.51},{44.03,62.51},
  {38.04,86.32},{85.50,131.11},{93.21,152.09},{82.26,160.47},
  {49.29,90.17},{78.86,126.58},{ 0.95,26.22},{63.44,106.39},
  {28.54,38.89},{44.60,91.99},{75.27,127.43},{ 3.21,28.03},
  {68.07,117.83},{28.55,64.70},{81.46,131.76},{37.61,72.26},
  {30.90,50.93},{83.26,129.32},{99.26,166.27},{92.25,127.03},
  {46.25,88.25},{87.28,130.21},{88.93,149.60},{67.16,121.60},
  {38.35,81.73},{60.44,102.45},{60.25,110.12},{50.22,80.88},
  {13.16,35.31},{ 5.44,39.66},{19.65,53.65},{19.06,70.17},
  { 1.77,14.56},{47.64,93.59},{34.43,67.49},{80.93,114.51},
  {57.97,101.17},{73.68,130.20},{54.59,106.92},{28.75,45.09},
  {21.77,55.38},{84.77,149.73},{45.67,79.64},{ 4.71,39.69},
  {97.31,162.31},{55.41,103.48},{60.03,108.59},{46.17,94.73},
  {29.61,50.63},{88.56,134.34},{96.77,146.07},{72.45,122.47},
  { 5.34,38.58},{29.51,61.88},{99.63,164.66},{33.03,79.84},
  {58.15,99.87},{23.47,40.32},{99.88,153.95},{42.19,87.58},
  {51.86,96.54},{51.82,103.10},{64.15,120.72},{35.58,69.85},
  {50.30,95.52},{30.40,59.75},{44.39,104.84},{ 5.75,27.37},
  {76.76,120.89},{38.51,78.25},{51.38,95.20},{95.87,144.37},
  {25.73,57.94},{48.17,86.26},{76.52,136.26},{62.27,104.44},
  { 6.09,25.91},{86.23,139.69},{95.85,137.52},{65.11,95.32},
  {50.01,76.43},{86.87,150.37},{72.84,114.23},{ 4.61,40.10},
  {56.12,94.18},{18.48,49.12},{71.50,129.55},{66.05,122.13},
  {88.05,135.69},{48.16,93.94},{15.01,56.52},{47.18,98.47},
  {92.48,169.10},{ 4.27,37.99},{28.35,83.15},{16.24,42.69},
  {61.16,106.80},{20.77,66.28},{98.82,146.01},{50.96,96.21},
  {30.15,81.64},{43.10,69.66},{63.77,110.11},{53.71,104.17},
  { 9.39,34.61},{57.13,101.90},{98.84,151.92},{27.33,71.33},
  {74.06,116.61},{42.54,82.78},{90.46,141.69},{11.72,28.01},
  {52.21,90.57},{71.61,109.93},{10.55,43.48},{ 3.79,25.55},
  {36.59,85.67},{30.36,66.51},{61.63,117.52},{50.93,83.15},
  {72.16,120.20},{94.21,142.89},{56.51,99.26},{78.14,130.00},
  {14.58,52.25},{77.84,112.59},{96.95,149.53},{60.81,102.14},
  {22.48,61.10},{ 0.30,26.35},{19.24,43.53},{14.33,32.93},
  { 2.96,27.57},{73.70,117.04},{80.68,139.90},{93.13,159.18},
  {51.72,79.18},{ 8.65,45.41},{47.80,90.78},{94.24,125.70},
  {34.17,67.00},{ 0.34,21.46},{71.40,137.37},{15.05,49.08},
  {76.83,118.57},{51.99,98.43},{61.83,95.44},{19.42,48.84},
  {30.69,71.48},{42.80,89.98},{38.40,75.66},{95.32,176.27},
  {26.26,63.12},{93.95,146.27},{82.26,127.92},{54.81,98.36},
  {69.41,113.00},{98.83,167.28},{65.81,112.40},{93.29,151.97},
  {83.91,135.23},{ 3.86,30.88},{44.71,93.03},{56.78,99.60},
  {32.13,74.18},{46.05,71.61},{50.97,109.62},{83.30,131.35},
  {16.22,43.35},{68.86,127.38},{32.42,80.10},{68.24,117.81},
  {96.48,145.77},{81.56,137.54},{75.45,128.67},{15.68,49.20},
  { 7.32,28.95},{38.46,79.41},{10.88,43.87},{12.70,38.61},
  {71.27,119.31},{52.17,94.03},{92.68,147.27},{53.31,108.86},
  {34.74,72.20},{22.60,43.26},{85.78,122.56},{16.33,38.68},
  {77.01,128.01},{82.01,145.23},{32.57,80.69},{ 0.02,16.66},
  {60.29,104.37},{56.00,93.17},{83.37,144.58},{77.48,123.07},
  {40.77,82.13},{19.64,37.30},{93.89,147.49},{84.13,136.13},
  {84.61,132.76},{71.94,127.43},{ 3.87,34.60},{ 0.79,31.77},
  {16.24,48.16},{ 5.54,32.61},{ 6.94,18.55},{77.58,121.24},
  {62.66,117.19},{ 3.97,27.93},{36.88,79.37},{33.39,73.04},
  {80.28,124.90},{69.44,112.26},{ 1.25,41.28},{67.13,112.65},
  {61.87,108.98},{79.75,121.69},{40.54,78.77},{14.74,50.92},
  {40.86,96.11},{93.05,142.28},{44.68,105.45},{64.08,118.34},
  {29.65,62.62},{54.85,107.69},{90.49,143.17},{59.53,97.33},
  { 9.42,16.65},{49.28,92.02},{52.06,88.07},{71.91,115.37},
  {28.39,74.31},{24.44,54.18},{99.63,161.50},{23.09,42.04},
  {49.72,104.02},{98.26,156.73},{19.47,39.65},{74.42,131.61},
  {26.34,51.76},{18.85,50.25},{92.10,151.85},{64.50,92.43},
  {52.33,93.21},{48.28,77.80},{ 7.17,45.70},{29.92,88.95},
  {93.88,146.70},{47.45,88.30},{74.86,130.32},{42.21,83.15},
  { 6.16,27.75},{57.72,105.95},{47.29,75.22},{73.18,117.51},
  {79.90,128.71},{57.13,103.83},{30.47,83.21},{62.64,106.70},
  {25.95,48.03},{19.20,36.11},{93.44,157.51},{29.61,64.43},
  {57.80,113.16},{30.12,85.68},{95.70,162.52},{38.33,91.31},
  {73.92,109.80},{40.35,80.61},{71.71,129.67},{82.19,125.78},
  {60.34,107.01},{68.00,108.15},{83.50,132.47},{65.17,109.88},
  {19.85,46.43},{77.69,134.82},{33.77,72.05},{70.60,127.89},
  { 5.90,32.10},{31.79,77.58},{33.11,61.47},{24.43,36.13},
  {84.00,145.60},{53.35,95.48},{24.63,67.01},{42.49,67.65},
  {78.58,129.77},{ 3.25,44.70},{55.43,116.08},{45.04,96.45},
  {31.23,88.99},{20.78,60.56},{16.71,26.57},{47.63,84.40},
  {54.65,100.54},{72.42,93.54},{11.31,38.33},{41.18,89.37},
  {92.63,145.69},{10.10,27.06},{15.15,53.80},{68.30,124.23},
  {51.42,98.39},{83.48,128.65},{99.17,147.48},{41.89,93.76},
  { 5.82,33.79},{46.12,102.08},{27.70,68.92},{61.27,107.36},
  {64.14,115.92},{57.55,92.30},{31.22,61.74},{82.43,127.56},
  { 9.58,31.09},{67.12,111.26},{62.96,107.98},{45.23,83.74},
  {61.04,102.84},{42.45,90.68},{73.58,117.97},{95.43,150.76},
  {90.81,141.34},{40.72,63.75},{93.60,136.40},{54.43,93.75},
  {71.29,115.15},{34.28,72.57},{67.20,123.36},{41.41,83.72},
  {73.92,120.15},{99.54,151.35},{26.27,45.43},{42.09,105.45},
  {67.21,130.43},{48.58,80.74},{54.84,102.13},{69.54,128.98},
  {52.74,79.17},{14.41,24.93},{72.35,118.07},{ 1.92,25.43},
  {97.97,152.71},{32.38,65.57},{78.44,106.08},{56.52,119.34},
  {95.59,138.92},{55.85,84.36},{95.11,154.67},{14.00,36.84},
  {64.62,95.99},{ 9.70,41.96},{52.26,96.94},{67.42,117.94},
  {24.96,59.18},{ 8.38,52.64},{74.37,116.83},{68.76,102.25},
  {34.88,78.65},{33.38,69.48},{24.82,45.38},{89.13,141.27},
  {33.29,67.31},{29.58,67.86},{ 2.19,19.77},{51.20,97.34},
  {51.45,87.51},{82.03,145.19},{67.08,116.99},{24.13,55.96},
  {82.14,133.19},{28.35,83.09},{ 4.42,31.24},{14.13,54.65},
  {56.99,109.60},{82.69,125.00},{ 7.98,41.14},{56.91,112.88},
  {68.30,100.42},{45.31,88.75},{51.48,101.16},{73.78,115.97},
  {14.44,44.23},{11.04,42.79},{41.96,91.91},{44.77,87.93},
  {28.40,66.17},{16.81,24.60},{17.48,49.68},{77.64,136.29},
  {50.49,87.91},{26.09,71.46},{54.62,102.60},{74.13,110.14},
  {75.00,135.54},{33.62,74.08},{88.73,161.69},{25.39,57.34},
  {34.65,56.67},{35.92,90.84},{19.41,54.22},{27.84,75.19},
  {25.89,70.68},{14.69,53.66},{39.51,81.53},{94.68,162.28},
  {97.60,149.96},{20.83,54.73},{83.43,133.29},{92.64,147.64},
  {56.05,111.15},{77.66,133.94},{54.67,107.20},{ 4.35,38.32},
  {23.43,64.26},{71.97,109.12},{59.18,112.54},{22.09,47.81},
  {74.20,129.06},{45.40,96.83},{26.51,46.30},{89.65,143.04},
  {85.96,156.02},{11.89,40.83},{44.87,70.52},{93.22,147.60},
  {28.66,59.66},{31.35,66.83},{69.34,109.77},{89.87,138.15},
  {26.17,59.46},{25.02,62.04},{73.71,132.40},{50.01,92.76},
  {30.35,64.18},{19.32,79.51},{95.09,168.34},{90.29,130.63},
  {75.42,124.10},{55.30,90.92},{12.26,16.01},{24.00,71.79},
  {84.46,133.57},{21.25,50.04},{79.23,143.89},{39.55,82.87},
  {20.27,46.05},{ 9.38,33.89},{37.56,71.08},{47.00,71.16},
  {62.66,117.62},{ 7.15,35.61},{60.14,105.59},{35.96,70.62},
  {15.72,42.11},{86.24,147.30},{39.11,67.83},{38.27,67.53},
  { 5.11,30.22},{78.63,136.75},{ 8.36,37.67},{23.37,64.23},
  {93.34,163.60},{88.87,131.48},{53.44,106.10},{34.51,72.10},
  {99.14,156.10},{64.15,130.98},{84.90,128.07},{ 8.75,50.00},
  {52.86,73.76},{ 0.66,22.96},{78.03,123.22},{58.80,102.22},
  {90.44,158.79},{ 7.63,19.88},{97.50,137.15},{33.11,66.31},
  {31.99,70.57},{78.25,130.68},{58.82,101.51},{95.21,149.34},
  {17.24,41.42},{55.65,110.20},{81.91,134.66},{13.44,34.70},
  {71.88,121.40},{98.19,127.99},{46.40,91.24},{96.90,156.60},
  {82.28,128.61},{64.25,121.59},{23.95,66.46},{24.12,50.64},
  {85.09,145.68},{24.52,67.35},{51.23,109.13},{67.27,122.06},
  {57.36,116.78},{77.75,141.04},{51.98,98.42},{ 1.57,38.62},
  {88.58,132.91},{46.38,90.37},{62.23,125.26},{79.95,110.72},
  {70.95,135.08},{90.87,145.92},{92.70,169.59},{67.62,111.00},
  {54.96,104.12},{27.45,57.75},{33.24,72.37},{ 5.84,37.71},
  {35.26,64.44},{79.57,130.76},{62.17,129.87},{95.17,143.29},
  {63.55,116.87},{15.06,55.89},{70.65,108.84},{39.94,99.98},
  {45.49,72.42},{21.52,45.93},{93.62,150.89},{18.22,45.57},
  {70.06,128.91},{78.48,122.49},{10.52,43.22},{10.13,22.28},
  { 3.80,43.79},{82.52,135.26},{12.22,48.56},{58.73,114.04},
  {66.52,103.81},{59.63,108.67},{35.19,79.32},{44.29,71.20},
  {31.38,63.97},{63.73,124.26},{69.03,119.23},{93.83,162.30},
  {22.60,67.08},{ 0.81,46.34},{29.76,58.96},{25.31,66.94},
  {49.26,82.53},{ 5.96,47.26},{15.31,43.11},{94.82,170.94},
  {10.51,35.38},{75.50,147.18},{25.36,76.18},{15.70,24.55},
  {69.85,120.54},{28.64,67.42},{35.17,65.17},{65.30,114.98},
  {19.21,53.54},{81.79,122.50},{90.04,143.32},{66.90,116.12},
  {19.73,44.64},{91.85,157.33},{84.23,134.69},{22.41,53.29},
  {53.21,104.45},{47.24,85.53},{85.50,142.97},{50.65,72.22},
  {12.50,59.88},{38.21,88.02},{34.15,72.81},{66.36,98.72},
  {28.57,61.63},{53.41,109.91},{ 5.73,51.48},{15.54,39.85},
  {46.55,91.39},{76.35,113.00},{31.47,49.92},{56.92,95.47},
  {67.12,133.66},{88.96,141.05},{29.55,61.62},{47.10,71.17},
  {92.78,145.54},{44.04,79.24},{27.02,59.14},{17.20,50.78},
  {62.42,98.43},{ 2.54,26.55},{30.04,64.90},{10.78,30.81},
  {58.75,93.74},{16.71,39.10},{15.56,38.98},{93.39,156.67},
  {60.61,110.53},{15.73,62.10},{98.61,139.02},{51.31,102.44},
  {19.08,37.73},{78.26,118.37},{31.17,67.56},{18.80,37.23},
  {83.13,147.59},{ 0.35,31.64},{21.67,47.71},{15.18,47.25},
  {61.59,137.62},{21.54,72.73},{42.59,120.68},{95.85,161.21},
  {79.61,123.34},{79.75,139.39},{19.91,64.49},{68.38,133.40},
  {65.95,124.12},{ 0.32,17.00},{95.87,147.90},{95.21,141.63},
  {90.92,156.46},{ 7.92,36.86},{55.98,95.75},{74.46,106.64},
  {54.65,104.63},{90.25,135.99},{84.04,134.68},{50.34,83.23},
  {66.60,113.94},{45.30,76.49},{19.48,47.26},{57.94,95.46},
  {72.86,122.33},{80.81,120.02},{56.71,84.36},{13.25,81.91},
  {29.92,79.97},{ 4.75,31.38},{72.58,112.88},{21.44,48.97},
  { 6.45,21.55},{61.14,117.38},{85.30,125.91},{69.16,103.20},
  {15.49,51.78},{80.99,132.88},{75.83,137.07},{99.06,153.87},
  {99.23,153.17},{44.45,118.03},{27.80,51.14},{60.92,91.38},
  { 0.83,28.88},{14.14,43.66},{ 9.52,33.16},{96.23,156.92},
  {90.15,154.47},{42.88,94.19},{86.49,143.73},{73.96,115.76},
  {65.42,99.10},{57.48,99.14},{50.34,104.97},{ 8.07,36.35},
  {42.66,91.16},{16.86,41.03},{38.36,79.29},{77.31,139.72},
  {80.99,141.69},{30.87,68.37},{99.31,154.45},{27.54,71.97},
  {97.78,176.46},{47.07,92.57},{11.39,56.29},{55.15,76.97},
  {16.59,43.67},{49.94,93.56},{ 2.51,20.58},{64.31,108.19},
  {87.11,140.35},{86.45,150.00},{31.76,75.18},{72.44,104.36},
  {39.66,78.77},{66.55,130.58},{49.60,86.48},{54.46,102.00},
  {52.51,83.37},{15.74,41.67},{ 6.85,41.33},{30.74,73.04},
  {25.76,66.32},{93.46,162.41},{13.31,39.16},{34.45,69.64},
  { 1.22,31.67},{32.35,61.83},{79.53,121.94},{10.75,40.63},
  {19.81,59.24},{80.78,132.52},{54.96,98.96},{42.86,84.40},
  {90.42,136.12},{82.66,128.43},{40.27,70.73},{ 8.31,26.93},
  {59.01,112.84},{51.02,77.72},{27.93,73.39},{21.73,49.60},
  {40.86,60.67},{35.11,81.44},{90.20,159.50},{80.94,138.65},
  {37.94,88.91},{76.79,130.89},{20.76,67.86},{50.93,110.36},
  {57.34,108.67},{17.88,56.82},{80.04,133.88},{28.97,52.15},
  {98.90,162.32},{ 9.80,25.08},{ 9.42,21.99},{46.04,84.24},
  {96.58,142.93},{20.69,56.67},{ 0.04,46.97},{99.72,138.89}
};
