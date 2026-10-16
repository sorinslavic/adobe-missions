# Backend

The vault's server, written in C++. It serves the website and answers the website's requests.

## How a request travels

```
Browser  ──►  http_routes.cpp  ──►  the file that knows the topic  ──►  database.cpp
                (which URL?)          (shop.cpp, asset_requests.cpp, ...)    (save / load)
```

## Files in `src/`

| File | What it does |
| --- | --- |
| `main.cpp` | Starts everything: opens the database, prints the boot log, starts the server |
| `http_routes.cpp` | Connects each URL (like `/api/shop`) to the code that handles it |
| `database.cpp` | Saves and loads data in a SQLite database (`data/vault.db`) |
| `asset_request_fields.hpp` | The list of fields a brand asset request may contain |
| `asset_requests.cpp` | Checks that a brand asset request is complete and valid |
| `request_rate_limiter.cpp` | Limits how many requests are accepted in a short time |
| `brand_color_check.cpp` | Checks whether a color is Adobe Red |
| `department_check.cpp` | Checks whether departments are supported |
| `shop.cpp` | The Adobe Stock shop: items, prices and checkout |
| `secrets.cpp` | Stores secrets scrambled and checks flags |

## Tests in `tests/`

| File | What it tests |
| --- | --- |
| `asset_request_tests.cpp` | Brand asset requests |
| `shop_tests.cpp` | The shop |
| `database_tests.cpp` | The database |
| `vault_tests.cpp` | Flags, the rate limiter and the brand color check |
| `test_framework.hpp` | The tiny test framework (`TEST`, `EXPECT_TRUE`, `EXPECT_EQUAL`) |
| `run_all_tests.cpp` | Runs every test and saves a report to `data/test-report.json` |

Run them with `make test`. The vault only starts when every test passes.

A test looks like this:

```cpp
TEST(buying_one_photo_costs_its_price) {
    const ShopItem* photo = findShopItem("desert-sunrise");

    CheckoutResult result = checkout(100, *photo, 1);

    EXPECT_TRUE(result.succeeded);
    EXPECT_EQUAL(result.creditsAfterCheckout, 75);
}
```

## `vendor/`

Libraries written by other people. You don't need to read them.

| File | Library |
| --- | --- |
| `httplib.h` | [cpp-httplib](https://github.com/yhirose/cpp-httplib) — the web server |
| `json.hpp` | [nlohmann/json](https://github.com/nlohmann/json) — reading and writing JSON |
| `sqlite3.c`, `sqlite3.h` | [SQLite](https://sqlite.org) — the database |
| `picosha2.h` | [PicoSHA2](https://github.com/okdshin/PicoSHA2) — SHA-256 fingerprints |
