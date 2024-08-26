#include "./Runner/runner.h"
#include "./GUI/ui.h"

int main(int argc, char *argv[]) {
    std::shared_ptr<Runner> runner = std::make_shared<Runner>();
    
    std::thread runnerThread(runner->createThreads());
    
    std::shared_ptr<UI> ui = std::make_shared<UI>(argc, argv, runner->getBuffer());
    
    runnerThread.join();

    return 0;
}
