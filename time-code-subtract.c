#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct time {
	int hours;

	int minutes;

	int seconds;
};

struct time argToTime(char* arg) {
	int c = 0;

	struct time t = {0};

	char *poo = strtok(arg, ":");
       
	while(poo) {
		if(c == 0) {
			t.seconds = atoi(poo);
		}

		if(c == 1) {
			t.minutes = t.seconds;

			t.seconds = atoi(poo);
		}

		if(c == 2) {
			t.hours = t.minutes;

			t.minutes = t.seconds;

			t.seconds = atoi(poo);
		}

		if(c > 2) {
			return t;	
		}

		c++;

		poo = strtok(0, ":");
	};

	return t;
}

struct time subtract(struct time a, struct time b) {
	struct time result = {0};

	int seconds_carry = a.seconds > b.seconds ? 1 : 0;

	int minutes_carry = a.minutes > (b.minutes - seconds_carry) ? 1 : 0;

	result.seconds = (b.seconds - a.seconds + 60) % 60;

	result.minutes = (b.minutes - a.minutes - seconds_carry + 60) % 60;

	result.hours = b.hours - a.hours - minutes_carry;

	return result;
}

void print(struct time t) {
	printf("%02d:%02d:%02d\n", t.hours, t.minutes, t.seconds);
}

int main(int argc, char **argv) {

	char *arg_a = argv[1];

	char *arg_b = argv[2];

	if(argc != 3) {
		printf("usage: time-code-subtract <end> <begin>");

		printf("\n\n");

		return 1;
	}

	struct time a = argToTime(arg_a);

	struct time b = argToTime(arg_b);

	struct time result = subtract(b, a);

	print(result);

	return 0;
}

