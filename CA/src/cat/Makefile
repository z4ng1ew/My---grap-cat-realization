Project_Name = cat
Flags = -Wall -Werror -Wextra

all: s21_$(Project_Name)

s21_$(Project_Name): clean
	gcc $(Flags) s21_$(Project_Name).c -o s21_$(Project_Name) -g -std=c11

clean:
	rm -rf *.out s21_$(Project_Name)

test: s21_$(Project_Name)
#для запуска тестов нужно дописать цели

style:
	clang-format -style=google -n *.c *.h

format:
	clang-format -style=google -i *.c *.h