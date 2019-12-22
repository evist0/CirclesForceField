cmake_minimum_required(VERSION 3.15)
project(Circles C)

set(CMAKE_C_STANDARD 99)

add_executable(Circles main.c Utilities/TwoDimensions/TwoDimensions.c Utilities/Settings/Settings.c CircleService/ServiceComponents/CirclesDraw/CirclesDraw.c CircleService/CircleService.c CircleService/CircleService.h CircleService/ServiceComponents/CircleLogic/CirclesLogic.c CircleService/ServiceComponents/CircleLogic/CirclesLogic.h CircleService/ServiceComponents/CirclesDraw/CirclesDraw.h Utilities/Color/Color.c Utilities/Color/Color.h Utilities/TwoDimensions/TwoDimensions.h Utilities/Settings/Settings.h)
target_link_libraries(
        ${PROJECT_NAME}
        -lopengl32
        -lfreeglut
)