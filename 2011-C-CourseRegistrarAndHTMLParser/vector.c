/* Parker Temple */

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void initialize(char ***subjects, char ***courses, int **crns)
{
  int i;
  *subjects = (char **) malloc(100 * sizeof(char *));
  for(i = 0; i < 100; i++)
    (*subjects)[i] = (char *) malloc(4);
  *courses = (char**) malloc(100 * sizeof(char*));
  for(i = 0; i < 100; i++)
    (*courses)[i] = (char *) malloc(6);
  *crns = (int *) malloc(100 * sizeof(int));
}//initialize

void resize(char ***subjects, char ***courses, int **crns, int *subsize, int *coursesize, int *crnsize)
{
  int i;
  char **subjects2, **courses2;
  int *crns2;
  subjects2 = (char **) malloc(*subsize * 2 * sizeof(char *));
  for(i = 0; i < (*subsize); i++)
    subjects2[i] = (*subjects)[i];
  free(*subjects);
  *subjects = subjects2;
  for(i = (*subsize); i < (*subsize) * 2; i++)
    (*subjects)[i] = (char *) malloc(4);
  *subsize = *subsize * 2;

  courses2 = (char **) malloc(*coursesize * 2 * sizeof(char*));
  for(i = 0; i < (*coursesize); i++)
    courses2[i] = (*courses)[i];
  free(*courses);
  *courses = courses2;
  for(i = (*coursesize); i < (*coursesize) * 2; i++)
    (*courses)[i] = (char *) malloc(6);
  *coursesize = *coursesize * 2;

  crns2 = (int *) malloc(*crnsize * 2 * sizeof(int));
  for(i = 0; i < *crnsize; i++)
    crns2[i] = (*crns)[i];
  free(*crns);
  *crns = crns2;
  *crnsize = *crnsize * 2;
}//resize

void deallocate(char **subjects, char **courses, int *crns, int subsize, int coursesize, int crnsize)
{
  int i;
  for(i = 0; i < subsize; i++)
    free(subjects[i]);
  free(subjects);
  for(i = 0; i < coursesize; i++)
    free(courses[i]);
  free(courses);
  free(crns);
}//deallocate
