BUILD_DIR := build/
SRC_DIR := src/
CPP_FLAGS := -g -Wall
object_files := ${BUILD_DIR}load_levels.o ${BUILD_DIR}main.o ${BUILD_DIR}utils.o ${BUILD_DIR}assert_setup.o
# targets := load_levels.o main.o testing.o utils.o assert_setup.o

all: ${object_files}
	@echo "Link all object files"
	g++ ${CPP_FLAGS} ${object_files} -o ${BUILD_DIR}main.exe
.PHONY: all

# Compile all *.cpp files in SRC_DIR and move result to BUILD_DIR
${BUILD_DIR}%.o: ${SRC_DIR}%.cpp
	g++ ${CPP_FLAGS} -c $< -o $@

test: ${BUILD_DIR}testing.o
	g++ ${CPP_FLAGS} ${BUILD_DIR}testing.o ${BUILD_DIR}load_levels.o -o ${BUILD_DIR}testing.exe

clean:
	@echo "cleaning project..."
	cmake -E rm -f ${object_files} ${BUILD_DIR}main.exe ${BUILD_DIR}testing.o ${BUILD_DIR}testing.exe
	@echo "project cleaned"
.PHONY: clean
