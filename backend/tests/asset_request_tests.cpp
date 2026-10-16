// Tests for brand asset requests.
//
// Want to add your own test? Copy one of these, give it a new name that describes
// what it checks and run `make test`.

#include "asset_request_fields.hpp"
#include "asset_requests.hpp"
#include "test_framework.hpp"

using nlohmann::json;

namespace {

json completeRequest() {
    return {
        {"name", "Alex Rivera"},
        {"email", "alex@school.edu"},
        {"asset_type", "Logo pack"},
        {"reason", "School poster for the robotics club."},
    };
}

}  // namespace

TEST(complete_request_is_accepted) {
    ValidationResult result = validateAssetRequest(completeRequest());
    EXPECT_TRUE(result.isValid);
}

TEST(request_without_email_is_rejected) {
    json request = completeRequest();
    request.erase("email");

    ValidationResult result = validateAssetRequest(request);

    EXPECT_FALSE(result.isValid);
    EXPECT_EQUAL(result.errorMessage, "missing field: email");
}

TEST(request_with_empty_name_is_rejected) {
    json request = completeRequest();
    request["name"] = "";

    ValidationResult result = validateAssetRequest(request);

    EXPECT_FALSE(result.isValid);
    EXPECT_EQUAL(result.errorMessage, "missing field: name");
}

TEST(request_with_unknown_field_is_rejected) {
    json request = completeRequest();
    request["favorite_color"] = "purple";

    ValidationResult result = validateAssetRequest(request);

    EXPECT_FALSE(result.isValid);
    EXPECT_EQUAL(result.errorMessage, "unknown field: favorite_color");
}

TEST(asset_request_form_has_exactly_four_fields) {
    EXPECT_EQUAL(ALLOWED_ASSET_REQUEST_FIELDS.size(), 4);
}
