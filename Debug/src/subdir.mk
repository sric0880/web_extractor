################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/HtmlProcessor.o \
../src/TextExtractor.o \
../src/test.o 

CPP_SRCS += \
../src/HtmlProcessor.cpp \
../src/InfoExtractor.cpp \
../src/Template.cpp \
../src/TemplateHiall.cpp \
../src/TextExtractor.cpp \
../src/test.cpp 

OBJS += \
./src/HtmlProcessor.o \
./src/InfoExtractor.o \
./src/Template.o \
./src/TemplateHiall.o \
./src/TextExtractor.o \
./src/test.o 

CPP_DEPS += \
./src/HtmlProcessor.d \
./src/InfoExtractor.d \
./src/Template.d \
./src/TemplateHiall.d \
./src/TextExtractor.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/c++/4.7 -I/usr/include -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


