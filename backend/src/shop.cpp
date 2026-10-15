// The Adobe Stock shop: what can be bought, and what it costs.

#include "shop.hpp"

const std::vector<ShopItem>& shopCatalog() {
    static const std::vector<ShopItem> catalog = {
        {"desert-sunrise", "Desert sunrise", "Photo", 25},
        {"icon-pack", "Icon pack", "Vector", 40},
        {"font-license", "Font license", "Font", 60},
        {VAULT_FLAG_ITEM_ID, "Vault Flag", "One per intern", 1000},
    };
    return catalog;
}

const ShopItem* findShopItem(const std::string& itemId) {
    for (const ShopItem& item : shopCatalog()) {
        if (item.id == itemId) {
            return &item;
        }
    }
    return nullptr;
}

CheckoutResult checkout(long long currentCredits, const ShopItem& item, int quantity) {
    if (quantity == 0) {
        return {false, "Choose how many you want to buy.", currentCredits};
    }
    if (quantity > MAXIMUM_QUANTITY_PER_ORDER) {
        return {false, "You can buy at most 999 at a time.", currentCredits};
    }

    long long totalCost = static_cast<long long>(item.price) * quantity;
    if (totalCost > currentCredits) {
        return {false, "Not enough credits.", currentCredits};
    }

    std::string message = "Bought " + std::to_string(quantity) + " x " + item.name + ".";
    return {true, message, currentCredits - totalCost};
}
