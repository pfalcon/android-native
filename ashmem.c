#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>

int main()
{
    char *p;
    int fd = 9;
    int size = 4096;

    fd = ashmem_create_region("my_shm_region", size);

    if (fd < 0) {
        printf("ashmem_create_region failed\n");
        exit(1);
    }

    ashmem_set_prot_region(fd, PROT_READ);

    p = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

    if (p == MAP_FAILED) {
        printf("mmap() failed. %s\n", strerror(errno));
        exit(1);
    }
    printf("mapped=%x\n", p);
}
