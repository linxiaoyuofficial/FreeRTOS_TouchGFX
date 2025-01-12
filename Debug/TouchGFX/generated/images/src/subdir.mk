################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/BitmapDatabase.cpp \
../TouchGFX/generated/images/src/SVGDatabase.cpp \
../TouchGFX/generated/images/src/image_TemplateResource.cpp \
../TouchGFX/generated/images/src/image_m_button_custom_ui_Clicked.cpp \
../TouchGFX/generated/images/src/image_m_button_custom_ui_Normal.cpp 

OBJS += \
./TouchGFX/generated/images/src/BitmapDatabase.o \
./TouchGFX/generated/images/src/SVGDatabase.o \
./TouchGFX/generated/images/src/image_TemplateResource.o \
./TouchGFX/generated/images/src/image_m_button_custom_ui_Clicked.o \
./TouchGFX/generated/images/src/image_m_button_custom_ui_Normal.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/BitmapDatabase.d \
./TouchGFX/generated/images/src/SVGDatabase.d \
./TouchGFX/generated/images/src/image_TemplateResource.d \
./TouchGFX/generated/images/src/image_m_button_custom_ui_Clicked.d \
./TouchGFX/generated/images/src/image_m_button_custom_ui_Normal.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/%.o TouchGFX/generated/images/src/%.su TouchGFX/generated/images/src/%.cyclo: ../TouchGFX/generated/images/src/%.cpp TouchGFX/generated/images/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src

clean-TouchGFX-2f-generated-2f-images-2f-src:
	-$(RM) ./TouchGFX/generated/images/src/BitmapDatabase.cyclo ./TouchGFX/generated/images/src/BitmapDatabase.d ./TouchGFX/generated/images/src/BitmapDatabase.o ./TouchGFX/generated/images/src/BitmapDatabase.su ./TouchGFX/generated/images/src/SVGDatabase.cyclo ./TouchGFX/generated/images/src/SVGDatabase.d ./TouchGFX/generated/images/src/SVGDatabase.o ./TouchGFX/generated/images/src/SVGDatabase.su ./TouchGFX/generated/images/src/image_TemplateResource.cyclo ./TouchGFX/generated/images/src/image_TemplateResource.d ./TouchGFX/generated/images/src/image_TemplateResource.o ./TouchGFX/generated/images/src/image_TemplateResource.su ./TouchGFX/generated/images/src/image_m_button_custom_ui_Clicked.cyclo ./TouchGFX/generated/images/src/image_m_button_custom_ui_Clicked.d ./TouchGFX/generated/images/src/image_m_button_custom_ui_Clicked.o ./TouchGFX/generated/images/src/image_m_button_custom_ui_Clicked.su ./TouchGFX/generated/images/src/image_m_button_custom_ui_Normal.cyclo ./TouchGFX/generated/images/src/image_m_button_custom_ui_Normal.d ./TouchGFX/generated/images/src/image_m_button_custom_ui_Normal.o ./TouchGFX/generated/images/src/image_m_button_custom_ui_Normal.su

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src

