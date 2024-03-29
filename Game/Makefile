SRC_DIR  = src
INT_DIR  = build
TEST_DIR = build/test
TARGET   = game

CXX = g++
CXXFLAGS = -std=c++17 -Isrc/ -Isrc/engine/ -MT $@ -MMD -MP -MF $(@:.o=.d) 
LDFLAGS = -lstdc++
# conditional linker flags based on OS (Linux (tested on Ubuntu, Elementary and void), Darwin = MacOS)
UNAME := $(shell uname)

HAS_CURSESW6 := $(shell command -v ncursesw6-config 2> /dev/null)
HAS_CURSESW5 := $(shell command -v ncursesw5-config 2> /dev/null)

# use ncursesw6-config utility to find libraries when available
# therwhise go for a best guess
ifdef HAS_CURSESW6
CXXFLAGS += $(shell ncursesw6-config --cflags)
LDFLAGS += $(shell ncursesw6-config --libs)
STATICNCURSES = $(shell ncursesw6-config --libdir)/libncurses.a
else
	ifdef HAS_CURSESW5
	CXXFLAGS += $(shell ncursesw5-config --cflags)
	LDFLAGS += $(shell ncursesw5-config --libs)
	STATICNCURSES = $(shell ncursesw5-config --libdir)/libncurses.a
	else
	CXXFLAGS += -D_XOPEN_SOURCE_EXTENDED
	LDFLAGS += -lncurses -lncursesw
	# mock of a likely location on Darwin for the ncurses static binary
	STATICNCURSES = /usr/local/Cellar/ncurses/6.2/lib/libncurses.a
	endif
endif

# Things to build
ALL_FILES :=$(wildcard $(SRC_DIR)/**/**/**/**/*.cpp) $(wildcard $(SRC_DIR)/**/**/**/*.cpp) $(wildcard $(SRC_DIR)/**/**/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
ALL_HEADER_FILES :=$(wildcard $(SRC_DIR)/**/**/**/*.hpp) $(wildcard $(SRC_DIR)/**/**/**/*.cpp) $(wildcard $(SRC_DIR)/**/**/*.hpp) $(wildcard $(SRC_DIR)/**/*.hpp) $(wildcard $(SRC_DIR)/*.hpp)
CPP_FILES := $(filter-out %.test.cpp, $(ALL_FILES))

ALL_OBJ_FILES := $(ALL_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)
CPP_OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)
AUX_OBJ_FILES := $(filter-out build/main.o, $(CPP_OBJ_FILES))

DEP_FILES := $(ALL_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.d)

SUB_FOLDERS := $(filter-out src, $(patsubst src/%,%, $(shell find src -type d)))
OBJ_FOLDERS := $(addprefix build/, $(SUB_FOLDERS)) $(addprefix build/test/, $(SUB_FOLDERS))
.PHONY: test debug info clean format runstatic-darwin

all: info $(TARGET)
debug: CXXFLAGS += -ggdb
debug: clean all test
static-linux: LDFLAGS += -static -static-libstdc++ -static-libgcc
static-linux: info all
docs: 
	doxygen docfile
rm-docs: 
	rm -rf docs
open_docs:
	xdg-open docs/html/index.html


vg: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)



static-lib: static-linux
static-lib: ${CPP_OBJ_FILES}
	ar -rvs libbrown.a ${CPP_OBJ_FILES} 

info:
	@echo
	@echo "CXX = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo

clean: rm-docs
	@echo -e "RMRF\tbuild $(TARGET)"
	@rm -rf build $(TARGET)

format:
	clang-format -i $(ALL_FILES) $(ALL_HEADER_FILES)

run: all
	@echo -e "RUN\t$(TARGET)"
	@./$(TARGET)

$(ALL_OBJ_FILES): $(INT_DIR)/%.o: $(SRC_DIR)/%.cpp $(INT_DIR)/%.d | $(OBJ_FOLDERS)
	@echo -e "CC\t$<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(CPP_OBJ_FILES)
	@echo -e "LD\t$@"
	@$(CXX) $^ $(LDFLAGS) -o $@

static-darwin: $(CPP_OBJ_FILES)
	@echo -e "LD\t$@"
	@$(CXX) $(STATICNCURSES) $^ -o $(TARGET)

$(DEP_FILES): $(INT_DIR)/%.d: ;

$(OBJ_FOLDERS):
	@echo -e "MKDIR\t$@"
	@mkdir -p $@

-include $(DEP_FILES)