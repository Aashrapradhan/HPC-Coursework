#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>

int n_passwords = 4;
char *encrypted_passwords[] = {
  "$6$KB$6SsUGf4Cq7/Oooym9WWQN3VKeo2lynKV9gXVyEG4HvYy1UFRx.XAye89TLp/OTcW7cGpf9UlU0F.cK/S9CfZn1",
  "$6$KB$BnOJ7N1FAfJEUjwbecr9dk3lZFbrvc0XenvCyQebIefk5xcLST4qwSQw0OkkP9QzHJHtRNyLdGiXlii0Yk08N/",
  "$6$KB$icnRnNepqkse.R27QuNspJ8610GJMOnYaq2yd.BvXh9liLT54pc8tVdQYgb.gGEHf9.pLy3jeBCBHUcGfTjBF0",
  "$6$KB$84zwDcHrdp/eBoNjCN/8erI4FwcEnLOYotIEb897.Kh359yBvOLg7U6kfY10D0EH6pDM/P29.GivukFyP3Jax/"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void firstpasscrack(char *salt_and_encrypted){
  int p, q, r;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);



  for(p='A'; p<='M'; p++){
    for(q='A'; q<='Z'; q++){
      for(r=0; r<=99; r++){
        sprintf(plain, "%c%c%02d", p, q, r);
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
  printf("The explored solutions are: %d \n", count);
}


void secondpasscrack(char *salt_and_encrypted){
  int p, q, r;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);



  for(p='N'; p<='Z'; p++){
    for(q='A'; q<='Z'; q++){
      for(r=0; r<=99; r++){
        sprintf(plain, "%c%c%02d", p, q, r);
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



