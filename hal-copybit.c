#include <stdio.h>
#include <stdlib.h>

#include <hardware/hardware.h>
#include <hardware/gralloc.h>
#include <hardware/copybit.h>


void print_module_info(const struct hw_module_t *mod_info)
{
    printf("version: %d.%d\n", mod_info->version_major, mod_info->version_major);
    printf("id: %s\n", mod_info->id);
    printf("name: %s\n", mod_info->name);
    printf("author: %s\n", mod_info->author);
}


struct copybit_rect_region_t {
    struct copybit_region_t _superclass;
    struct copybit_rect_t rect;
    int _count;
};

static int copybit_rect_region_next(struct copybit_region_t const *region, struct copybit_rect_t *rect)
{
    struct copybit_rect_region_t *cb = (struct copybit_rect_region_t*)region;
printf("in copybit_rect_region_next\n");
    if (cb->_count > 0)
      return 0;
    cb->_count++;
    memcpy(rect, &cb->rect, sizeof(cb->rect));
    return 1;
}

int copybit_rect_region_init(struct copybit_rect_region_t *region)
{
    region->_superclass.next = copybit_rect_region_next;
    region->_count = 0;
}


int main(int argc, char *argv[])
{
    int i, status;
    const struct hw_module_t *gralloc_mod = NULL;
    const struct hw_module_t *copybit_mod = NULL;
    const gralloc_module_t *gralloc = NULL;
    framebuffer_device_t *fb_dev = NULL;
    alloc_device_t *gr_dev = NULL;
    struct copybit_device_t * copybit_dev = NULL;

    status = hw_get_module("gralloc", &gralloc_mod);
    gralloc = (gralloc_module_t*)gralloc_mod;
    status = hw_get_module("copybit", &copybit_mod);

    printf("gralloc info:\n");
    print_module_info(gralloc_mod);
    printf("copybit info:\n");
    print_module_info(copybit_mod);

    framebuffer_open(gralloc_mod, &fb_dev);
    gralloc_open(gralloc_mod, &gr_dev);
    printf("fb_dev=%#x\n", fb_dev);
    printf("gralloc_dev=%#x\n", gr_dev);
    printf("framebuffer size: %dx%d, format: %d\n", fb_dev->width, fb_dev->height, fb_dev->format);

    buffer_handle_t buffer_h;
    int stride = 0;
    status = gr_dev->alloc(gr_dev, fb_dev->width, fb_dev->height, fb_dev->format,
      GRALLOC_USAGE_HW_FB, &buffer_h, &stride);
    printf("alloc status=%d,stride=%d\n", status, stride);
    short *vaddr;
    status = gralloc->lock(gralloc, buffer_h, GRALLOC_USAGE_SW_WRITE_OFTEN, 0, 0, fb_dev->width, fb_dev->height, (void**)&vaddr);
    printf("lock status=%d, vaddr=%#x\n", status, vaddr);
    for (i = 32000; i > 0; i--) *vaddr++ = 0xaa55;


    {
        struct copybit_image_t src;
        struct copybit_image_t dst;
        struct copybit_rect_t src_rect = {0, 0, 128, 64};
        struct copybit_rect_t dst_rect = {200, 400, 328, 464};
        struct copybit_rect_region_t region;

        src.w = fb_dev->width;
        src.h = fb_dev->height;
        src.format = fb_dev->format;
        src.base = 0;
        src.handle = 0;
        src.base = vaddr;
        src.handle = buffer_h;

        dst.w = fb_dev->width;
        dst.h = fb_dev->height;
        dst.format = fb_dev->format;
        dst.base = vaddr;
        dst.handle = buffer_h;

        copybit_rect_region_init(&region);
        region.rect.l = 0;
        region.rect.t = 0;
        region.rect.r = fb_dev->width;
        region.rect.b = fb_dev->height;

        copybit_open(copybit_mod, &copybit_dev);
        status = copybit_dev->stretch(copybit_dev, &dst, &src, &dst_rect, &src_rect, (struct copybit_region_t *)&region);
        printf("copybit status=%d\n", status);
    }

    status = gralloc->unlock(gralloc, buffer_h);
    printf("unlock status=%d\n", status);
    fb_dev->post(fb_dev, buffer_h);

    return 0;
}
