cmake_minimum_required(VERSION 3.22)

find_package(SoapySDR)

add_executable(SDREnumerator
    src/SDREnumerator.cpp)

    target_include_directories(SDREnumerator
    PUBLIC     
    ${SoapySDR_INCLUDE_DIRS}
    sdr/include)

target_link_libraries(SDREnumerator
    PRIVATE
    sdr)

target_compile_features(SDREnumerator PRIVATE cxx_std_20)