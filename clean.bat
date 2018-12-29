@rem https://www.cnblogs.com/cbugs/p/8992059.html
del *.img *.bin
for /r %%x in (*.o) do @del %%x
