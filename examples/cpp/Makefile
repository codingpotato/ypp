BUILD = build
SRC = $(wildcard *.c)
SRCXX = $(wildcard *.cpp)
OBJC = $(SRC:%.c=$(BUILD)/%.o)
OBJCXX = $(SRCXX:%.cpp=$(BUILD)/%.o)
TARGET = $(BUILD)/cpp.elf

PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++

CFLAGS = -mcpu=cortex-m7 -mthumb -mfloat-abi=soft -ffunction-sections -fdata-sections -g
CXXFLAGS = -mcpu=cortex-m7 -mthumb -mfloat-abi=soft -ffunction-sections -fdata-sections -g
LINKFLAGS = -mcpu=cortex-m7 -mthumb -mfloat-abi=soft --specs=nano.specs -Wl,--gc-sections -Tcortexm.ld

.PHONY: all build clean

all: build $(TARGET)

build:
	@mkdir -p $(BUILD)

$(OBJC): $(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJCXX): $(BUILD)/%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJC) $(OBJCXX) cortexm.ld
	$(CC) $(LINKFLAGS) -o $@ $(OBJC) $(OBJCXX)

clean:
	@rm -rf $(BUILD)
