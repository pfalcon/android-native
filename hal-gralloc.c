#include <stdio.h>
#include <stdlib.h>

#include <hardware/hardware.h>
#include <hardware/gralloc.h>


void print_module_info(const struct hw_module_t *mod_info)
{
    printf("version: %d.%d\n", mod_info->version_major, mod_info->version_major);
    printf("id: %s\n", mod_info->id);
    printf("name: %s\n", mod_info->name);
    printf("author: %s\n", mod_info->author);
}

int main(int argc, char *argv[])
{
    int i;
    const struct hw_module_t *mod_info = NULL;
    const gralloc_module_t *gralloc = NULL;
    framebuffer_device_t *fb_dev = NULL;
    alloc_device_t *gr_dev = NULL;

    int status = hw_get_module("gralloc", &mod_info);
    gralloc = (gralloc_module_t*)mod_info;
    printf("gralloc info:\n");
    print_module_info(mod_info);

    framebuffer_open(mod_info, &fb_dev);
    gralloc_open(mod_info, &gr_dev);
    printf("fb_dev=%#x\n", fb_dev);
    printf("gralloc_dev=%#x\n", gr_dev);
    if (!fb_dev || !gr_dev) {
        printf("fbdev/gralloc failed\n");
        exit(1);
    }

    printf("framebuffer size: %dx%d, format: %d\n", fb_dev->width, fb_dev->height, fb_dev->format);
    int pixel_size;
    switch (fb_dev->format) {
        case HAL_PIXEL_FORMAT_RGB_565:
//        case HAL_PIXEL_FORMAT_RGB_5551:
//        case HAL_PIXEL_FORMAT_RGB_4444:
            pixel_size = 2;
            break;
        // a bit unsafe
        default:
            pixel_size = 4;
            break;
    }

    buffer_handle_t buffer_h;
    int stride = 0;
    status = gr_dev->alloc(gr_dev, fb_dev->width, fb_dev->height, fb_dev->format,
      GRALLOC_USAGE_HW_FB, &buffer_h, &stride);
    printf("alloc status=%d\n", status);
    printf("alloc buffer_handle=%#x, stride=%d\n", buffer_h, stride);

    char *vaddr;
    status = gralloc->lock(gralloc, buffer_h, GRALLOC_USAGE_SW_WRITE_OFTEN, 0, 0, fb_dev->width, fb_dev->height, (void**)&vaddr);
    printf("lock status=%d, vaddr=%#x\n", status, vaddr);

    if (pixel_size == 2) {
        for (i = fb_dev->width * fb_dev->height / 2; i--;) {
            *(short*)vaddr = 0xaa55;
            vaddr += 2;
        }
    } else {
        for (i = fb_dev->width * fb_dev->height / 2; i--;) {
            *(long*)vaddr = 0xaaaa5555;
            vaddr += 4;
        }
    }

    status = gralloc->unlock(gralloc, buffer_h);
    printf("unlock status=%d\n", status);
    fb_dev->post(fb_dev, buffer_h);

    return 0;
}
