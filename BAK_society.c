#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define true 1
#define false 0
//setup 
/*************
 * will be used to
 * create and monitor
 * the people of the society
 ************/
struct person{
  int SELF;
  int happy;
  int id;
};

int ARRAYLEN = 0;
int TIMES = 1;
int FATCATS = 0;
int selfish;
int altruistic;
void printresults(struct person bloke);
void dothething(struct person pop[ARRAYLEN]);
int cutmeup(int runs);

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

/********************************
 * BIRTHS A NEW PERSON INTO THE WORLD!
 ********************************/
struct person birth(int tag){
  struct person bloke;
  bloke.SELF = rando();
  bloke.id = tag;
  bloke.happy = 0;
  return bloke;
}

/*****************************
 * ease of use dealio
 ****************************/
int askaquestion(char *string){
  printf("%s",string);
  int answer;
  scanf("%d", &answer);
  return answer;
}

/***********************************************
 * sets up how many runs if multiple and will pass along
 * if there is only one. if not it will run through all 
 * the runs given
 **********************************************/
void questionnaire(struct person pop[ARRAYLEN]){
  int answer = askaquestion("\nMultiple Runs?\n\t1 for YES and 0 for NO\n");
  printf("\n %d = answer",answer);

  int runs; //how many times will this experiment be run?
  if (answer == true){
    runs = askaquestion("\nHow many Runs?\t");
    //printf("\n %d = runs",runs);
  }else{
    printf("thanks for playing");
    runs = 1;
  }

  if (runs > 1){
    while (runs > 0){
      dothething(pop);
      runs--;
    }
  }else{
    dothething(pop);
  }
  return;
}

/*************************************
 * This is where the
 * main part of the project
 * is being done
 * i have set it up so that the "question" based on
 * a random int which will determine if the individual will change
 * sides or always stick to their morals
 ************************************/
void dothething(struct person pop[]){
  int question = rand();
  int i = 0;
  int mod;
  int k = 0;
  printf("Run %d results:\n", TIMES);
  while(i < ARRAYLEN){
    while (k < ARRAYLEN){
      if (k == i){
        k++;
      }
      if (pop[k].SELF == true){
        selfish++;
      }else{
        altruistic++;
      }
      k++;
    }
    //mod should signify the weight of others opinions/actions on the individual
      mod = ((selfish * -1) + altruistic)%10;
      selfish = 0;
      altruistic = 0;
     // ^ this above section should vary every iteration 
    if ((question+
          (mod*(pop[i].id+1)*abs(pop[i].happy))
        )% 2 != 0){
      if (pop[i].SELF == true){
        pop[i].SELF = false;
      }else{
        pop[i].SELF = true;
      }
    }
    if (pop[i].SELF == true){
      pop[i].happy+=5;
      selfish++;
    }else{
      pop[i].happy-=2;
      altruistic++;
    }
    printresults(pop[i]);
    i++;
  } 
  if(selfish > altruistic){
    FATCATS = selfish - altruistic;
    FATCATS *= -1;
  }else{
    FATCATS = altruistic - selfish;
  }
  i = 0;
  while(i < ARRAYLEN){
    pop[i].happy += FATCATS;
    i++;
  }
  FATCATS = 0;
  printf("%d was the number in question\n", question);
  TIMES++;
  return;
}

/**************************************
 * prints the results on an individual level
 *************************************/
void printresults(struct person bloke){
  char * string;
  if(bloke.SELF == true)
    string = "true";
  else
    string = "false";
  printf(" ID: %d,\tHappiness: %d,\tSelfish? %s\n", bloke.id, bloke.happy, string);
}

/***********************************
 * should be able to take command line
 * args so that they can create a population
 * to their specifics
 * maybe later on they can change the default
 * setting for person.SELF
 ***********************************/
int main (int nargs, char * args[]){
  srand(time(NULL));
  char * string;
  int k = atoi(args[1]);
  ARRAYLEN = k;
  int idnum = 0;
  struct person pop[k]; //setting up null population at base lien
  //the creation of a society takes a sec
  printf("%d : k \n", k);
  printf("[********************Beginning Stats***********************]\n");
  while(k){
    struct person sean = birth(idnum);
    printresults(sean);
    pop[idnum] = sean;
//    printf("%d,\t",pop[idnum].id);
    idnum++;
    k--;
  }
  //check to see if it will fork
  questionnaire(pop);
  exit(0);
}

