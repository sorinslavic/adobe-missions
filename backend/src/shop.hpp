// The Adobe Stock shop: what can be bought, and what it costs.
#pragma once

#include <string>
#include <vector>

const long long STARTING_CREDITS = 100;
const int MAXIMUM_QUANTITY_PER_ORDER = 999;
const std::string VAULT_FLAG_ITEM_ID = "vault-flag";

struct ShopItem {
    std::string id;
    std::string name;
    std::string kind;
    int price;
};

struct CheckoutResult {
    bool succeeded;
    std::string message;
    long long creditsAfterCheckout;
};

const std::vector<ShopItem>& shopCatalog();

// Returns the item with this id, or nullptr if the shop doesn't sell it.
const ShopItem* findShopItem(const std::string& itemId);

CheckoutResult checkout(long long currentCredits, const ShopItem& item, int quantity);
