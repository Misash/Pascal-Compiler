
TARGET = myprog
CLFAGS = -Wall
CPROGRAM = Scanner.cpp

run:
	@ cd scanner/ && g++ $(CPROGRAM) -o $(TARGET) && ./$(TARGET)


.PHONY: clean
clean:
	@ cd scanner/ && rm -f *.o  $(TARGET)

#g++ parser.cpp -o pro && ./pro
