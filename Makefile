# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Define build directory
BUILD_DIR = $(CURDIR)/build

# Recursive search for .cpp files using Windows batch command (for /R)
SOURCES = $(subst \,/,$(shell for /R %%f in (*.cpp) do @echo %%f))

# Map .cpp files to .o files inside the build directory
OBJECTS = $(patsubst %.cpp, %.o,$(subst $(CURDIR),$(BUILD_DIR),$(SOURCES)))

# Define target (final executable)
TARGET = $(BUILD_DIR)/compiled.exe

# Rule to compile .cpp to .o
# @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
$(BUILD_DIR)/%.o: %.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files into the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)

# Compile and run the compiled executable file
crun: $(TARGET)
	$(TARGET)

# Run the executable file
run: $(TARGET)
	$(TARGET)
