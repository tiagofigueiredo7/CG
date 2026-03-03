cmake_minimum_required(VERSION 3.10)
project(CG)

include_directories(include)

# Definir preferência para usar GLVND (OpenGL moderno)
set(OpenGL_GL_PREFERENCE GLVND)

# Encontrar bibliotecas necessárias
find_package(TinyXML2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Juntar todos os arquivos fonte automaticamente
file(GLOB GENERATOR_SOURCES CONFIGURE_DEPENDS "src/generator/*.cpp")
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/engine/*.cpp")
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS "src/utils/*.cpp")

# Generator
add_executable(generator ${GENERATOR_SOURCES} ${UTILS_SOURCES})
target_include_directories(generator PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Engine
add_executable(engine ${ENGINE_SOURCES} ${UTILS_SOURCES})
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} tinyxml2)
target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${TinyXML2_INCLUDE_DIRS})
