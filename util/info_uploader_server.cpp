#include <unistd.h>
#include "info_uploader_server.h"

using namespace std;

void InfoUploaderServer::ServeThread(InfoUploaderServer *pThis) {
    pThis->run();
}

InfoUploaderServer::InfoUploaderServer()
:mbWork(true),
 mServeThread(ServeThread, this)
{
}

InfoUploaderServer::~InfoUploaderServer() {
    mbWork = false;
    if (mServeThread.joinable()) {
        mServeThread.join();
    }
}

std::future<int> InfoUploaderServer::pushTask(UploadFuncT f) {
    std::packaged_task<int()> task(f);
    std::future<int> res = task.get_future();
    std::lock_guard<std::mutex> lk(mMutex);
    mTasks.push_back(std::move(task));
    return res;
}


void InfoUploaderServer::run() {
    while (mbWork) {
        std::packaged_task<int()> task;
        {
            std::lock_guard<std::mutex> lk(mMutex);
            if (mTasks.empty()) {
                usleep(1000);
                continue;
            }
            task = std::move(mTasks.front());
            mTasks.pop_front();
        }
        task();
    }
}

InfoUploaderServer & InfoUploaderServer::instance() {
    static InfoUploaderServer server;
    return server;
}

