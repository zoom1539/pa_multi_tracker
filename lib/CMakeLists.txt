cmake_minimum_required(VERSION 3.0.0)



# CUDA
find_package(CUDA REQUIRED)
include_directories(/usr/local/cuda/include)
link_directories(/usr/local/cuda/lib64)


# OpenCV
find_package(OpenCV 3.4.15 REQUIRED PATHS /root/PLATFORM/3rdparty/opencv3415)
# find_package(OpenCV REQUIRED)


# TensorRT
set(TENSORRT_ROOT /root/PLATFORM/3rdparty/TensorRT-7.0.0.11)
set(TENSORRT_INCLUDE_DIR ${TENSORRT_ROOT}/include)
set(TENSORRT_LIB_DIR ${TENSORRT_ROOT}/lib)


#
aux_source_directory(. LIB_SRC)
message(${LIB_SRC})
add_library(multi_tracker SHARED ${LIB_SRC} )

target_include_directories(multi_tracker 
            PUBLIC ${TENSORRT_INCLUDE_DIR}
            PUBLIC ${OpenCV_INCLUDE_DIRS}
            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/extra/detector/include
            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/extra/tracker/include)

target_link_libraries(multi_tracker ${OpenCV_LIBS} 
                      ${TENSORRT_LIB_DIR}/libnvinfer.so 
                      ${CMAKE_CURRENT_SOURCE_DIR}/extra/detector/lib/libdetector.so
                      ${CMAKE_CURRENT_SOURCE_DIR}/extra/tracker/lib/libtracker.so
                      ${CUDA_LIBRARIES})

# cd build 
# make install
install(FILES class_multi_tracker.h DESTINATION include)
install(TARGETS multi_tracker LIBRARY DESTINATION lib)
