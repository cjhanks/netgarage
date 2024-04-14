#include <stdbool.h>
#include <stdio.h>

int main() {
	unsigned head = 0xbffffa78;
	signed   shft = 0;

	do {
		unsigned k = head + shft;

		if (k == 0x0804b00c) {
			printf("Shift = %d\n", shft);
			break;
		} else {
			++shft;
		}
	} while (true);
}
