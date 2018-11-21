AUX_SOURCE_DIRECTORY(. DEBUG_TOOL_SRC)
ADD_LIBRARY(concurrent_debug_tools ${DEBUG_TOOL_SRC})
TARGET_LINK_LIBRARIES(concurrent_debug_tools pthread)
