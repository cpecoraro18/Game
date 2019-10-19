game: AABB.o Block.o Collision.o Game.o main.o Map.o Player.o TextureManager.o Vector.o Window.o
	g++ AABB.o Block.o Collision.o Game.o main.o Map.o Player.o TextureManager.o Vector.o Window.o -o game
AABB.o: src/AABB.cpp
	g++ -c src/AABB.cpp
Block.o: src/Block.cpp
	g++ -c src/Block.cpp
Collision.o: src/Collision.cpp
	g++ -c src/Collision.cpp
Game.o: src/Game.cpp
	g++ -c src/Game.cpp
main.o: src/main.cpp
	g++ -c src/main.cpp
Map.o: src/Map.cpp
	g++ -c src/Map.cpp
Player.o: src/Player.cpp
	g++ -c src/Player.cpp
TextureManager.o: src/TextureManager.cpp
	g++ -c src/TextureManager.cpp
Vector.o: src/Vector.cpp
	g++ -c src/Vector.cpp
Window.o: src/Window.cpp
	g++ -c src/Window.cpp
clean:
	rm *.o game
