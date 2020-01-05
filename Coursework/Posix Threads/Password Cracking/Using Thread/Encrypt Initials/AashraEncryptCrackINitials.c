#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>

int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$6VWsIodK8PLb35fn9UWFEUu4jeSnGZL/dXr9ZIQBNDK7dluF5WU3s0FATxd72CRRnJqSQVLtBBvZoTedJ1Lhm/",
  "$6$KB$wslsakny.T0z8oUgGV2Vr8zqeWdAPxTdT4NBV2fuzk55CiZnfv7dc2yuvPlU6pinokVuXBBkv.fN8y1RcWS1..",
  "$6$KB$mBKJgSxPkiisqP7uunjVGcER/fDA4GUFvVFA2qfJGITMpv62JtEaYwM0M2lfJtI2K4bDQKeXL7mvWxh0L0sg.0",
  "$6$KB$inKVoFdNhedgkapWziCiajBYC2Os/xK6lDZJQ5qqgIn/zRvBEeo7yn6NUU1mG666Rio898.WLknA.9btHYZ3K/"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void firstpasscrack(char *salt_and_encrypted){
  int aa, p, q, r;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[8];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);


for(aa='A'; aa<='M'; aa++){
  for(p='A'; p<='Z'; p++){
    for(q='A'; q<='Z'; q++){
      for(r=0; r<=99; r++){
        sprintf(plain, "%c%c%c%02d", aa, p, q, r);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);

        } else {
	printf(" %-8d%s %s\n", count, plain, enc);

        }
      }
    }
  }
}
  printf("The explored solutions are: %d \n", count);
}


void secondpasscrack(char *salt_and_encrypted){
  int aa, p, q, r;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[8];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);


for(aa='N'; aa<='Z'; aa++){
  for(p='A'; p<='Z'; p++){
    for(q='A'; q<='Z'; q++){
      for(r=0; r<=99; r++){
        sprintf(plain, "%c%c%c%02d", aa, p, q, r);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);

        } else {
	printf(" %-8d%s %s\n", count, plain, enc);

        }
      }
    }
  }
}
  printf(" The explored solutions are: %d \n", count);
}



int time_difference(struct timespec *start,
                    struct timespec *finish,
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



int main(int argc, char *argv[]){

  pthread_t threadfirst, threadsecond;
  int aashra;

  struct timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

   for(aashra=0;aashra<n_passwords;aashra<aashra++)
   {

    pthread_create(&threadfirst, NULL, (void*) firstpasscrack, encrypted_passwords[aashra]);
    pthread_create(&threadsecond, NULL, (void*) secondpasscrack, encrypted_passwords[aashra]);
    pthread_join(threadfirst, NULL);
    pthread_join(threadsecond, NULL);
   }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    time_difference(&start, &finish, &time_elapsed);
    printf("The time duration is %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9));
  return 0;
}


