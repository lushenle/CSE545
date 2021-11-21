#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct {
    unsigned char ring_buffer[32];
    void (*exit_func_ptr)(int);
} global;

void give_me_a_shell()
{
    printf("Good job!\n");
    system("/bin/sh");
}

void my_exit()
{
    exit(0);
}

void my_awesome_hash(unsigned char* data, int n)
{
    unsigned long long hash = 0x9980c25e1b3501da;

    // Initialization
    for (int i = 0; i < n; ++i)
    {
        global.ring_buffer[i] = 0;
    }

    // Compute the hash
    for (int i = 0; i < n; ++i)
    {
        hash ^= data[i];
        hash = (hash << 9) ^ (hash >> 5);
        hash += 17;
        hash ^= 0xdeadbeefc0debabe;

        // Write out hash into the ring buffer
        // Be extra-careful - do not overflow!
        for (int j = 0; j < sizeof(unsigned long long); ++j) {
            int pos = j + i;
            if (pos > sizeof(global.ring_buffer)) {
                pos = 0;
            }
            global.ring_buffer[pos] = *((unsigned char*)&hash + j);
        }
    }
}

int main(int argc, char **argv)
{
    global.exit_func_ptr = &my_exit;
    if (argc != 2) {
        printf("Usage: %s input\n", argv[0]);
        global.exit_func_ptr(1);
    }
    printf("Hashing your input...\n");

    my_awesome_hash((unsigned char*)argv[1], strlen(argv[1]));

    printf("Your hash is: ");
    for (int i = 0; i < sizeof(global.ring_buffer); ++i) {
        printf("%02x ", global.ring_buffer[i]);
    }
    printf("\n");

    global.exit_func_ptr(0);
}
