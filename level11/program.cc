#include <iostream>
#include <string>


#define MAX_NESTING 100
int bf(const char *prog, char *result, int maxlen)
{
	int output_len = 0;
	char tape[4001];
	int edi=0, eip=0;
	unsigned long endless_loop_protection = 100000;
	int loopstart[MAX_NESTING + 1], depth = 0, state;

	memset(tape, 0, sizeof(tape));
	while(eip < strlen(prog) && --endless_loop_protection)
	{
		//printf("%2d %2d %2d\n", eip, edi, tape[0]);
		switch(prog[eip])
		{
			case '<':
				if(edi) --edi;
				break;
			case '>':
				if(edi<4000) ++edi;
				break;
			case '+':
				++tape[edi];
				break;
			case '-':
				--tape[edi];
				break;
			case '.':
				if (output_len < maxlen) result[output_len++] = tape[edi];
				break;
			case ',':
				/* not implemented */
				break;
			case '[':
				state=1;
				if(!tape[edi])
					while (state && ++eip < strlen(prog))
						if (prog[eip] ==']') --state;
						else if (prog[eip] == '[') ++state;
						else;
				else if (depth < MAX_NESTING)
					loopstart[++depth] = eip;
				break;
			case ']' :
				if(depth)
					if(tape[edi] == 0)
						--depth;
					else
						eip = loopstart[depth];
				break;
		}
		++eip;
	}

	result[output_len]=0;
	return output_len;
}

int main() {
  std::string AA = "+[----->+++<]>++.++++++.[->+++++<]>+++.[--->++<]>-.+.-.+[---->+<]>+++.>-[--->+<]>---.----[-->+++<]>.---------.-------.[--->+<]>----.+[-->+++++<]>-.";
  std::string BB = "+[----->+++<]>++.++++++.[->+++++<]>+++.[--->++<]>-.+.-.+[---->+<]>+++.>-[--->+<]>--.[--->+<]>++++.+[->+++<]>+.++++++++.++++++++.+[-->+++++<]>-.";


	{
	const char* prog_i = "+[----->+++<]>++.++++++.[->+++++<]>+++.[--->++<]>-.+.-.+[---->+<]>+++.>-[--->+<]>---.----[-->+++<]>.---------.-------.[--->+<]>----.+[-->+++++<]>-.";
	char prog_o[101];

	bf(prog_i, prog_o, strlen(prog_i));
	printf("%s\n", prog_o);
	}

	{
	const char* prog_i = "+[----->+++<]>++.++++++.[->+++++<]>+++.[--->++<]>-.+.-.+[---->+<]>+++.>-[--->+<]>--.[--->+<]>++++.+[->+++<]>+.++++++++.++++++++.+[-->+++++<]>-.";
	char prog_o[101];

	bf(prog_i, prog_o, strlen(prog_i));
	printf("%s\n", prog_o);
	}

	return 0;
}
