# depedency generator

.PHONY: dep
dep: .dep

.dep: $(OBJS:%.o=%.d)
	cat $^ > $@
	cat $^ | sed 's/\.o:/\.d:/' >> $@

%.d: Makefile
