#include <stdio.h>

int main(int argc, char* argv[]) {
	int k = argc;
	int u = 0xdeadbeef;
	int v = argc + 1;

	if (k == u) {
		printf("DOG\n");
		return 1;
	}
	
	if (k == v) {
		printf("DOG\n");
		return 1;
	}

	return 0;
}
