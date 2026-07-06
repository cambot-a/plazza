/*
** EPITECH PROJECT, 2026
** ThreadSafeOstream.cpp
** File description:
** ThreadSafeOstream
*/

#include "ThreadSafeOstream.hpp"
#include "ThreadSafeStringstream.hpp"

ThreadSafeOstream& ThreadSafeOstream::operator<<(Manipulator manip)
{
    if (manip == static_cast<Manipulator>(std::endl)) {
        flush();
    } else {
        std::lock_guard<std::mutex> lock(stream_mutex);
        manip(this->buffer);
    }
    return *this;
}

void ThreadSafeOstream::flush()
{
    std::lock_guard<std::mutex> lock(stream_mutex);
    this->stream << this->buffer.str() << std::endl;
    this->buffer.str("");
    this->buffer.clear();
}

ThreadSafeStringstream& ThreadSafeStringstream::operator<<(Manipulator manip)
{
    if (manip == static_cast<Manipulator>(std::endl)) {
        *this << "\n";
    } else {
        std::lock_guard<std::mutex> lock(stream_mutex);
        manip(this->buffer);
    }
    return *this;
}

std::string ThreadSafeStringstream::str()
{
    std::lock_guard<std::mutex> lock(stream_mutex);
    std::string result = this->buffer.str();
    this->buffer.str("");
    this->buffer.clear();
    return result;
}
