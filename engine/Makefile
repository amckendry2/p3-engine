GAME := testgame

CC = g++
COMPILER_FLAGS = -std=c++2a -w
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRCS_DIR := ./engine/src
HEADERS_FLAG := -I$(SRCS_DIR)/headers
BUILD_DIR := ./engine/build

G_DIR=../$(GAME)
G_SRCS_DIR = $(G_DIR)/scripts
G_BUILD_DIR = $(G_DIR)/build
G_HEADERS_FLAG = -I$(G_SRCS_DIR)/headers

SRCS := $(shell find $(SRCS_DIR) -name '*.cpp' -exec basename {} \;) 
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o) 
DEPS := $(SRCS:%.cpp=$(BUILD_DIR)/%.d)

G_SRCS := $(shell find $(G_SRCS_DIR) -name '*.cpp' -exec basename {} \;)
G_OBJS := $(G_SRCS:%.cpp=$(G_BUILD_DIR)/%.o)
G_DEPS := $(G_SRCS:%.cpp=$(G_BUILD_DIR)/%.d)

$(G_DIR)/$(GAME).out : $(OBJS) $(G_OBJS)
	$(CC) $(OBJS) $(G_OBJS) $(LINKER_FLAGS) -o $@

$(G_BUILD_DIR)/%.o : $(G_SRCS_DIR)/%.cpp
	$(CC) $(COMPILER_FLAGS) $(G_HEADERS_FLAG) $(HEADERS_FLAG) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CC) $(COMPILER_FLAGS) $(HEADERS_FLAG) -MMD -MP -c $< -o $@

-include $(DEPS) $(G_DEPS)

.PHONY game:
game:
	make $(G_DIR/$(GAME).out
