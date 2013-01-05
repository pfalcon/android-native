#include <time.h>

#define FROYO_PLUS

//#include <binder/ProcessState.h>
#include <binder/IMemory.h>

#include <ui/DisplayInfo.h>
#ifdef FROYO_PLUS
#include <surfaceflinger/SurfaceComposerClient.h>
#include <surfaceflinger/ISurfaceComposer.h>
#else
#include <ui/SurfaceComposerClient.h>
#endif

using namespace android;

#define DISPLAY_ID 0

int main(int argc, char** argv)
{
    printf("Creating new SurfaceComposerClient...\n");
    printf("%x\n", new SurfaceComposerClient());
    sp<SurfaceComposerClient> client = new SurfaceComposerClient();
    DisplayInfo di;
    printf("client->getDisplayInfo: %x\n", client->getDisplayInfo);

    client->getDisplayInfo(DISPLAY_ID, &di);
    printf("Display #%d:\n", DISPLAY_ID);
    printf("  width: %d\n", di.w);
    printf("  height: %d\n", di.h);
    printf("  format:\n");
    printf("    components: %d\n", di.pixelFormatInfo.components);
    printf("  orientation: %d\n", di.orientation);
    printf("  reserved: 0x%x 0x%x 0x%x\n", di.reserved[0], di.reserved[1], di.reserved[2]);
    printf("  fps: %f\n", di.fps);
    printf("  density: %f\n", di.density);
    printf("  xdpi: %f\n", di.xdpi);
    printf("  ydpi: %f\n", di.ydpi);
    return 0;
}
