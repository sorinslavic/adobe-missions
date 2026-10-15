// Tests for the Adobe Stock shop.

#include "shop.hpp"
#include "test_framework.hpp"

TEST(buying_one_photo_costs_its_price) {
    const ShopItem* photo = findShopItem("desert-sunrise");

    CheckoutResult result = checkout(100, *photo, 1);

    EXPECT_TRUE(result.succeeded);
    EXPECT_EQUAL(result.creditsAfterCheckout, 75);
}

TEST(buying_three_icon_packs_costs_three_times_the_price) {
    const ShopItem* iconPack = findShopItem("icon-pack");

    CheckoutResult result = checkout(200, *iconPack, 3);

    EXPECT_TRUE(result.succeeded);
    EXPECT_EQUAL(result.creditsAfterCheckout, 80);
}

TEST(starting_credits_are_not_enough_for_the_vault_flag) {
    const ShopItem* vaultFlag = findShopItem(VAULT_FLAG_ITEM_ID);

    CheckoutResult result = checkout(STARTING_CREDITS, *vaultFlag, 1);

    EXPECT_FALSE(result.succeeded);
    EXPECT_EQUAL(result.message, "Not enough credits.");
    EXPECT_EQUAL(result.creditsAfterCheckout, STARTING_CREDITS);
}

TEST(buying_zero_items_is_rejected) {
    const ShopItem* photo = findShopItem("desert-sunrise");

    CheckoutResult result = checkout(100, *photo, 0);

    EXPECT_FALSE(result.succeeded);
}

TEST(unknown_items_are_not_sold) {
    EXPECT_TRUE(findShopItem("time-machine") == nullptr);
}
