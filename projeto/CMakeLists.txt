cmake_minimum_required(VERSION 3.10)
project(CG)

include_directories(include)

# Encontrar bibliotecas necessárias
find_package(TinyXML2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Juntar todos os arquivos fonte automaticamente
file(GLOB GENERATOR_SOURCES "src/generator/*.cpp")
file(GLOB ENGINE_SOURCES "src/engine/*.cpp")
file(GLOB UTILS_SOURCES "src/utils/*.cpp")

# Generator
add_executable(generator ${GENERATOR_SOURCES} ${UTILS_SOURCES})

# Engine
add_executable(engine ${ENGINE_SOURCES} ${UTILS_SOURCES})
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} tinyxml2)
target_include_directories(engine PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${TinyXML2_INCLUDE_DIRS})
