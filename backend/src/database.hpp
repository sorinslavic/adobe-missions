// Everything the vault remembers between restarts, stored in a SQLite database file.
#pragma once

#include <string>
#include <vector>

struct sqlite3;

class VaultDatabase {
public:
    // Opens (or creates) the database file. Use ":memory:" for a temporary database.
    VaultDatabase(const std::string& filePath, long long startingCredits);
    ~VaultDatabase();

    void markMissionSolved(int missionNumber);
    std::vector<int> solvedMissions();

    void saveAssetRequest(const std::string& fieldsAsJson);

    long long credits();
    void setCredits(long long newCredits);

private:
    sqlite3* connection = nullptr;

    void runStatement(const std::string& sql);
    void createTablesIfMissing(long long startingCredits);
};
