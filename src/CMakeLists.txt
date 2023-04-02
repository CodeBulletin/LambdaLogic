# Include the FetchContent module
include(FetchContent)

# Use FetchContent to download and include SFML
FetchContent_Declare (
    SFML  # Name of the dependency
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"  # URL of the repository
    GIT_TAG        master  # Branch or tag to checkout
)
fetchcontent_makeavailable (SFML)

# Use FetchContent to download and include imgui
FetchContent_Declare (
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        master
)
fetchcontent_makeavailable (imgui)

# Use FetchContent to download and include imgui-sfml
FetchContent_Declare (
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG        master
)

# Set the IMGUI_DIR variable to the directory containing imgui
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)  # Don't search for SFML, we already did that

# Download and build imgui-sfml, linking against imgui and SFML
fetchcontent_makeavailable (imgui-sfml)