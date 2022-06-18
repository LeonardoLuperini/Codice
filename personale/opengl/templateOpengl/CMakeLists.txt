cmake_minimum_required(VERSION 3.22.5)

# set the project name
project(template)

# add the executable
add_executable(${PROJECT_NAME} src/main.c include/glad.c)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw3 opengl32)