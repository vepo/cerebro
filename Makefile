CXX             := -c++
LDFLAGS         := -L/usr/lib -lstdc++ -lm
CXXFLAGS        := --coverage
BUILD           := ./build
OBJ_DIR         := $(BUILD)/objects
APP_DIR         := $(BUILD)/apps
INCLUDE         := -Iinclude/
SRC             := $(wildcard src/*/*.cpp)

MAINS           := $(wildcard src/*.cpp)
PROGS           := $(MAINS:src/%.cpp=%)
BINS            := $(MAINS:src/%.cpp=$(APP_DIR)%)
OBJECTS         := $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES    := $(OBJECTS:.o=.d)


TESTS           := $(wildcard test/*.cpp test/*/*.cpp)

DOCTEST_VERSION := 2.4.6
DOCTEST_DIR     := $(BUILD)/doctest
DOCTEST_INCLUDE := -I$(DOCTEST_DIR)/doctest

all: build $(PROGS)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(OBJ_DIR)/%: src/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) src/$@.cpp -o $(APP_DIR)/$@ $(OBJECTS) $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

$(DOCTEST_DIR):
	curl https://github.com/onqtam/doctest/archive/refs/tags/$(DOCTEST_VERSION).zip -sL -o $(BUILD)/doctest.zip
	unzip $(BUILD)/doctest.zip -d $(BUILD)
	@mv $(DOCTEST_DIR)-$(DOCTEST_VERSION) $(DOCTEST_DIR)

test: $(TESTS) $(OBJECTS) $(DOCTEST_DIR)
	$(CXX) $(CXXFLAGS) $(DOCTEST_INCLUDE) $(INCLUDE) $(TESTS) $(OBJECTS) -o $(BUILD)/tests $(LDFLAGS)
	$(BUILD)/tests

clean-doctest:
	-@rm -rvf $(DOCTEST_DIR)

coverage: test
	./test-coverage.sh

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@find . -name '*.gcov'      -exec rm -rv -- '{}' +
	-@find . -name '*.gcno'      -exec rm -rv -- '{}' +
	-@find . -name '*.gcda'      -exec rm -rv -- '{}' +
	-@find . -name '*.stackdump' -exec rm -rv -- '{}' +

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Mains:           ${MAINS}       "
	@echo "[*] Executables:     ${BINS}        "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
	@echo "[*] Tests:           ${TESTS}       "