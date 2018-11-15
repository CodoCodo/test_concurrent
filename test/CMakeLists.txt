LIST(APPEND TEST_DEP_LIBS pthread concurrent_common)

ADD_EXECUTABLE(test_concurrent test_concurrent.cpp)
TARGET_LINK_LIBRARIES(test_concurrent ${TEST_DEP_LIBS})

ADD_EXECUTABLE(test_condition test_condition.cpp)
TARGET_LINK_LIBRARIES(test_condition ${TEST_DEP_LIBS})
