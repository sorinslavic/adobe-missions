// Stores solved missions, asset requests and the wallet in SQLite.

#include "database.hpp"

#include <stdexcept>

#include "sqlite3.h"

namespace {

// A prepared SQL statement that cleans itself up when it goes out of scope.
class Statement {
public:
    Statement(sqlite3* connection, const std::string& sql) {
        if (sqlite3_prepare_v2(connection, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
            throw std::runtime_error(std::string("Database error: ") + sqlite3_errmsg(connection));
        }
    }
    ~Statement() { sqlite3_finalize(statement); }

    void bindNumber(int position, long long value) { sqlite3_bind_int64(statement, position, value); }
    void bindText(int position, const std::string& value) {
        sqlite3_bind_text(statement, position, value.c_str(), -1, SQLITE_TRANSIENT);
    }

    // Moves to the next result row. Returns false when there are no more rows.
    bool nextRow() { return sqlite3_step(statement) == SQLITE_ROW; }
    void run() { sqlite3_step(statement); }

    long long numberColumn(int column) { return sqlite3_column_int64(statement, column); }

private:
    sqlite3_stmt* statement = nullptr;
};

}  // namespace

VaultDatabase::VaultDatabase(const std::string& filePath, long long startingCredits) {
    if (sqlite3_open(filePath.c_str(), &connection) != SQLITE_OK) {
        throw std::runtime_error("Could not open the database at " + filePath);
    }
    createTablesIfMissing(startingCredits);
}

VaultDatabase::~VaultDatabase() {
    sqlite3_close(connection);
}

void VaultDatabase::runStatement(const std::string& sql) {
    Statement(connection, sql).run();
}

void VaultDatabase::createTablesIfMissing(long long startingCredits) {
    runStatement(
        "CREATE TABLE IF NOT EXISTS solved_missions ("
        "  mission_number INTEGER PRIMARY KEY,"
        "  solved_at TEXT DEFAULT CURRENT_TIMESTAMP)");
    runStatement(
        "CREATE TABLE IF NOT EXISTS asset_requests ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  created_at TEXT DEFAULT CURRENT_TIMESTAMP,"
        "  fields_json TEXT NOT NULL)");
    runStatement(
        "CREATE TABLE IF NOT EXISTS wallet ("
        "  id INTEGER PRIMARY KEY CHECK (id = 1),"
        "  credits INTEGER NOT NULL)");

    Statement createWallet(connection, "INSERT OR IGNORE INTO wallet (id, credits) VALUES (1, ?)");
    createWallet.bindNumber(1, startingCredits);
    createWallet.run();
}

void VaultDatabase::markMissionSolved(int missionNumber) {
    Statement insert(connection, "INSERT OR IGNORE INTO solved_missions (mission_number) VALUES (?)");
    insert.bindNumber(1, missionNumber);
    insert.run();
}

std::vector<int> VaultDatabase::solvedMissions() {
    std::vector<int> missionNumbers;
    Statement query(connection, "SELECT mission_number FROM solved_missions ORDER BY mission_number");
    while (query.nextRow()) {
        missionNumbers.push_back(static_cast<int>(query.numberColumn(0)));
    }
    return missionNumbers;
}

void VaultDatabase::saveAssetRequest(const std::string& fieldsAsJson) {
    Statement insert(connection, "INSERT INTO asset_requests (fields_json) VALUES (?)");
    insert.bindText(1, fieldsAsJson);
    insert.run();
}

long long VaultDatabase::credits() {
    Statement query(connection, "SELECT credits FROM wallet WHERE id = 1");
    query.nextRow();
    return query.numberColumn(0);
}

void VaultDatabase::setCredits(long long newCredits) {
    Statement update(connection, "UPDATE wallet SET credits = ? WHERE id = 1");
    update.bindNumber(1, newCredits);
    update.run();
}
