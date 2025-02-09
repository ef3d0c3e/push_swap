NAME   := push_swap
CC     := gcc
CFLAGS := -Wall -Wextra -Og -ggdb -fsanitize=address

SOURCES := \
   		src/stack/stack.c \
   		src/stack/stack_op.c \
		src/blk.c \
   		src/push_swap.c \
   		src/push_swap_data.c \
   		src/sort_blk.c \
   		src/sort.c \
   		src/sort_small.c \
   		src/util.c

OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))

# Printf library
LIB_PRINTF_PATH := libs/ft_printf
LIB_PRINTF_INC := libs/ft_printf/src
LIB_PRINTF := libftprintf.a

$(LIB_PRINTF_PATH)/$(LIB_PRINTF):
	$(MAKE) -C $(LIB_PRINTF_PATH) bonus
	
IFLAGS := -I $(LIB_PRINTF_INC)
LFLAGS := $(LIB_PRINTF_PATH)/$(LIB_PRINTF)

objs/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIB_PRINTF_PATH)/$(LIB_PRINTF)
	$(CC) $(IFLAGS) $(CFLAGS) \
		$(OBJECTS) $(LFLAGS) -o $(NAME)

.PHONY: all
all: $(NAME)


.PHONY: clean
clean:
	$(RM) $(OBJECTS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
