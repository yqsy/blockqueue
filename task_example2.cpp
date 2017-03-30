#include "blockqueue.h"


#include <iostream>
#include <string>
#include <functional>

class Task
{
public:
    std::function<void()> call_;
};


int main()
{
    BlockQueue<Task*> queue;

    Task task;

    task.call_ = []
    {
        std::cout << "1" << std::endl;
    };

    queue.Put(&task);

    Task* t = queue.Take();
    t->call_();
}