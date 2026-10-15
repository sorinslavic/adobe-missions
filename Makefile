# Pixel Vault
#
#   make start   build the vault, run the tests, then open the vault
#   make test    build and run the tests only
#   make reset   forget all progress (solved missions, credits, requests)
#   make clean   delete everything that was compiled

CXXFLAGS := -std=c++17 -O1 -Wall -Wextra -Wno-sign-compare -Ibackend/src -isystem backend/vendor -MMD -MP
CFLAGS   := -O1 -DSQLITE_THREADSAFE=1 -DSQLITE_OMIT_LOAD_EXTENSION
LDLIBS   := -pthread -lm

BUILD_FOLDER := build

APP_SOURCES    := $(wildcard backend/src/*.cpp)
SHARED_SOURCES := $(filter-out backend/src/main.cpp, $(APP_SOURCES))
TEST_SOURCES   := $(wildcard backend/tests/*.cpp)

APP_OBJECTS  := $(APP_SOURCES:%.cpp=$(BUILD_FOLDER)/%.o) $(BUILD_FOLDER)/sqlite3.o
TEST_OBJECTS := $(SHARED_SOURCES:%.cpp=$(BUILD_FOLDER)/%.o) $(TEST_SOURCES:%.cpp=$(BUILD_FOLDER)/%.o) $(BUILD_FOLDER)/sqlite3.o

VAULT_PROGRAM := $(BUILD_FOLDER)/pixel-vault
TEST_PROGRAM  := $(BUILD_FOLDER)/vault-tests

.PHONY: start test reset clean
.DEFAULT_GOAL := start

start: test $(VAULT_PROGRAM)
	@./$(VAULT_PROGRAM)

test: $(TEST_PROGRAM)
	@mkdir -p data
	@./$(TEST_PROGRAM)

reset:
	@rm -rf data
	@echo "Progress, credits and requests were reset."

clean:
	@rm -rf $(BUILD_FOLDER)
	@echo "Compiled files were deleted."

$(VAULT_PROGRAM): $(APP_OBJECTS)
	@echo "  linking the vault"
	@$(CXX) $^ -o $@ $(LDLIBS)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	@echo "  linking the tests"
	@$(CXX) $^ -o $@ $(LDLIBS)

$(BUILD_FOLDER)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "  compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_FOLDER)/sqlite3.o: backend/vendor/sqlite3.c
	@mkdir -p $(BUILD_FOLDER)
	@echo "  compiling the SQLite database engine (only the first time, this takes a moment)"
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(APP_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)
