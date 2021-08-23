cmake_minimum_required(VERSION 3.16)

project(LearnOpenGL)

# Glad
add_subdirectory(glad/)
# Reusable
add_subdirectory(src/)

# HelloWindow
add_subdirectory(Chapter-HelloWindow/)
# HelloTriangle
add_subdirectory(Chapter-HelloTriangle/)
# Shaders
add_subdirectory(Chapter-Shaders/)
# Textures
add_subdirectory(Chapter-Textures/)
# Two Textures
add_subdirectory(Chapter-TwoTextures/)

SET(LINK_FLAGS ${LINK_FLAGS} glfw3 dl GL X11 pthread glad Utils)


# \/ Configure Targets \/

target_link_libraries(HelloWindow ${LINK_FLAGS})
target_link_libraries(HelloTriangle ${LINK_FLAGS})
target_link_libraries(Shaders ${LINK_FLAGS})
target_link_libraries(Textures ${LINK_FLAGS})
target_link_libraries(TwoTextures ${LINK_FLAGS})