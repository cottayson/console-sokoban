@g++ -Wall build/load_levels.o build/main.o build/utils.o build/assert_setup.o -o build/main.exe
@g++ -Wall build/testing.o build/load_levels.o -o build/testing.exe