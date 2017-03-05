#include "blockqueue.h"

#include <cstdio>
#include <string>
#include <vector>

#include <process.h>
#include <windows.h>
#include <time.h>

struct Data
{
    std::string cust_no;
    int time_stamp;
};


const int no_producers = 5;
const int no_consumers = 2;
const int per_thread_nums = 100;

int all_sum = 0;
Mutex all_sum_mtx;

bool IsComplete()
{
    MutexLock lg(&all_sum_mtx);
    if (all_sum == (no_producers * per_thread_nums))
        return true;
    all_sum++;
    return false;
}

void producer(void* param)
{
    BlockQueue<Data>* bq = (BlockQueue<Data>*)param;

    for (int i = 0; i < per_thread_nums; i++)
    {
        Data data;
        data.cust_no = "100086";
        data.time_stamp = (int)time(NULL);
        bq->Put(data);
        Sleep(10);
    }
}

void consumer(void* param)
{
    BlockQueue<Data>* bq = (BlockQueue<Data>*)param;
    for (;;)
    {
        if (IsComplete())
            return;
        Data data = bq->Take();

        std::printf("%s %d\n", data.cust_no.c_str(), data.time_stamp);
    }
}

int main()
{
    BlockQueue<Data> block_queue;

    std::vector<HANDLE> handles;

    for (int i = 0; i < no_producers; i++)
        handles.push_back((HANDLE)_beginthread(&producer, 0, &block_queue));

    for (int i = 0; i < no_consumers; i++)
        handles.push_back((HANDLE)_beginthread(&consumer, 0, &block_queue));

    for (size_t i = 0; i < handles.size(); i++)
        WaitForSingleObject(handles[i], INFINITE);

    std::printf("%d test ok!", all_sum);
    return 0;
}