#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main () {
	srand(getpid());
	int limits[255];
	int i, j, l, v=0, N= 25600;
	for (i=0; i<255; i++) {
		l = (N - v ) - (255 - i);
		limits[i] = rand() % l + v;
		v = limits[i];	
	}
	int res;
	for (i = 0 ; i<10000000 ; i++ ) {
		res = rand () % 25600;
		j=0;
		while (j<255 && limits[j] < res) {
			j++;
		}
		printf("%c", j);
	}
	return 0;
}
