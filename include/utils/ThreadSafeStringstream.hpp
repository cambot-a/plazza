/*
** EPITECH PROJECT, 2026
** ThreadSafeStringstream.hpp
** File description:
** ThreadSafeStringstream
*/

#ifndef THREADSAFESTRINGSTREAM_HPP_
    #define THREADSAFESTRINGSTREAM_HPP_
    #include "ThreadSafeOstream.hpp"

class ThreadSafeStringstream
{
private:
    std::stringstream buffer;
public:
    ThreadSafeStringstream() {}
    template<typename T>
    ThreadSafeStringstream& operator<<(const T& value)
    {
        std::lock_guard<std::mutex> lock(stream_mutex); //
        this->buffer << value;
        return *this;
    }
    ThreadSafeStringstream& operator<<(Manipulator manip);
    std::string str();
};

#endif /* THREADSAFESTRINGSTREAM_HPP_ */