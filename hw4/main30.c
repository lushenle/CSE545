#include <stdio.h>
#include <stdlib.h>


#define TABLELEN 7
int table[] = {2, 3, 5, 7, 11, 13, 17};


void loadTable(unsigned long long *hashtable) {
    int i;
    for (i = 0; i < TABLELEN; i++) {
        hashtable[i] = table[i];
    }
}


int main(int argc, char *argv[])
{
    unsigned long long array[8];
    unsigned long long index;
    unsigned long long value;
    char buffer[30] = {0};
    register long long rsp asm ("rsp");

    loadTable(array);

    printf("Current stack pointer: %llx\n", rsp);

    // Load index
    scanf("%29s", buffer);
    index = strtoll(buffer, NULL, 10);

    // Load value
    scanf("%29s", buffer);
    value = strtoull(buffer, NULL, 16);

    printf("Updating table value at index %lld with %llx.\n", index, value);
    printf("Previous value was %llx\n", array[index]);
    array[index] = value;

    printf("The updated table is:\n");
    for (index = 0; index < TABLELEN; index++) {
        printf("%lld | %llx\n", index, array[index]);
    }

    return 0;
}
