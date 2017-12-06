file(GLOB SRCS *.cpp)

add_executable(testAVLTree ${SRCS})

target_link_libraries(testAVLTree
        avltree
        gtest
        gmock
)

include_directories("..")

install(TARGETS testAVLTree DESTINATION bin)
