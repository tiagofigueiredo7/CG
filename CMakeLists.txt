cmake_minimum_required(VERSION 3.10)
project(CG)

include_directories(include)

# Encontrar bibliotecas necessárias
find_package(TinyXML2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Generator
add_executable(generator src/generator/generator.cpp src/generator/primitives.cpp src/utils/utils.cpp)

# Engine
add_executable(engine src/engine/engine.cpp src/utils/utils.cpp)
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} tinyxml2)
target_include_directories(engine PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})




