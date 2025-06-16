run:
	mkdir -p build
	cd build && cmake .. && cmake --build .
	echo "" && build/todo
