LIST(APPEND TEST_DEP_LIBS pthread concurrent_common concurrent_util concurrent_debug_tools)

ADD_EXECUTABLE(test_concurrent test_concurrent.cpp)
TARGET_LINK_LIBRARIES(test_concurrent ${TEST_DEP_LIBS})

ADD_EXECUTABLE(test_condition test_condition.cpp)
TARGET_LINK_LIBRARIES(test_condition ${TEST_DEP_LIBS})

ADD_EXECUTABLE(test_future test_future.cpp)
TARGET_LINK_LIBRARIES(test_future ${TEST_DEP_LIBS})

ADD_EXECUTABLE(test_time test_time.cpp)
TARGET_LINK_LIBRARIES(test_time ${TEST_DEP_LIBS})

ADD_EXECUTABLE(test_basic test_basic.cpp)
TARGET_LINK_LIBRARIES(test_basic ${TEST_DEP_LIBS})

ADD_EXECUTABLE(test_md5 test_md5.cpp)
TARGET_LINK_LIBRARIES(test_md5 ${TEST_DEP_LIBS})
