#include <time.h>

#include <cutils/memory.h>

#include <utils/IPCThreadState.h>
#include <utils/ProcessState.h>
#include <utils/IServiceManager.h>
#include <utils/Log.h>

#include <ui/Surface.h>
#include <ui/ISurface.h>
#include <ui/Overlay.h>
#include <ui/SurfaceComposerClient.h>
#include <ui/DisplayInfo.h>

#define DONUT

using namespace android;

namespace android {
class Test {
public:
    static const sp<ISurface>& getISurface(const sp<Surface>& s) {
        return s->getISurface();
    }
};
};

#define DISPLAY_ID 0
#define NUM_ITER 50

int main(int argc, char** argv)
{
    printf("Starting...\n");
    // set up the thread-pool
//    sp<ProcessState> proc(ProcessState::self());
//    ProcessState::self()->startThreadPool();

    // create a client to surfaceflinger
    sp<SurfaceComposerClient> client = new SurfaceComposerClient();
    DisplayInfo di;
    client->getDisplayInfo(DISPLAY_ID, &di);
    printf("Display:\n");
    printf("  width: %d\n", di.w);
    printf("  height: %d\n", di.h);
    printf("  format:\n");
    printf("    components: %d\n", di.pixelFormatInfo.components);
    printf("  fps: %f\n", di.fps);
    printf("  density: %f\n", di.density);
    
    // create pushbuffer surface
    sp<Surface> surface = client->createSurface(getpid(), DISPLAY_ID, 800, 480, 
            PIXEL_FORMAT_RGB_565);


    client->openTransaction();
    // Be on top of everything
    surface->setLayer(100000);
    client->closeTransaction();

/*    client->openTransaction();
    surface->setSize(320, 240);
    client->closeTransaction();
*/


    Surface::SurfaceInfo info;
    timeval start = {0};
    timeval end = {0};
    timeval duration;
    gettimeofday(&start, NULL);
    for (int cnt = 0; cnt < NUM_ITER; cnt++) {

    surface->lock(&info);
#ifndef DONUT
    ssize_t bpr = info.s * bytesPerPixel(info.format);
#else
    ssize_t bpr = info.bpr;
#endif
    android_memset16((uint16_t*)info.bits, 0xF800, bpr*info.h);
    surface->unlockAndPost();

/*    surface->lock(&info);
    android_memset16((uint16_t*)info.bits, 0x07E0, bpr*info.h);
    surface->unlockAndPost();

    surface->lock(&info);
    android_memset16((uint16_t*)info.bits, 0x001F, bpr*info.h);
    surface->unlockAndPost();
*/    }
    gettimeofday(&end, NULL);
    timersub(&end, &start, &duration);

    printf("duration: %d.%ds\n", duration.tv_sec, duration.tv_usec);
    printf("FPS: %f\n", 3 * NUM_ITER * 1.0 / (duration.tv_sec + duration.tv_usec / 1000000.0));

    client->openTransaction();
    surface->hide();
    client->closeTransaction();

    sleep(1);

    client->openTransaction();
    surface->show();
    client->closeTransaction();

    sleep(1);

//    IPCThreadState::self()->joinThreadPool();
    return 0;
}
