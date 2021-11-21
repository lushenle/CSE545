#include <stdio.h>
#include <stdlib.h>


void give_me_a_shell()
{
    system("/bin/sh");
}


int main(int argc, char *argv[])
{
    int buffer[12];
    unsigned long long addr = 1;
    unsigned long long value = 0x1337;
    /* Ref: https://stackoverflow.com/questions/8201233/accessing-a-register-without-using-inline-assembly-with-gcc */
    register long long rsp asm ("rsp");

    if (argc < 3)
    {
        fprintf(stderr, "Not enough arguments.\n");
        fprintf(stderr, "Usage: %s address new_value\n", argv[0]);
        return -1;
    }

    /* Fill in the buffer */
    for (int i = 0; i < sizeof(buffer) / sizeof(int); ++i)
    {
        buffer[i] = i * 10;
    }

    printf("The give_me_a_shell function is at %#llx.\n", (unsigned long long)&give_me_a_shell + 1);
    /* We skip the very first instruction of give_me_a_shell(), otherwise it segfaults inside libc because of alignment issues.
     * See https://stackoverflow.com/questions/54393105/libcs-system-when-the-stack-pointer-is-not-16-padded-causes-segmentation-faul */
    printf("The current stack frame looks like this:\n");
    for (int i = 0; i < 20; ++i)
    {
        printf("%02x | %016llx | %llx\n", i, rsp + i * 8, *(unsigned long long*)(rsp + i * 8));
    }

    addr = rsp + 8 * strtoull(argv[1], NULL, 16);
    value = strtoull(argv[2], NULL, 16);
    printf("Updating value at address %llx with %llx: previous value was %llx\n", addr, value, *(unsigned long long*)addr);
    *(unsigned long long*)addr = value;

    printf("After updating, the current stack frame looks like this:\n");
    for (int i = 0; i < 20; ++i)
    {
        printf("%02x | %016llx | %llx\n", i, rsp + i * 8, *(unsigned long long*)(rsp + i * 8));
    }

    return 0;
}
