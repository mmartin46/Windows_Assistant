# Psalms 37:4
MAIN_FILE = main.cpp
EXECUTEABLE = main.exe

main:
	g++ $(MAIN_FILE) -o $(EXECUTEABLE)

clean:
	rm $(EXECUTEABLE)