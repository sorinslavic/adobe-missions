// The Adobe Stock shop: lists items, shows credits and buys things.

import { buyItem, getShop } from "./api.js";
import { drawShopItemCover } from "./mission-covers.js";

function showShopMessage(html, styleName) {
  const message = document.getElementById("shop-message");
  message.innerHTML = html;
  message.className = "shop-message " + styleName;
}

function shopItemCard(item) {
  const special = item.id === "vault-flag" ? "is-special" : "";
  return `
    <article class="shop-item ${special}">
      ${drawShopItemCover(item.id)}
      <div class="shop-item-details">
        <b>${item.name}</b>
        <span class="shop-item-price">${item.price.toLocaleString()} credits · ${item.kind}</span>
        <div class="buy-row">
          <input class="quantity-input" type="number" min="1" value="1" aria-label="Quantity of ${item.name}">
          <button class="buy-button" data-item-id="${item.id}">Buy</button>
        </div>
      </div>
    </article>`;
}

function showCredits(credits) {
  document.getElementById("credits").textContent = credits.toLocaleString();
}

export async function loadShop() {
  const result = await getShop();
  showCredits(result.data.credits);
  document.getElementById("shop-items").innerHTML = result.data.items.map(shopItemCard).join("");
  showShopMessage("", "");
}

export function setupShop() {
  document.getElementById("shop-items").addEventListener("click", async (event) => {
    const button = event.target.closest(".buy-button");
    if (!button) {
      return;
    }

    const quantityInput = button.parentElement.querySelector(".quantity-input");
    const quantity = Number(quantityInput.value);
    const result = await buyItem(button.dataset.itemId, quantity);

    if (result.data.credits !== undefined) {
      showCredits(result.data.credits);
    }
    if (!result.ok) {
      showShopMessage(result.data.error, "is-error");
      return;
    }

    showShopMessage(result.data.message, "is-success");
    if (result.data.download) {
      showShopMessage(`${result.data.message} Your download: <code></code>`, "is-success");
      document.querySelector("#shop-message code").textContent = result.data.download;
    }
  });
}
