# CMakeList.txt: проект CMake для BattleCity; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project ("BattleCity")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (BattleCity "src/BattleCity.cpp" "src/BattleCity.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
