project(Application)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC MnemosEvolved)
target_include_directories(${PROJECT_NAME} PUBLIC ../include)