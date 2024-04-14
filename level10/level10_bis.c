//written by andersonc0d3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv) {
        FILE *fp = fopen("/levels/level10_bis.pass", "r");
        struct {char welcome[200], pass[20], msg_err[200];} pwfile = {{0}};
        char ptr[0];


        if(!fp || argc != 2)
                return -1;

        fread(&pwfile, 1, 220, fp);
        printf("%.20s", pwfile.welcome);

        pwfile.pass[19] = 0;
        ptr[atoi(argv[1])] = 0;
        fread(pwfile.msg_err, 1, sizeof(pwfile.msg_err), fp);
        fclose(fp);


        if(!strcmp(pwfile.pass, argv[1]))
                execl("/bin/sh", "sh", 0);
        else
                puts(pwfile.msg_err);


        return 0;
}

