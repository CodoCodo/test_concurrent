#include <iostream>
#include "info_uploader_server.h"

using namespace std;

int upload_func(int frame_id) {
    sleep(2);
    cout << __FUNCTION__ << '\t' << __LINE__ << '\t' << frame_id << endl;
    return 12;
}

int main(int argc, char *argv[]) {
    int tmpId = 34;
    cout << "before push" << endl;
    std::future<int> res = InfoUploaderServer::instance().pushTask(std::bind(upload_func, tmpId));
    cout << "after push" << endl;
    cout << "return value is " << res.get() << endl;
    return 0;
}

