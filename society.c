#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0

/************
 * will be used to
 * create and monitor
 * the people of the society
 ************/
struct person{
  int SELF;
  int happy;
};

/*****************************
 * will create a rando 1 or 0
 * this is gonna go and become
 * a new persons personality
 *****************************/
int rando(){
  int val = rand();
  if (val%2 != 0) {
    val = true;
  }else{
    val = false;
  }
  return val;
}

/*********************
 * should be able to take command line
 * args so that they can create a population
 * to their specifics
 * maybe later on they can change the default
 * setting for person.SELF
 **********************/
int main (int nargs, char * args){
  srand(time(NULL));
  int popl;
  int k=100;
  struct person pop[k]; //setting up null population at base lien
  //the creation of a society takes a sec
  while(k){
    int val = rando();
    printf("%d\t", val);
    struct person sean; //unisex name
    sean.SELF = val;
    pop[k] = sean;
    k--;
  }
  return 0;
}

