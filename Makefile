run:
	g++ days/day$(day)/solution.cpp -o bin/out && bin/out

lint:
	find . -iname '*.h' -o -iname '*.cpp' -o -iname '*.hpp' | clang-format --style=file -i --files=/dev/stdin
