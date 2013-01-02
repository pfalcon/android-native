#include <stdio.h>
#include <stdlib.h>

#include <hardware/hardware.h>

void print_module_info(const struct hw_module_t *mod_info)
{
    printf("id: %s\n", mod_info->id);
    printf("version: %d.%d\n", mod_info->version_major, mod_info->version_major);
    printf("name: %s\n", mod_info->name);
    printf("author: %s\n", mod_info->author);
}

void process_module(char *id)
{
    const struct hw_module_t *mod_info;
    int status = hw_get_module(id, &mod_info);
    if (status == 0) {
        printf("%s info:\n", id);
        print_module_info(mod_info);
    } else {
        printf("Error getting %s module\n", id);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    const struct hw_module_t *mod_info;
    int status;

    process_module("alsa");
    process_module("gralloc");
    process_module("copybit");
    process_module("hwcursor");
    process_module("lights");
    process_module("overlay");
    process_module("sensors");

    return 0;
}
