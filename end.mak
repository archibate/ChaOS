# cleaning

.PHONY: clean
clean:
ifdef WIN
	$Dclean.bat
else
	rm -rf *.bin *.elf *.out *.sys *.i .dep *mzsiz.* $(OBJS) $(OBJS:%.o=%.d)
endif
