// Runs every TEST, prints the results and saves them to data/test-report.json.

#include <fstream>
#include <iostream>
#include <vector>

#include "json.hpp"
#include "test_framework.hpp"

namespace {

struct Test {
    std::string name;
    std::function<void()> body;
};

std::vector<Test>& allTests() {
    static std::vector<Test> tests;
    return tests;
}

std::vector<std::string> failuresOfCurrentTest;

const std::string TEST_REPORT_PATH = "data/test-report.json";

}  // namespace

void registerTest(const std::string& name, std::function<void()> body) {
    allTests().push_back({name, body});
}

void recordFailure(const std::string& message, const char* file, int line) {
    failuresOfCurrentTest.push_back(std::string(file) + ":" + std::to_string(line) + "  " + message);
}

int main() {
    nlohmann::json report = {{"tests", nlohmann::json::array()}};
    int passedCount = 0;
    std::vector<std::string> failedTestNames;

    std::cout << std::endl << "  Running tests" << std::endl;

    for (const Test& test : allTests()) {
        failuresOfCurrentTest.clear();
        try {
            test.body();
        } catch (const std::exception& error) {
            recordFailure(std::string("crashed: ") + error.what(), "?", 0);
        }

        bool passed = failuresOfCurrentTest.empty();
        if (passed) {
            passedCount++;
            std::cout << "    PASS  " << test.name << std::endl;
        } else {
            failedTestNames.push_back(test.name);
            std::cout << "    FAIL  " << test.name << std::endl;
            for (const std::string& failure : failuresOfCurrentTest) {
                std::cout << "            " << failure << std::endl;
            }
        }
        report["tests"].push_back({{"name", test.name}, {"passed", passed}});
    }

    report["passed"] = passedCount;
    report["failed"] = failedTestNames.size();
    std::ofstream(TEST_REPORT_PATH) << report.dump(2) << std::endl;

    std::cout << std::endl << "  " << passedCount << " passed, " << failedTestNames.size() << " failed" << std::endl;
    if (failedTestNames.empty()) {
        return 0;
    }

    std::cout << std::endl << "  Failing tests:" << std::endl;
    for (const std::string& name : failedTestNames) {
        std::cout << "    - " << name << std::endl;
    }
    std::cout << std::endl << "  The vault will not start until every test passes." << std::endl << std::endl;
    return 1;
}
