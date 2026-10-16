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
