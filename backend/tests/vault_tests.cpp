// Tests for flags, the request limiter and the brand color check.

#include <chrono>

#include "brand_color_check.hpp"
#include "request_rate_limiter.hpp"
#include "secrets.hpp"
#include "test_framework.hpp"

TEST(a_wrong_flag_is_rejected) {
    EXPECT_FALSE(isCorrectFlag(0, "adbe{not_the_flag}"));
}

TEST(flags_for_missions_that_do_not_exist_are_rejected) {
    EXPECT_FALSE(isCorrectFlag(42, "adbe{anything}"));
    EXPECT_FALSE(isCorrectFlag(-1, "adbe{anything}"));
}

TEST(limiter_allows_requests_up_to_the_limit) {
    RequestRateLimiter limiter(3, std::chrono::seconds(60));

    EXPECT_TRUE(limiter.allowRequest());
    EXPECT_TRUE(limiter.allowRequest());
    EXPECT_TRUE(limiter.allowRequest());
}

TEST(limiter_blocks_requests_over_the_limit) {
    RequestRateLimiter limiter(2, std::chrono::seconds(60));
    limiter.allowRequest();
    limiter.allowRequest();

    EXPECT_FALSE(limiter.allowRequest());
}

TEST(adobe_red_is_recognized_in_rgb_and_hex) {
    EXPECT_TRUE(isAdobeRed("rgb(235, 16, 0)"));
    EXPECT_TRUE(isAdobeRed("#EB1000"));
}

TEST(other_colors_are_not_adobe_red) {
    EXPECT_FALSE(isAdobeRed("rgb(142, 142, 142)"));
    EXPECT_FALSE(isAdobeRed("#FF0000"));
}
