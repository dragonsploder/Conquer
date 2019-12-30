CFLAGS = -lncurses -w

SRCS=   main.c map.c display.c misc.c tile.c actions.c

conquer:
	g++ $(SRCS) $(CFLAGS) -o conquer

.PHONY: conquer

countLines: 
	find . \( -name "*.c" -o -name "*.h" \) | xargs wc -l | sort