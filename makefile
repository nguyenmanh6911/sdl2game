# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# SDL2 Config - Lấy cờ biên dịch và liên kết từ pkg-config
SDL2_CFLAGS := $(shell pkg-config --cflags SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2_net SDL2_gfx)
SDL2_LIBS := $(shell pkg-config --libs SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2_net SDL2_gfx)

# Tên file thực thi
TARGET := main

# Lấy danh sách tất cả các file .cpp và chuyển thành .o
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

# Mục tiêu mặc định: Biên dịch chương trình
all: $(TARGET)

# Biên dịch chương trình
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET).exe $(SDL2_LIBS)

# Biên dịch từng file .cpp thành .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

# Lệnh make run để biên dịch và chạy chương trình ngay
run: all
	./$(TARGET).exe

# Xóa file biên dịch
clean:
	rm -f $(OBJECTS) $(TARGET).exe
