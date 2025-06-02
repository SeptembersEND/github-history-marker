#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>


#define WEEKS	32
// ' ': end
// _: day
// #: draw
// T: tommorrow
const char timeline[7][WEEKS] = {
	/*Su*/ "________________________________",
	/*Mo*/ "___#__#_###_#___#___####________",
	/*Tu*/ "___#__#_#___#___#___#__#________",
	/*We*/ "___####_##__#___#___#__#_______T",
	/*Th*/ "___#__#_#___#___#___#__#_______ ",
	/*Fr*/ "___#__#_###_###_###_####_______ ",
	/*Sa*/ "_______________________________ ",
};
const int today = 350;

void print(const char line[7][WEEKS]) {
	for (int y=0; y<7; y++) {
		for (int x=0; x<WEEKS; x++) {
			char c = line[y][x];
			printf("%c,", c);
		}
		printf("\n");
	}
}
void run(int val) {
#define BUFS	256
	char buf[BUFS] = {0};
	memset(buf, 0, BUFS);
	static int test = 0;

	snprintf(buf, BUFS, "git add . && git commit -m 'Commit Position: #%d try 7' --no-edit --date=\"$(date -uRd $(date -ud '2025-01-01 + %d days' +\%Y-%s-%s))\"", test++, val+1, "%m", "%d");
	FILE* outfile = fopen("command", "w");
	fprintf(outfile, "Command: `%s`\n", buf);
	fclose(outfile);
	printf("%s\n", buf);
	system(buf);
}
int main(void) {
	//run(350);
	int thevalue = 0;
	for (int x=0; x<7; x++) {
		if (timeline[x][WEEKS-1] == 'T') {
			thevalue = x;
			break;
		}
		//printf("%c\n", timeline[x][WEEKS-1]);
	}
	assert(thevalue != 0);


	const int totallength = (today-thevalue) - (WEEKS * 7);
	//printf("%d\n", totallength);
	int z=totallength;

	print(timeline);
	for (int y=0; y<7; y++) {
		for (int x=0,z=WEEKS-1; x<WEEKS-1; x++,z--) {
			char c = timeline[y][x];
			if (c == '#') {
				int r = (((today-thevalue) - (z * 7)) + y)-1;
				//printf("%d,", r);
				run(r);
			}
		}
		printf("\n");
	}
}
