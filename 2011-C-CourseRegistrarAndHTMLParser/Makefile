#Parker Temple

rsvp.out: rsvp.o course.o vector.o
	gcc -g -Wall -o rsvp.out rsvp.o course.o vector.o
rsvp.o: rsvp.c rsvp.h
	gcc -g -Wall -c rsvp.c
course.o: course.c course.h
	gcc -g -Wall -c course.c
vector.o: vector.c vector.h
	gcc -g -Wall -c vector.c
clean:
	rm -f vector.o course.o rsvp.o rsvp.out
