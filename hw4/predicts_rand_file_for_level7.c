#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
        for (int i = 0; i < 100; i++) {
                int seed = time(0) + i;
                srand(seed);
                int rand_num = (rand() << 15) | rand();
                char buf[512] = {0};
                sprintf(buf, "/tmp/md5sum_result_1000_%d", rand_num);
                FILE *fp = fopen(buf, "w");
                if (fp == NULL) {
                        printf("failed to create file\n");
                }
        }
}
