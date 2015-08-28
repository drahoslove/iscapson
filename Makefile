# is caps on?

NAME:=iscapson

FLAGS:= -DWIN32 -DUNICODE -mwindows

run: build
	./$(NAME)

build: $(NAME)

$(NAME): $(NAME).o icons.o caps.o tray.o
	gcc $(FLAGS) $^ -o $@

%.o: %.c %.h
	gcc $(FLAGS) -c $< -o $@

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

%.o: %.rc
	windres $^ -o $@

clean:
	-rm $(NAME) $(NAME).exe *.o