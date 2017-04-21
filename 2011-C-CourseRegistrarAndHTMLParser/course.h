/* Parker Temple */

#ifndef COURSE_H
  #define COURSE_H

void find_crn(char **subjects, char **courses, int *crns, int subsize, int coursesize, int crnsize);
void find_subject(char **subjects, char **courses, int *crns, int subsize, int coursesize, int crnsize);
void read_courses(char *arg[], char ***subjects, char ***courses, int **crns, int *subsize, int *coursesize, int *crnsize);

#endif
