cmake_minimum_required(VERSION 2.8)

project(vpBrief)

find_package (OpenCV REQUIRED)
find_package (VISP REQUIRED)

set(${PROJECT_NAME}_CPP
  main.cpp
  vpBrief.cpp
  function_opencv.cpp
  ransac.cpp
  ../vpFast/vpGetKeypointsFast.cpp
  ../vpFast/vpFast.cpp
)
set(${PROJET_NAME}_H
    vpBrief.h
    function_opencv.h
    ransac.h
  ../vpFast/vpGetKeypointsFast.h
  ../vpFast/vpFast.h
)

add_executable(${PROJECT_NAME}
	${${PROJECT_NAME}_CPP}
	${${PROJECT_NAME}_H}
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${VISP_LIBRARIES})
