/* Parker Temple */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "course.h"
#include "vector.h"

void find_crn(char **subjects, char **courses, int *crns, int subsize, int coursesize, int crnsize)
{
  int i, crn;
  printf("Please enter a CRN: ");
  scanf("%d", &crn);
  for(i = 0; i < crnsize; i++)
    if(crn == crns[i])
    {
      printf("%s %s\n", subjects[i], courses[i]);
      return;
    }//if
  printf("CRN %d not found.\n", crn);
}//find_crn

void find_subject(char **subjects, char **courses, int *crns, int subsize, int coursesize, int crnsize)
{
  char subj[4];
  int i, count = 0;
  printf("Please enter subject: ");
  scanf("%s", subj);
  for(i = 0; i < subsize; i++)
  {
    if(!strcmp(subj, subjects[i]))
    {
      printf("%d %s %s\n", crns[i], subjects[i], courses[i]);
      count++;
    }//if !strcmp
  }//for i
  if(!count)
    printf("No courses were found for %s.\n", subj);   
}//find_subject()

void read_courses(char *arg[], char ***subjects, char ***courses, int **crns, int *subsize, int *coursesize, int *crnsize)
{
  FILE *fp = fopen(arg[1], "r");
  int i, j, subcount = 0, coursecount = 0, crncount = 0, crn;
  char *line, str[6], *ptr;
  if(fp == NULL)
  {
    printf("(null) not readable.\n");
    exit(1);
  }//if fp null
  line = (char *) malloc(sizeof(char) * 300);
  ptr = (char *) malloc(sizeof(char) * 300);
  initialize(subjects, courses, crns);
  
  while(fgets(line, 299, fp) != NULL)
  {
    for(i = 0; i < 6; i++)
    {
      if(!isdigit(line[0]))
        break;
      if(i < 5)
      {
        str[i] = line[i];
      }//if i < 5
      if(!isdigit(line[4]))
        break;
      if(i == 5)
      {
        str[5] = '\0';
        crn = atoi(str);
        (*crns)[crncount++] = crn;
        ptr = strtok(line, "\t");
        ptr = strtok(NULL, "\t");
        if(ptr[0] == '^')
          ptr = strtok(NULL, "\t");
        for(j = 0; j < 3; j++)
          (*subjects)[subcount][j] = ptr[j];
        (*subjects)[subcount][j] = '\0';
        subcount++;
        ptr = strtok(NULL, "\t");
        
        for(j = 0; j < 5; j++)
        {
          if(ptr[j] == '\t')
            break;
          (*courses)[coursecount][j] = ptr[j];
        }//for j < 5
        ptr[j] = '\0';
        coursecount++; 
      }//if i is 6
    }//for i
    if(crncount == (*crnsize - 2))
      resize(subjects, courses, crns, subsize, coursesize, crnsize);
  }//while fgets
  for(i = 0; i < coursecount / 2; i++)
    printf("%s %s %d\n", (*subjects)[i], (*courses)[i], (*crns)[i]);
  fclose(fp);
}//read_courses
