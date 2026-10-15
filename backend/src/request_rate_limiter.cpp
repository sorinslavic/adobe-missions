// Limits how many requests are accepted within a sliding window of time.

#include "request_rate_limiter.hpp"

RequestRateLimiter::RequestRateLimiter(int maximumRequests, std::chrono::seconds timeWindow)
    : maximumRequests(maximumRequests), timeWindow(timeWindow) {}

bool RequestRateLimiter::allowRequest() {
    Clock::time_point now = Clock::now();
    forgetRequestsOlderThanTheWindow(now);

    recentRequestTimes.push_back(now);
    int requestsInTheWindow = static_cast<int>(recentRequestTimes.size());
    return requestsInTheWindow <= maximumRequests;
}

void RequestRateLimiter::forgetRequestsOlderThanTheWindow(Clock::time_point now) {
    while (!recentRequestTimes.empty() && now - recentRequestTimes.front() > timeWindow) {
        recentRequestTimes.pop_front();
    }
}
