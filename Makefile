SRC_DIR := ./src
INC_DIRS := ./include
BUILD_DIR := ./build

LUA_CFLAGS=$(shell pkg-config lua5.3 --cflags)
LUA_LIBS=$(shell pkg-config lua5.3 --libs)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := -std=c++11 -g $(INC_FLAGS) $(LUA_CFLAGS) -MMD -MP

SRCS := $(shell cd $(SRC_DIR); find . -name "*.cpp")
OBJS := $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SRCS)))
DEPS := $(OBJS:.o=.d)

deathray: $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $@ $(LUA_LIBS);

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ $(LUA_LIBS)

clean:
	rm -r $(BUILD_DIR)
	rm ./deathray

.PHONY: clean all

-include $(DEPS)
