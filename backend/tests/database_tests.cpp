// Tests for the database that remembers progress, requests and credits.

#include "database.hpp"
#include "test_framework.hpp"

TEST(new_database_starts_with_the_given_credits) {
    VaultDatabase database(":memory:", 100);
    EXPECT_EQUAL(database.credits(), 100);
}

TEST(solved_missions_are_remembered_once) {
    VaultDatabase database(":memory:", 100);

    database.markMissionSolved(3);
    database.markMissionSolved(3);

    EXPECT_EQUAL(database.solvedMissions().size(), 1);
    EXPECT_EQUAL(database.solvedMissions()[0], 3);
}

TEST(latest_asset_request_is_the_most_recent_one) {
    VaultDatabase database(":memory:", 100);

    database.saveAssetRequest("{\"name\":\"first\"}");
    database.saveAssetRequest("{\"name\":\"second\"}");

    EXPECT_EQUAL(database.latestAssetRequest(), "{\"name\":\"second\"}");
}
