# Video that helped make this makefile: https://youtu.be/YjMrj_FbDGU (has stuff about sfml renderwindow class, too)
OBJS = main.cpp ContentContainer.cpp Button.cpp Content.cpp InputBox.cpp ContentToDisplay.cpp MessageWindow.cpp Plant.cpp Map.cpp
CXX = g++
CPPFLAGS = -WALL
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lmysqlcppconn

app: $(OBJS)
	$(CXX) -o garden_planner $(OBJS) $(LDLIBS)

clean:
	$(RM) garden_planner *.o
