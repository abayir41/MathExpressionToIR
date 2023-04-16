CC=gcc
CFLAGS=

SRCS=main.c Lexer.c Parser.c VariableController.c Calculator.c
OBJS=$(SRCS:.c=.o)
HDRS=Lexer.h Parser.h VariableController.h Calculator.h Structures.h

advcalc: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o advcalc

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) advcalc