#include "blockqueue.h"


#include <iostream>
#include <string>

class ITask
{
public:
    virtual void Doing() = 0;
    virtual ~ITask() {};
};


class ImplTask : public ITask
{
public:
    ImplTask(const char* s) : s_(s)
    {

    }

    virtual void Doing()
    {
        std::cout << "Impl: " << s_ << std::endl;
    }

private:
    std::string s_;
};

int main()
{
    BlockQueue<ITask*> queue;

    ImplTask task("1");

    queue.Put(&task);

    ITask* t = queue.Take();

    t->Doing();
}