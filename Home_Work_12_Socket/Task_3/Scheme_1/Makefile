TARGET_SERVER = server
TARGET_CLIENT = client

SERVER_SOURCE = server.c
CLIENT_SOURCE = client.c

COMPIELER = gcc

all: $(TARGET_SERVER) $(TARGET_CLIENT)


$(TARGET_SERVER): $(SERVER_SOURCE)
					@$(COMPIELER) $(SERVER_SOURCE) -o $(TARGET_SERVER) -pthread

$(TARGET_CLIENT): $(CLIENT_SOURCE)
					@$(COMPIELER) $(CLIENT_SOURCE) -o $(TARGET_CLIENT)
