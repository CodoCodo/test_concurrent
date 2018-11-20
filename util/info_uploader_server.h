#ifndef _INFO_UPLOADER_SERVER_H
#define _INFO_UPLOADER_SERVER_H

#include <deque>
#include <mutex>
#include <thread>
#include <future>
#include <utility>
#include <boost/function.hpp>

typedef std::function<int()> UploadFuncT;

class InfoUploaderServer {
public:
    ~InfoUploaderServer();

    std::future<int> pushTask(UploadFuncT f);
    static void ServeThread(InfoUploaderServer *pThis);
    static InfoUploaderServer & instance();
private:
    InfoUploaderServer();
    void run();

    int mbWork;
    std::thread mServeThread;
    std::mutex mMutex;
    std::deque< std::packaged_task<int()> > mTasks;
};

#endif /* _INFO_UPLOADER_SERVER_H */
