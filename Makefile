##
## EPITECH PROJECT, 2026
## Makefile ++
## File description:
## please god let this work
##

SRC = 	src/main.cpp	\
		src/kitchen/KitchenPool.cpp	\
		src/kitchen/KitchenParent.cpp	\
		src/kitchen/KitchenChild.cpp	\
		src/IPC/PacketHeader.cpp	\
		src/IPC/PacketDeserializer.cpp	\
		src/IPC/OrderPipes.cpp	\
		src/IPC/CommandPacket.cpp	\
		src/parsing/pizza_parsers.cpp	\
		src/kitchen/Cellar.cpp	\
		src/parsing/ReceptionCli.cpp	\
		src/help.cpp	\
		src/kitchen/CookWorker.cpp	\
		src/utils/ThreadSafeStreams.cpp	\
		src/Pizzeria.cpp	\
		src/kitchen/DeliveryDeck.cpp	\
		src/kitchen/OrderTickets.cpp	\
		src/utils/PizzaSingle.cpp	\
		src/utils/stream_mutex.cpp	\
		src/utils/ctrl_c_handler.cpp	\

OBJ = $(SRC:.cpp=.o)

# LIBS = libcentipede libcurses libsdl libsnake

NAME = plazza

CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++20
CPPFLAGS =	-I./include/kitchen	\
			-I./include/workers	\
			-I./include/parsing	\
			-I./include/IPC	\
			-I./include/utils	\
			-I./include/	\

# LDFLAGS += -ldl

all: $(NAME) # $(LIBS)
lib%:
	make -C ./lib/$@

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ)

DEBUG_IGNORE_ERRORS	=	-Wno-unused-parameter	\
						-Wno-unused-private-field	\
						-Wno-unused-variable	\
						-Wno-unused-function	\

DEBUG_FLAGS	=	-g3

debug: CPPFLAGS += $(DEFAULT_THREAD_DEBUG_STRATEGY) $(DEBUG_FLAGS)
debug: re

debug_hg: DEFAULT_THREAD_DEBUG_STRATEGY	=
debug_hg: DEBUG_FLAGS	=	-g -O1
debug_hg: debug

debug_Asan: DEBUG_FLAGS	+=	-fsanitize=address,undefined
debug_Asan: debug

debug_Tsan: DEBUG_FLAGS	+=	-fsanitize=thread
debug_Tsan: debug

debug_hg: DEFAULT_THREAD_DEBUG_STRATEGY	=
debug_hg: DEBUG_FLAGS	=	-g -O1
debug_hg: debug

debug_ign: CPPFLAGS += $(DEBUG_IGNORE_ERRORS)
debug_ign: debug

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
