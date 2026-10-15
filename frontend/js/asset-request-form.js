// The brand asset request form: sends the form fields to the vault and shows the answer.

import { sendAssetRequest } from "./api.js";

function showStatus(text, styleName) {
  const status = document.getElementById("asset-request-status");
  status.textContent = text;
  status.className = "form-status " + styleName;
}

export function setupAssetRequestForm() {
  const form = document.getElementById("asset-request-form");

  form.addEventListener("submit", async (event) => {
    event.preventDefault();
    const fields = Object.fromEntries(new FormData(form));

    showStatus("Sending...", "");
    const result = await sendAssetRequest(fields);

    if (result.ok) {
      showStatus(result.data.message, "is-success");
    } else {
      showStatus(result.data.error || "Something went wrong.", "is-error");
    }
  });
}
