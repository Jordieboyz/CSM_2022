

# header files in this project
HEADERS := button.hpp buttonHandler.hpp buttonListener.hpp
HEADERS += motionSensor.hpp motionSensorHandler.hpp motionSensorListener.hpp
HEADERS += displayControl.hpp 
HEADERS += lights.hpp lightSensor.hpp
HEADERS += InitializeControl.hpp ManageLightsControl.hpp
HEADERS += settings.hpp

# source files in this project (main.cpp is automatically assumed)
SOURCES := 

# other places to look for files for this project
SEARCH  := Button Display motionSensor Lights res

# settings for Arduino Due projects
TARGET           	:= arduino_due
SERIAL_PORT 		:= /dev/ttyACM0
CONSOLE_BAUDRATE 	:= 2400
STACK_SIZE 			:= 81920
HEAP				:= BMPTK
CONSOLE_BAUDRATE  	:= 115200


# Include all the needed libraries
RELATIVE			:= .
RTOS				?= $(RELATIVE)/../rtos
include 			$(RTOS)/makefile.inc

include           	$(RELATIVE)/Makefile.link
