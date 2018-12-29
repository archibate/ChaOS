# cleaning

.PHONY: clean
clean:
ifdef WIN
	$Dclean.bat
else
	rm -rf *.bin *.elf *.out *.sys $(OBJS)
endif
