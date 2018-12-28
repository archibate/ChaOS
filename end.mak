# cleaning

.PHONY: clean
clean:
ifdef WIN
	clean.bat
else
	false clean not impelemented for unix-liked systems yet
endif
