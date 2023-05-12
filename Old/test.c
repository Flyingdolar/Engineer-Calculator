#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getNetwork() {
    int num;
    FILE *fp = NULL;
    char buffer[100];
    char *cmd = "ip -s link | grep -v mode | grep -v link | grep -v bytes | awk '{print $1}'";

    fp = popen(cmd, "r");
    if (fp == NULL) return -1;

    fgets(buffer, 100, fp);
    num = atoi(buffer);

    pclose(fp);
    return num;
}

int main(int argc, char const *argv[]) {
    int num = 0;

    num -= getNetwork();
    sleep(1);
    num += getNetwork();
    printf("%d\n", num);
    return 0;
}
