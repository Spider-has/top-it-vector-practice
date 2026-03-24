CXXFLAGS += -Wall -Wextra -std=c++14 -MMD

main: main.o
	$(CXX) $^ -o out/$@

-include main.d

run: out/main
	./$^
