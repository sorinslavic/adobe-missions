// Limits how many requests are accepted within a sliding window of time.
#pragma once

#include <chrono>
#include <deque>

class RequestRateLimiter {
public:
    RequestRateLimiter(int maximumRequests, std::chrono::seconds timeWindow);

    // Records a new request. Returns false when there were too many requests recently.
    bool allowRequest();

private:
    using Clock = std::chrono::steady_clock;

    int maximumRequests;
    std::chrono::seconds timeWindow;
    std::deque<Clock::time_point> recentRequestTimes;

    void forgetRequestsOlderThanTheWindow(Clock::time_point now);
};
