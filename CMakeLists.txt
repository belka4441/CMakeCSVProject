# CMakeList.txt: проект CMake для CMakeCSVProject; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMakeCSVProject "CMakeCSVProject.cpp" "CMakeCSVProject.h" "Expression.h" "Expression.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
