APPLICATION := application
PROJECTS    := ./lpcopen_lpc4337 ./$(APPLICATION)

all:
	@for PROJECT in $(PROJECTS) ; do \
		echo "*** Building project $$PROJECT ***" ; \
		make -C $$PROJECT ; \
		echo "" ; \
	done
clean:
	@for PROJECT in $(PROJECTS) ; do \
		echo "*** Cleaning project $$PROJECT ***" ; \
		make clean -C $$PROJECT ; \
		echo "" ; \
	done

download: 
	@echo "Downloading $(APPLICATION).bin to EDU-CIAA-NXP..."
	openocd -f ./$(APPLICATION)/cfg/ciaa-nxp.cfg -c "init" -c "halt 0" -c "flash write_image erase unlock ./$(APPLICATION)/out/$(APPLICATION).bin 0x1A000000 bin" -c "reset run" -c "shutdown"
	@echo "Download done. Do not forget to RESET your CIAA!"

erase:
	@echo "Erasing flash memory..."
	openocd -f ./$(APPLICATION)/cfg/ciaa-nxp.cfg -c "init" -c "halt 0" -c "flash erase_sector 0 0 last" -c "exit"
	@echo "Erase done. Do not forget to RESET your CIAA!"

