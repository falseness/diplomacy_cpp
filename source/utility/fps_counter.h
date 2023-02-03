#pragma once

#include <chrono>


class FramesCounter {
    std::size_t frames_count_;
    std::chrono::steady_clock::time_point last_time_point_;
    static constexpr size_t kMillisecondsInterval = 5 * 1000;
public:
    FramesCounter();
    void Step();
};