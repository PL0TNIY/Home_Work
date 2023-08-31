TARGET_ARU = add_random_user.o
SOURCE_ARU = add_random_user.c

TARGET_SU = show_user.o
SOURCE_SU = show_user.c

TARGET_SCU = search_user.o
SOURCE_SCU = search_user.c

TARGET_AU = add_user.o
SOURCE_AU = add_user.c

TARGET_DU = delete_user.o
SOURCE_DU = delete_user.c

TARGET_ARCHIVE = libbox.a
SOURCE_ARCHIVE = $(TARGET_ARU) $(TARGET_SU) $(TARGET_SCU) $(TARGET_AU) $(TARGET_DU)

TARGET_MAIN = main
SOURCE_MAIN = main.c

COMPIELER = gcc

all: $(TARGET_ARU) $(TARGET_SU) $(TARGET_SCU) $(TARGET_AU) $(TARGET_DU) $(TARGET_ARCHIVE) $(TARGET_MAIN)


$(TARGET_ARU): $(SOURCE_ARU)
				@$(COMPIELER) $(SOURCE_ARU) -c

$(TARGET_SU): $(SOURCE_SU)
				@$(COMPIELER) $(SOURCE_SU) -c

$(TARGET_SCU): $(SOURCE_SCU)
				@$(COMPIELER) $(SOURCE_SCU) -c

$(TARGET_AU): $(SOURCE_AU)
				@$(COMPIELER) $(SOURCE_AU) -c

$(TARGET_DU): $(SOURCE_DU)
				@$(COMPIELER) $(SOURCE_DU) -c

$(TARGET_ARCHIVE): $(SOURCE_ARCHIVE)
					@ar rc libbox.a $(TARGET_ARU) $(TARGET_SU) $(TARGET_SCU) $(TARGET_AU) $(TARGET_DU)

$(TARGET_MAIN): $(SOURCE_MAIN)
					@$(COMPIELER) $(SOURCE_MAIN) -o $(TARGET_MAIN) -L. -lbox
