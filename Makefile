
TARGET = myprog
CLFAGS = -Wall
CPROGRAM = parser.cpp

run:
	@ cd src/ && g++ $(CPROGRAM) -o $(TARGET) && ./$(TARGET)


.PHONY: clean
clean:
	@ cd src/ && rm -f *.o  $(TARGET)


