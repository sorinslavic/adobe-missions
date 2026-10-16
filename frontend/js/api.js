// All calls from the website to the vault's backend.

async function sendJson(method, url, body) {
  const response = await fetch(url, {
    method: method,
    headers: { "Content-Type": "application/json" },
    body: body === undefined ? undefined : JSON.stringify(body),
  });
  const data = await response.json().catch(() => ({}));
  return { status: response.status, ok: response.ok, data: data };
}

export function getProgress() {
  return sendJson("GET", "/api/progress");
}

export function submitFlag(missionId, flag) {
  return sendJson("POST", "/api/flags", { mission: missionId, flag: flag });
}

export function sendAssetRequest(fields) {
  return sendJson("POST", "/api/asset-requests", fields);
}

export function checkBrandColor(color) {
  return sendJson("POST", "/api/brand-check", { color: color });
}

export function checkDepartmentReadiness() {
  return sendJson("GET", "/api/department-check");
}

export function getShop() {
  return sendJson("GET", "/api/shop");
}

export function buyItem(itemId, quantity) {
  return sendJson("POST", "/api/shop/checkout", { item: itemId, quantity: quantity });
}
