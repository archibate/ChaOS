# depedency generator

.PHONY: dep
dep: .dep

.dep: $(OBJS:%.o=%.d) $(DEPISRC:%.i=%.d)
	cat $^ > $@
	cat $^ | sed 's/\.[oi]:/\.d:/' >> $@

%.d: Makefile
