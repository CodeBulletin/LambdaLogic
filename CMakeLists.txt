cmake_minimum_required(VERSION 3.0.0)
project(LambdaLogic VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(OpenGL REQUIRED)
file(GLOB_RECURSE SRCS "./src/*.cpp")
file(GLOB DIRS "./exheaders/*")
link_directories(~/SFML/lib)
add_executable(LambdaLogic ${SRCS})
target_include_directories(LambdaLogic PRIVATE ./headers ${DIRS} ~/SFML/include)
target_link_libraries(LambdaLogic sfml-graphics sfml-window sfml-system ${OPENGL_gl_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
