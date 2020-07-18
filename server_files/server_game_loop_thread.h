#ifndef _SERVER_GAME_LOOP_THREAD
#define _SERVER_GAME_LOOP_THREAD

#include <atomic>
#include <unistd.h>

#include "../common_files/common_sockets.h"
#include "../common_files/common_thread.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_protocol_message.h"
#include "../common_files/common_message_to_server.h"

class GameLoopThread : public Thread {
private:
    Queue_2 &queue;
    std::atomic<bool> running;

public:
    GameLoopThread(Queue_2 &queue);

    virtual void run() override;
};

#endif
