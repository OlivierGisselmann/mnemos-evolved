project(Application)

# Create executable from sources
add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
)

# Link Mnemos against the executable
target_link_libraries(${PROJECT_NAME} PUBLIC MnemosEvolved)

# Include Mnemos public API
target_include_directories(${PROJECT_NAME} PUBLIC ../include)