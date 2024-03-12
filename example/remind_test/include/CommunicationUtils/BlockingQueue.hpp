// From https://gist.github.com/thelinked/6997598

#pragma once

#include <list>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue
{
public:
    void push(T const& _data)
    {
        {
            std::lock_guard<std::mutex> lock(guard);
            queue.push_back(_data);
        }
        signal.notify_one();
    }

    bool isEmpty() const
    {
        std::lock_guard<std::mutex> lock(guard);
        return queue.empty();
    }

    // Non blocking
    bool tryPopFront(T& outputValue)
    {
        std::lock_guard<std::mutex> lock(guard);
        if (queue.empty())
            return false;

        outputValue = queue.front();
        queue.pop_front();

        return true;
    }

    // Blocking
    T popFront()
    {
        std::unique_lock<std::mutex> lock(guard);
        while (queue.empty())
            signal.wait(lock);

        T ret = queue.front();
        queue.pop_front();

        return ret;
    }

    // Non blocking
    bool tryPopBack(T& outputValue)
    {
        std::lock_guard<std::mutex> lock(guard);
        if (queue.empty())
            return false;

        outputValue = queue.back();
        queue.pop_back();

        return true;
    }

    // Blocking
    T popBack()
    {
        std::unique_lock<std::mutex> lock(guard);
        while (queue.empty())
            signal.wait(lock);

        T ret = queue.back();
        queue.pop_back();

        return ret;
    }

//    bool tryWaitAndPop(T& _value, int _milli)
//    {
//        std::unique_lock<std::mutex> lock(guard);
//        while (queue.empty())
//        {
//            signal.wait_for(lock, std::chrono::milliseconds(_milli));
//            return false;
//        }

//        _value = queue.front();
//        queue.pop();
//        return true;
//    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(guard);
        queue.clear();
    }

    int getLen()
    {
        std::lock_guard<std::mutex> lock(guard);
        return queue.size();
    }

private:
    std::list<T> queue;
    mutable std::mutex guard;
    std::condition_variable signal;
};
