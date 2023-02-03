#include "fps_counter.h"

#include <iostream>

FramesCounter::FramesCounter() : frames_count_(0), last_time_point_(std::chrono::steady_clock::now()) {}

void FramesCounter::Step() {
    ++frames_count_;
    auto new_time_point = std::chrono::steady_clock::now();
    size_t milliseconds_count = std::chrono::duration_cast<std::chrono::microseconds>(new_time_point - last_time_point_).count() / 1000.0;
    if (milliseconds_count < FramesCounter::kMillisecondsInterval) {
        return;
    }

    double fps = static_cast<double>(frames_count_ * 1000) / static_cast<double>(milliseconds_count);
    std::cout << "FPS: " << static_cast<size_t>(fps) << '\n';
    last_time_point_ = new_time_point;
    frames_count_ = 0;
}


