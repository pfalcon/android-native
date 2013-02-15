#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
    void *so, *sym;

    if (argc < 2) {
        printf("Usage: %s <lib.so> [<symbol>]\n", argv[0]);
        exit(1);
    }

    so = dlopen(argv[1], RTLD_NOW);
    if (!so) {
        printf("Error dlopen'ing %s: %s\n", argv[1], dlerror());
        exit(1);
    }
    printf("Shared object handle for %s: %p\n", argv[1], so);

    if (argc == 2)
        return 0;

    sym = dlsym(so, argv[2]);
    printf("Address of '%s': %p\n", argv[2], sym);
    return 0;
}
