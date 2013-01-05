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
    if (setuid(1000) < 0)
        printf("Could not setuid\n");

    // set up the thread-pool
//    sp<ProcessState> proc(ProcessState::self());
//    ProcessState::self()->startThreadPool();

    printf("Creating new SurfaceComposerClient...\n");
    printf("%x\n", new SurfaceComposerClient());
    sp<SurfaceComposerClient> client = new SurfaceComposerClient();
    printf("client = %#x\n", client.get());
    if (!client.get())
        printf("Failed getting client\n");
    else
        printf("Got client\n");

    sp<ISurfaceComposer> serv = ComposerService::getComposerService();
    printf("ISurfaceComposer: %x\n", serv.get());
    sp<IMemoryHeap> serv_cblk = serv->getCblk();
    printf("serv_cblk: %x\n", serv_cblk.get());
    printf("serv_cblk base: %x\n", serv_cblk->getBase());

    sp<ISurfaceComposerClient> cli = serv->createConnection();
    printf("ISurfaceComposerClient: %x\n", cli.get());

    sp<IMemoryHeap> cli_cblk = cli->getControlBlock();
    printf("cli_cblk: %x\n", cli_cblk.get());
    if (cli_cblk.get())
        printf("cli_cblk base: %x\n", cli_cblk->getBase());
}
