##
## 
## Made by longle_h
## Login   <henri.longle@epitech.eu>
## 
## Started on  Wed May 31 15:39:14 2017 longle_h
## Last update Sun Oct  8 17:24:19 2017 DESKTOP-OEH668A
## Last update Wed Oct  4 15:59:43 2017 DESKTOP-0DMKG6E
##

NAME	= spider_server

CC	= g++

RM	= rm -rf

SRCS	= 	./src/Log.cpp \
            ./src/Tools.cpp \
            ./src/main.cpp \
	        ./src/AEncryption.cpp \
	        ./src/EOpenSSL.cpp \
	        ./src/ClientTcpConnection.cpp \
            ./src/AServer.cpp \
	        ./src/DBMongo.cpp \

OBJS	= $(SRCS:.cpp=.o)

LOG_DIR	=	./Log/

SSL_DIR	=	./OpenSSL/

CPPFLAGS = -I./inc/

CPPFLAGS += -W -Wall -Wextra -std=c++14 `pkg-config --cflags libmongocxx`

LDFLAGS		+= 	-lboost_system
LDFLAGS		+=	-lboost_filesystem
LDFLAGS    	+= 	-lboost_date_time
LDFLAGS		+= 	-lboost_thread
LDFLAGS		+= 	-lssl
LDFLAGS		+=	-lcrypto
LDFLAGS		+=	-lpthread
LDFLAGS		+=	`pkg-config --libs libmongocxx`

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

cleandir :
		$(RM) $(LOG_DIR)
		$(RM) $(SSL_DIR)

re: fclean all

.PHONY: all clean fclean re
