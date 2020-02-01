# compiler flags:
#  -Wall turns on most, but not all, compiler warnings
#  -Werror turns all warnings into errors
CFLAGS  = -Wall -Werror

# the build target executable:
TARGET = SEEsh

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc $(TARGET).c $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(TARGET)