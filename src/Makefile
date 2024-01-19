ri: ri.c
	$(CC) ri.c -o ri -Wall -Wextra -pedantic -std=c99 -lncurses

clean:
	@if [ -e ri ]; then \
        rm ri; \
        echo "Executable removed"; \
    else \
        echo "Directory already clean"; \
    fi
