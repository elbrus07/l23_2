cmake_minimum_required(VERSION 3.10)
project(MyGtkmmApp)

# Включаем стандарт C++ (gtkmm-4.0 требует минимум C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем пакет gtkmm-4.0
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

# Собираем все .cpp файлы в папке проекта
file(GLOB SOURCES "*.cpp")

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Связываем проект с библиотеками gtkmm
target_link_libraries(${PROJECT_NAME} PkgConfig::GTKMM)
