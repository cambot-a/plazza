/*
** EPITECH PROJECT, 2026
** ThreadSafeOstream.hpp
** File description:
** ThreadSafeOstream
*/

#ifndef THREADSAFEOSTREAM_HPP_
    #define THREADSAFEOSTREAM_HPP_

#include <iostream>
#include <mutex>
#include <sstream>

extern std::mutex stream_mutex;

using Manipulator = std::ostream& (*)(std::ostream&);

class ThreadSafeOstream
{
private:
    std::stringstream buffer;
    std::ostream& stream;
public:
    ThreadSafeOstream(std::ostream& stream) : stream(stream) {}
    template<typename T>
    ThreadSafeOstream& operator<<(const T& value)
    {
        std::lock_guard<std::mutex> lock(stream_mutex);
        this->buffer << value;
        return *this;
    }
    ThreadSafeOstream& operator<<(Manipulator manip);
    void flush();
};

#endif /* THREADSAFEOSTREAM_HPP_ */