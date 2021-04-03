# rprtr258-s-2048
My copy of 2048 on C++

## Build
```bash
g++ -D SFML_STATIC main.cpp -o app.exe -I SFML-2.5.1/include/ -L SFML-2.5.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32
```