# 烧录
flash: $(BUILD_DIR)/$(TARGET).hex
	@echo Download program
	openocd -f $(SDK_DIR)/scripts/openocd/stm32f030_jlink.cfg -c init -c targets -c 'reset halt' -c 'flash write_image erase $(BUILD_DIR)/$(TARGET).hex' -c 'reset halt' -c 'verify_image $(BUILD_DIR)/$(TARGET).hex' -c 'reset run' -c shutdown

reset:
	openocd -f $(SDK_DIR)/scripts/openocd/stm32f030_jlink.cfg -c init -c targets -c 'reset run' -c shutdown

halt:
	openocd -f $(SDK_DIR)/scripts/openocd/stm32f030_jlink.cfg -c init -c targets -c 'halt' -c shutdown

erase:
	openocd -f $(SDK_DIR)/scripts/openocd/stm32f030_jlink.cfg -c init -c targets -c 'halt' -c 'flash erase_address 0x08000000 0x80000' -c shutdown

readdfu:
	openocd -f $(SDK_DIR)/scripts/openocd/stm32f030_jlink.cfg -c init -c targets -c 'halt' -c 'flash read_bank 0 image.dfu 0x60000 0x20000' -c shutdown

gdbs:
	openocd -f $(SDK_DIR)/scripts/openocd/stm32f030_jlink.cfg

gdb:
	arm-none-eabi-gdb $(BUILD_DIR)/$(TARGET).elf -ex 'target remote localhost:3333' -ex 'monitor reset halt' -ex 'load'

release:
	cp $(BUILD_DIR)/$(TARGET).hex  $(BUILD_DIR)/$(TARGET)_$(VERSION)_$(TIMESTAMP).hex
	cp $(BUILD_DIR)/$(TARGET).bin  $(BUILD_DIR)/$(TARGET)_$(VERSION)_$(TIMESTAMP).bin

