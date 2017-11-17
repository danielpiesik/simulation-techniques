PROJECT_ROOT=$(realpath ../../)

BUILD_DIR=$(PROJECT_ROOT)/build
SRC_DIR=$(PROJECT_ROOT)/src
OBJ_DIR=$(BUILD_DIR)/obj

EXECUTABLE=simulation

SRC_EXT=cpp

CXX=g++
CFLAGS=-Wall -c
LDFLAGS=

################################################################################
# do not change below lines
################################################################################

SOURCES=$(shell find $(SRC_DIR) -name *.$(SRC_EXT))
OBJECTS=$(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES:.$(SRC_EXT)=.o))

all: \
	$(shell mkdir -p $(OBJ_DIR)) \
	$(shell mkdir -p $(BUILD_DIR)) \
	$(SOURCES) $(EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BUILD_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)/$@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(SRC_EXT)
	$(shell mkdir -p $(shell dirname $@))
	$(CXX) $(CFLAGS) $< -o $@
