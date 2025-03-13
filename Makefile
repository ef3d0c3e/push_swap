NAME   := push_swap
CC     := gcc
CFLAGS := -Wall -Wextra -ggdb -fsanitize=address
#CFLAGS := -Wall -Wextra -Ofast -march=native -mtune=native -O3

SOURCES := \
src/blk/split.c  \
src/blk/blk_sort.c  \
src/blk/blk.c  \
src/blk/blk_sort_3.c  \
src/blk/move.c  \
src/stack/stack.c  \
src/stack/stack_util.c  \
src/stack/stack_op.c  \
src/util.c  \
src/args.c  \
src/opti/opti.c  \
src/opti/backtrack.c  \
src/state/state.c  \
src/state/state_util.c  \
src/sort/pivot.c  \
src/sort/quicksort.c  \
src/sort/sort.c  \
src/sort/annealing.c

OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))

objs/%.o: IFLAGS += -I./libs/ft_printf/includes
objs/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

# Push swap main target
$(NAME): LFLAGS += $(LIB_PRINTF)
$(NAME): OBJECTS += ./objs/src/push_swap.o
$(NAME): $(OBJECTS) ./objs/src/push_swap.o $(LIB_PRINTF)
	$(CC) $(IFLAGS) $(CFLAGS) \
		$(OBJECTS) $(LFLAGS) -o $(NAME) -lm

checker: LFLAGS += $(LIB_PRINTF)
checker: OBJECTS += ./objs/src/checker.o
checker: $(OBJECTS) ./objs/src/checker.o $(LIB_PRINTF)
	$(CC) $(IFLAGS) $(CFLAGS) \
		$(OBJECTS) $(LFLAGS) -o $@ -lm

# ft_printf
LIB_PRINTF := ./libs/ft_printf/libftprintf.a
$(LIB_PRINTF):
	echo "Building libprintf..."
	$(MAKE) -C $(dir $(LIB_PRINTF))

.PHONY: all
all: $(NAME)


.PHONY: clean
clean:
	$(RM) -r objs

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(RM) checker

.PHONY: re
re: fclean all
