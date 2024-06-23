add_executable(bk_intersection bk_intersection.cpp)

target_link_libraries(bk_intersection PUBLIC sdsl divsufsort divsufsort64)
