CC := gcc

OUTPUT	=	tetromino
SRCS 	= ./src/*
CFLAGS	= -I ./libs

$(OUTPUT) : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	@rm -f $(OUTPUT)
	@rm -f *.o