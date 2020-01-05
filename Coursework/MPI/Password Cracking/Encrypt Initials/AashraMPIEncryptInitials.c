

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <crypt.h>
#include <mpi.h>

/***********************************************************************
*******
  
  Compile with:
    mpicc -o AashraMPIEncryptInitials AashraMPIEncryptInitials.c -lcrypt

  Run with:

    mpirun -n 3 ./AashraMPIEncryptInitials > EncryptInitialsMPIResult.txt


************************************************************************
******/

int n_passwords = 4;
pthread_t threadfirst, threadsecond;
char *encrypted_passwords[] = {
  "$6$KB$pmFmErkYTIPVuY1v6D11uRabeN4qQsZLdNFa9NxCRl5mhzlzZi0hakaYuZNbDPxsadjim3TpleFoGH52rIu1d0",
  "$6$KB$8V1VyMkh.4210SEu0mDey6M.q0H93kDVOxL4Mhs62VPFP.9gDQ7hvoTjPQsiNPYYoiG5dDFOvXkdg1KxblPaY1",
  "$6$KB$3Y8WmKjk7ve0PWRsQ9cSEEPEm7cwnOPeviyc2CRj/KE0wvI5/yoqWNM8lwOWVByI/RNhs9z6/EoEtX5giAw1g.",
  "$6$KB$X9cXvmuZREDHA68atbAZ9UoCt7lq7Ob6TWEwqP27cnPl4mbh97g.o.PszjPfhlJOgCGU8hpLRv3ljzRiTmwnD/"
};

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}
  
void AashraPassCrack(char *salt_and_encrypted){
  int p, q, r;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space

  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);
  
  for(p='A'; p<='M'; p++){
    for(q='A'; q<='Z'; q++){
      for(r=0; r<=9999; r++){
	printf("Instance number 1:");
	sprintf(plain, "%c%c%04d",p, q, r);
	enc = (char *) crypt(plain, salt);
	count++;
	if(strcmp(salt_and_encrypted, enc) == 0){
	  printf("#%-8d%s %s\n", count, plain, enc);
	} else {
	 // printf(" %-8d%s %s\n", count, plain, enc);
	}
      }
    }
  }
  printf("The explored solutions are: %d\n", count);
}
void AashraPassCrack2(char *salt_and_encrypted){
  int p, q, r;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space

  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);
  
  for(p='N'; p<='Z'; p++){
    for(q='A'; q<='Z'; q++){
      for(r=0; r<=9999; r++){
	printf("Instance number 2:");
	sprintf(plain, "%c%c%04d",p, q, r);
	enc = (char *) crypt(plain, salt);
	count++;
	if(strcmp(salt_and_encrypted, enc) == 0){
	  printf("#%-8d%s %s\n", count, plain, enc);
	} else {
	 // printf(" %-8d%s %s\n", count, plain, enc);
	}
      }
    }
  }
  printf("The explored solutions are: %d\n", count);
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

int main(int argc, char** argv) {
 struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

 
  int size, rank;
  int aashra;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(size != 3) {
    if(rank == 0) {
      printf("This program needs to run on exactly 3 processes\n");
    }
  } else {
    if(rank ==0){

      int x;
    
      MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Send(&x, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);


 
    } else if(rank==1){
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 
                         MPI_STATUS_IGNORE);
        for(aashra=0;aashra<n_passwords;aashra<aashra++) {
          AashraPassCrack(encrypted_passwords[aashra]);
        }
      }
      else{
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 
                         MPI_STATUS_IGNORE);
        for(aashra=0;aashra<n_passwords;aashra<aashra++) {
          AashraPassCrack2(encrypted_passwords[aashra]);
        }
      }
    }
    MPI_Finalize(); 
 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("The time duration is %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9)); 

  return 0;
}
