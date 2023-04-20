CC=gcc
CFLAGS=

SRCS=main.c Lexer.c Parser.c VariableController.c Calculator.c ProccesCounter.c
OBJS=$(SRCS:.c=.o)
HDRS=Lexer.h Parser.h VariableController.h Calculator.h Structures.h ProcessCounter.h

advcalc2ir: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o advcalc2ir

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) advcalc