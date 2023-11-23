PROJECT_NAME=cat
FLAGS=-Wall -Werror -Wextra

s21_$(PROJECT_NAME): $(PROJECT_NAME).c
	gcc $(FLAGS) $(PROJECT_NAME).c -o $(PROJECT_NAME)

clean:
	rm -rf $(PROJECT_NAME)

style:
	clang-format -style=google -n -Werror *.c *.h

format:
	clang-format -style=google -i *.c *.h
test:
	chmod +x flag_test_cat.sh
	bash flag_test_cat.sh