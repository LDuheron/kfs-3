# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athierry <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 22:36:58 by athierry          #+#    #+#              #
#    Updated: 2022/12/28 18:07:08 by athierry         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# ******************************* NAMES ************************************** #
# **************************************************************************** #

NAME = minirt

# **************************************************************************** #
# ******************************* FLAGS ************************************** #
# **************************************************************************** #

MLIBX_PATH = minilibx-linux
MLIBX = $(MLIBX_PATH)/libmlx_Linux.a
MLIBX_FLAGS = -lXext -lX11
MATH_FLAGS = -lm

CC = clang
CFLAGS = -fenable-matrix -g3
CPPFLAGS = -fenable-matrix -g3

DEBUGFLAGS = -fsanitize=address -g3
PPDEBUGFLAGS = -fsanitize=address -g3

CHECKFLAGS = -Wall -Wextra -Werror
CPPCHECKFLAGS = -Wall -Wextra -Werror

ifeq ($(MAKECMDGOALS),debug)
CFLAGS += $(DEBUGFLAGS)
CPPFLAGS += $(PPDEBUGFLAGS)
endif

ifeq ($(MAKECMDGOALS),check)
CFLAGS += $(CHECKFLAGS)
CPPFLAGS += $(CPPCHECKFLAGS)
endif

RM = rm -f

# **************************************************************************** #
# ******************************* INCLUDE************************************* #
# **************************************************************************** #

HEAD_PATH = include/
HEAD = $(HEAD_PATH)minirt.h

# **************************************************************************** #
# ******************************* SOURCES ************************************ #
# **************************************************************************** #

MAIN_PATH = main/
MAIN_FILES = main.c \
MAIN = $(addprefix $(MAIN_PATH),$(MAIN_FILES))

HITTABLE_PATH = hittable/
HITTABLE_FILES = sphere.c \
HITTABLE = $(addprefix $(HITTABLE_PATH),$(HITTABLE_FILES))

MATH_PATH = math/
MATH_FILES = vector.c \
MATH = $(addprefix $(MATH_PATH),$(MATH_FILES))

RENDER_PATH = render/
RENDER_FILES = ray_tracer.c \
RENDER = $(addprefix $(RENDER_PATH),$(RENDER_FILES))

SRCS_PATH = srcs/
SRCS_FILES = $(MAIN) $(HITTABLE) $(MATH) $(RENDER)
SRCS = $(addprefix $(SRCS_PATH),$(SRCS_FILES))
		
# **************************************************************************** #
# ******************************* OBJECTS ************************************ #
# **************************************************************************** #

OBJS_PATH = obj/
OBJS_FILES = $(SRCS_FILES:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_FILES))

# **************************************************************************** #
# ******************************* DEPENDENCIES ******************************* #
# **************************************************************************** #

DEPS = $(OBJS:.o=.d)

# **************************************************************************** #
# ******************************* RULES ************************************** #
# **************************************************************************** #

.PHONY: all
all: $(NAME)

-include $(DEPS)

$(MLIBX):
	@$(MAKE) -C $(MLIBX_PATH) --no-print-directory

$(NAME): $(OBJS) $(MLIBX)
	$(CC) $(CFLAGS) -o $@ $^ $(MLIBX) $(MATH_FLAGS) $(MLIBX_FLAGS)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@[ -d $(OBJS_PATH) ] || mkdir -p $(OBJS_PATH)
	@[ -d $(OBJS_PATH)$(MAIN_PATH) ] || mkdir -p $(OBJS_PATH)$(MAIN_PATH)
	@[ -d $(OBJS_PATH)$(MATH_PATH) ] || mkdir -p $(OBJS_PATH)$(MATH_PATH)
	@[ -d $(OBJS_PATH)$(RENDER_PATH) ] || mkdir -p $(OBJS_PATH)$(RENDER_PATH)
	@[ -d $(OBJS_PATH)$(HITTABLE_PATH) ] || mkdir -p $(OBJS_PATH)$(HITTABLE_PATH)
	$(CC) -I $(HEAD_PATH) -MMD $(CPPFLAGS) -o $@  -c $<

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: dirty
dirty: re
	@$(RM) $(OBJS) $(DEPS)

.PHONY: debug
debug: dirty

.PHONY: check
check: dirty

.DEFAULT_GOAL := all

# **************************************************************************** #
