OBJS = main.o Mesh.o supportClass.o Cuboid.o Cylinder.o Shape1.o Shape2.o
SRC_DIR = C:\Users\LENOVO\OneDrive\Desktop\testDHMT

all: main
		
assignment:
	g++ assignment-2010514.cpp -o run -lfreeglut -lglu32 -lopengl32
	./run
	del -f run.exe
		
main: $(OBJS)
	g++ -o main $(OBJS) -lfreeglut -lglu32 -lopengl32
	main
	del -f $(OBJS) main.exe
	
main.o: main.cpp 
	g++ -c main.cpp -lfreeglut -lglu32 -lopengl32

Mesh.o: Mesh.cpp Mesh.hpp supportClass.hpp
	g++ -c Mesh.cpp -lfreeglut -lglu32 -lopengl32

supportClass.o: SupportClass.cpp SupportClass.hpp
	g++ -c supportClass.cpp -lfreeglut -lglu32 -lopengl32

Cuboid.o : Cuboid.cpp Mesh.hpp
	g++ -c Cuboid.cpp -lfreeglut -lglu32 -lopengl32
	
Cylinder.o : Cuboid.cpp Mesh.hpp
	g++ -c Cylinder.cpp -lfreeglut -lglu32 -lopengl32
	
Shape1.o : Shape1.cpp Mesh.hpp
	g++ -c Shape1.cpp -lfreeglut -lglu32 -lopengl32

Shape2.o : Shape2.cpp Mesh.hpp
	g++ -c Shape2.cpp -lfreeglut -lglu32 -lopengl32
	
clean:
	del -f $(OBJS) main.exe