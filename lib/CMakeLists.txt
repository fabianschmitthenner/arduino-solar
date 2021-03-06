set (path ${arduinoDirectory}/hardware/arduino/cores/arduino)
add_library (arduinoLib STATIC 
	${path}/HardwareSerial.cpp
	${path}/Print.cpp
	${path}/wiring.c
	${path}/wiring_shift.c
	${path}/WInterrupts.c
	${path}/wiring_digital.c
	${path}/WMath.cpp
	${path}/pins_arduino.c
	${path}/wiring_analog.c
	${path}/wiring_pulse.c
)

set (libraries ${arduinoDirectory}/libraries)
add_library (EEPROM STATIC ${libraries}/EEPROM/EEPROM.cpp)
add_library (SoftSerial STATIC ${libraries}/SoftwareSerial/SoftwareSerial.cpp)
add_library (Lcd STATIC ${libraries}/LiquidCrystal/LiquidCrystal.cpp)
add_library (Servo STATIC ${libraries}/Servo/Servo.cpp)
target_link_libraries (Servo arduinoLib)

add_subdirectory (FreqCounter)
add_subdirectory (sd-reader_source_20101010)
add_subdirectory(Memory)