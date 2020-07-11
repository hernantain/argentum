#ifndef _SERVER_GAME_LOOP_THREAD
#define _SERVER_GAME_LOOP_THREAD

#include <atomic>
#include <unistd.h>

#include "../common_files/common_sockets.h"
#include "../common_files/common_thread.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_protocol_message.h"

class GameLoopThread : public Thread {
private:
    Queue &queue;
    std::atomic<bool> running;

public:
    GameLoopThread(Queue &queue);

    virtual void run() override;
};

#endif
