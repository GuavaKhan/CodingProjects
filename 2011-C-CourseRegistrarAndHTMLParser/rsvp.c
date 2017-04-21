/* Parker Temple */

#include <stdio.h>
#include "rsvp.h"
#include "course.h"
#include "vector.h"

int main(int argc, char *argv[])
{
  char **subjects, **courses;
  int *crns, subsize = 100, coursesize = 100, crnsize = 100;
  read_courses(argv, &subjects, &courses, &crns, &subsize, &coursesize, &crnsize);
  display_info(subjects, courses, crns, subsize, coursesize, crnsize);
  deallocate(subjects, courses, crns, subsize, coursesize, crnsize);
  return 0;
}//main

int get_choice()
{
  int choice = 1;
  while(choice)
  {
    printf("\nRSVP Menu\n");
    printf("0. Done.\n");
    printf("1. Find by CRN.\n");
    printf("2. Find by subject.\n");
    printf("Your choice (0 - 2): ");
    scanf("%d", &choice);
    if(choice > 2 || choice < 0)
      printf("Your choice is outside the acceptable range.  Please try again.\n\n");
    else//choice btwn 0 and 2 inclusive
      break;
  }//while
  return choice;
}//get_choice

void display_info(char **subjects, char **courses, int *crns, int subsize, int coursesize, int crnsize)
{
  int choice = 1;
  while(choice)
  {
    choice = get_choice();
    if(choice == 0)
      break;
    if(choice == 1)
      find_crn(subjects, courses, crns, subsize, coursesize, crnsize);
    if(choice == 2)
      find_subject(subjects, courses, crns, subsize, coursesize, crnsize);
  }//while
}//display_info
