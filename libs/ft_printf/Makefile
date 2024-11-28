NAME   := libftprintf.a
CC     := gcc
CFLAGS := -Wall -Wextra -Werror

SOURCES := \
		src/arg_parser.c \
		src/args.c \
		src/args_char.c \
		src/args_hex.c \
		src/args_int.c \
		src/args_ptr.c \
		src/args_string.c \
		src/args_unsigned.c \
		src/printf.c \
		src/util.c
OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))
BONUS_SOURCES := \
		src/printf_bonus.c
BONUS_OBJECTS := $(addprefix objs/,$(BONUS_SOURCES:.c=.o))

objs/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(AR) rcs $(NAME) $(OBJECTS)

.PHONY: all
all: $(NAME)

.PHONY: bonus
bonus: $(OBJECTS) $(BONUS_OBJECTS)
	$(AR) rcs $(NAME) $(OBJECTS) $(BONUS_OBJECTS)

.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	$(RM) $(BONUS_OBJECTS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
