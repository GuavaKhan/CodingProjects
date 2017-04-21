/* Parker Temple */

#ifndef VECTOR_H
  #define VECTOR_H

void initialize(char ***subjects, char ***courses, int **crns);
void resize(char ***subjects, char ***courses, int **crns, int *subsize, int *coursesize, int *crnsize);
void deallocate(char **subjects, char **courses, int *crns, int subsize, int coursesize, int crnsize);

#endif
