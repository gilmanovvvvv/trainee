#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int sharedData = 0;

void writerThread() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        sharedData = i;
        std::cout << "Writer wrote: " << i << std::endl;
        mtx.unlock();
    }
}

void readerThread() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        int data = sharedData;
        std::cout << "Reader read: " << data << std::endl;
        mtx.unlock();
    }
}

int main() {
    std::thread writer(writerThread);
    std::thread reader(readerThread);

    writer.join();
    reader.join();

    return 0;
}
