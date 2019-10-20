# Video that helped make this makefile: https://youtu.be/YjMrj_FbDGU (has stuff about sfml renderwindow class, too)
OBJS = main.cpp ContentContainer.cpp Button.cpp Content.cpp InputBox.cpp
CXX = g++
CPPFLAGS = -WALL
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

app: $(OBJS)
	$(CXX) -o garden_planner $(OBJS) $(LDLIBS)

clean:
	$(RM) garden_planner *.o
