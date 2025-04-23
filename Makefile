COMP=g++
FLAGS=-std=c++11
main: social_network.o user.o network.o
	$(COMP) $(FLAGS) $^ -o $@
%.o: %.cpp
	$(COMP) $(FLAGS) -c $< -o $@
clean:
	rm *.o main