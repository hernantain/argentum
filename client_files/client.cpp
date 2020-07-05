
#include "client_game.h"
#include <chrono>
#include <ctime>
#include <thread>

int main(int argc, char* argv[]) {

    // auto t_start = std::chrono::high_resolution_clock::now();

    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // auto t_end = std::chrono::high_resolution_clock::now();


    // std::cout << std::fixed << std::setprecision(2) << "Wall clock time passed: "
    //           << std::chrono::duration<double, std::milli>(t_end-t_start).count()
    //           << " ms\n";

    // std::cout << 7 % 5 << std::endl;

    Game game;
    game.run();

	return 0;
}


