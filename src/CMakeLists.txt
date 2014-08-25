file(GLOB sources *.cpp Space/*.cpp)
file(GLOB headers *.hpp Space/*.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${sources} ${headers})

target_link_libraries(${CMAKE_PROJECT_NAME} tank)

#set(EXEPATH ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)