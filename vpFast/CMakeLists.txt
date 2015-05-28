cmake_minimum_required(VERSION 2.8)

project(vpFast)

find_package (VISP REQUIRED)

set(${PROJECT_NAME}_CPP
	main.cpp
	vpGetKeypointsFast.cpp
	vpFast.cpp
)
set(${PROJET_NAME}_H
	vpGetKeypointsFast.h
	vpFast.h
)

add_executable(${PROJECT_NAME}
	${${PROJECT_NAME}_CPP}
	${${PROJECT_NAME}_H}
)

target_link_libraries(${PROJECT_NAME} ${VISP_LIBRARIES})
