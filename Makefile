NAME   := push_swap
CC     := gcc
CFLAGS := -Wall -Wextra -ggdb -fsanitize=address

SOURCES := \
src/state.c \
src/state_util.c \
src/blk/split.c \
src/blk/blk.c \
src/blk/blk_util.c \
src/blk/blk_sort.c \
src/blk/move.c \
src/blk/blk_sort_3.c \
src/stack/stack.c \
src/stack/stack_op.c \
src/util.c \
src/push_swap.c \
src/sort/sort.c \
src/sort/sort_small.c \
src/opti/opti.c


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
		$(OBJECTS) $(LFLAGS) -o $(NAME)

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
