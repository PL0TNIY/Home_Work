TARGET_SUM = sum.o
SOURCE_SUM = sum.c

TARGET_SUB = sub.o
SOURCE_SUB = sub.c

TARGET_MULT = mult.o
SOURCE_MULT = mult.c

TARGET_DIV = div.o
SOURCE_DIV = div.c

TARGET_ARCHIVE = libcalculator.a
SOURCE_ARCHIVE = $(TARGET_SUM) $(TARGET_SUB) $(TARGET_MULT) $(TARGET_DIV)

TARGET_MAIN = main
SOURCE_MAIN = main.c

COMPIELER = gcc

all: $(TARGET_SUM) $(TARGET_SUB) $(TARGET_MULT) $(TARGET_DIV) $(TARGET_ARCHIVE) $(TARGET_MAIN)


$(TARGET_SUM): $(SOURCE_SUM)
				@$(COMPIELER) $(SOURCE_SUM) -c

$(TARGET_SUB): $(SOURCE_SUB)
				@$(COMPIELER) $(SOURCE_SUB) -c

$(TARGET_MULT): $(SOURCE_MULT)
				@$(COMPIELER) $(SOURCE_MULT) -c

$(TARGET_DIV): $(SOURCE_DIV)
				@$(COMPIELER) $(SOURCE_DIV) -c

$(TARGET_ARCHIVE): $(SOURCE_ARCHIVE)
					@ar rc libcalculator.a $(TARGET_SUM) $(TARGET_SUB) $(TARGET_MULT) $(TARGET_DIV)

$(TARGET_MAIN): $(SOURCE_MAIN)
					@$(COMPIELER) $(SOURCE_MAIN) -o $(TARGET_MAIN) -L. -lcalculator
