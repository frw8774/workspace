#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("error\n");
        exit(1);
    }
    for(int i = 0;i < argc;i++) {
        char *str = argv[i];
        printf("str: %s\n", str);
    }
    return 0;
}