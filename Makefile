NAME   := push_swap
CC     := gcc
CFLAGS := -Wall -Wextra -ggdb -fsanitize=address
#CFLAGS := -Wall -Wextra -Ofast -march=native -mtune=native -O3 -fopenmp -funroll-all-loops

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
src/push_swap.c  \
src/opti/opti.c  \
src/opti/backtrack.c  \
src/state/state.c  \
src/state/state_util.c  \
src/sort/pivot.c  \
src/sort/quicksort.c  \
src/sort/sort.c  \
src/sort/annealing.c  \
src/sort/sort_small.c

OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))

# Printf library
LIB_PRINTF_PATH := libs/ft_printf
LIB_PRINTF_INC := libs/ft_printf/includes
LIB_PRINTF := libftprintf.a

IFLAGS := -I $(LIB_PRINTF_INC)
LFLAGS := $(LIB_PRINTF_PATH)/$(LIB_PRINTF)

objs/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIB_PRINTF_PATH)/$(LIB_PRINTF)
	$(CC) $(IFLAGS) $(CFLAGS) \
		$(OBJECTS) $(LFLAGS) -o $(NAME) -lm

$(LIB_PRINTF_PATH)/$(LIB_PRINTF):
	$(MAKE) -C $(LIB_PRINTF_PATH)

.PHONY: all
all: $(NAME)


.PHONY: clean
clean:
	$(RM) -r objs

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
