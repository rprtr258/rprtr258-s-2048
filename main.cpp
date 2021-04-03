#include <sstream>
#include <time.h>
#include <SFML/Graphics.hpp>


const int TILES_COUNT = 29;
const int HEIGHT = 10;
const int WIDTH = 10;
const int MAX_TILES = HEIGHT * WIDTH;
const int TILE_SIZE = 66;


void generatetile(sf::Sprite *spr_tiles, int (&map)[WIDTH][HEIGHT], int &tiles, sf::Texture empty, sf::Texture &n1) {
    if (tiles == MAX_TILES) return;
    int x = rand() % WIDTH;
    int y = rand() % HEIGHT;
    while (map[x][y] != 0) {
        x = rand() % WIDTH;
        y = rand() % HEIGHT;
    }
    spr_tiles[x * WIDTH + y].setTexture(n1);
    map[x][y] = 1;
}

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(TILE_SIZE * WIDTH, TILE_SIZE * HEIGHT), "rprtr258's 2048");
    sf::Texture tex_tiles[TILES_COUNT];
    int tiles = 1;
    // TODO: specify size from argv
    //in << WIDTH << HEIGHT;
    bool press_but = false;
    for (int i = 0; i < TILES_COUNT; i++) {
        std::ostringstream str;
        str << "img\\" << i << ".png";
        if (!tex_tiles[i].loadFromFile(str.str())) {
            return 1;
        }
    }
    sf::Sprite spr_tiles[WIDTH][HEIGHT];
    int map[WIDTH][HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            spr_tiles[j][i].setTexture(tex_tiles[0]);
            spr_tiles[j][i].setPosition(j * TILE_SIZE, i * TILE_SIZE);
            map[j][i] = 0;
        }
    }
    generatetile((sf::Sprite*)spr_tiles, map, tiles, tex_tiles[0], tex_tiles[1]);
    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            if (Event.type == sf::Event::KeyPressed) {
                bool turnmade = false;
                if (Event.key.code == sf::Keyboard::Up && !press_but) {
                    press_but = true;
                    for (int i = 0; i < WIDTH; i++) {
                        for (int j = 1; j < HEIGHT; j++) {
                            if (map[i][j] != 0 && map[i][j - 1] == 0) {
                                int k = j - 1;
                                while (k >= 0 && map[i][k] == 0)
                                    k--;
                                if (map[i][k + 1] == 0) {
                                    if (map[i][j] == map[i][k]) {
                                        map[i][k]++;
                                        map[i][j] = 0;
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        spr_tiles[i][k].setTexture(tex_tiles[map[i][k]]);
                                        tiles--;
                                    } else {
                                        spr_tiles[i][k + 1].setTexture(tex_tiles[map[i][j]]);
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        std::swap(map[i][j], map[i][k + 1]);
                                    }
                                    turnmade = true;
                                }
                            } else if (map[i][j] != 0 && map[i][j] == map[i][j - 1]) {
                                map[i][j - 1]++;
                                map[i][j] = 0;
                                tiles--;
                                spr_tiles[i][j].setTexture(tex_tiles[0]);
                                spr_tiles[i][j - 1].setTexture(tex_tiles[map[i][j - 1]]);
                                turnmade = true;
                            }
                        }
                    }
                }
                if (Event.key.code == sf::Keyboard::Right && !press_but) {
                    press_but = true;
                    for (int j = 0; j < HEIGHT; j++) {
                        for (int i = WIDTH - 1; i >= 0; i--) {
                            if (map[i][j] != 0 && map[i + 1][j] == 0) {
                                int k = i + 1;
                                while (k < WIDTH && map[k][j] == 0)
                                    k++;
                                if (map[k - 1][j] == 0) {
                                    if (map[i][j] == map[k][j]) {
                                        map[k][j]++;
                                        map[i][j] = 0;
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        spr_tiles[k][j].setTexture(tex_tiles[map[k][j]]);
                                        tiles--;
                                    } else {
                                        spr_tiles[k - 1][j].setTexture(tex_tiles[map[i][j]]);
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        std::swap(map[i][j], map[k - 1][j]);
                                    }
                                    turnmade = true;
                                }
                            } else if (map[i][j] != 0 && map[i][j] == map[i + 1][j]) {
                                map[i + 1][j]++;
                                map[i][j] = 0;
                                tiles--;
                                spr_tiles[i][j].setTexture(tex_tiles[0]);
                                spr_tiles[i + 1][j].setTexture(tex_tiles[map[i + 1][j]]);
                                turnmade = true;
                            }
                        }
                    }
                }
                if (Event.key.code == sf::Keyboard::Left && press_but == false) {
                    press_but = true;
                    for (int j = 0; j < HEIGHT; j++) {
                        for (int i = 1; i < WIDTH; i++) {
                            if (map[i][j] != 0 && map[i - 1][j] == 0) {
                                int k = i - 1;
                                while (k >= 0 && map[k][j] == 0)
                                    k--;
                                if (map[k + 1][j] == 0) {
                                    if (map[i][j] == map[k][j]) {
                                        map[k][j]++;
                                        map[i][j] = 0;
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        spr_tiles[k][j].setTexture(tex_tiles[map[k][j]]);
                                        tiles--;
                                    } else {
                                        spr_tiles[k + 1][j].setTexture(tex_tiles[map[i][j]]);
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        std::swap(map[i][j], map[k + 1][j]);
                                    }
                                    turnmade = true;
                                }
                            } else if (map[i][j] != 0 && map[i][j] == map[i - 1][j]) {
                                map[i - 1][j]++;
                                map[i][j] = 0;
                                tiles--;
                                spr_tiles[i][j].setTexture(tex_tiles[0]);
                                spr_tiles[i - 1][j].setTexture(tex_tiles[map[i - 1][j]]);
                                turnmade = true;
                            }
                        }
                    }
                }
                if (Event.key.code == sf::Keyboard::Down && !press_but) {
                    press_but = true;
                    for (int i = 0; i < WIDTH;i++) {
                        for (int j = HEIGHT - 2; j >= 0; j--) {
                            if (map[i][j] != 0 && map[i][j + 1] == 0) {
                                int k = j + 1;
                                while (k < HEIGHT && map[i][k] == 0)
                                    k++;
                                if (map[i][k - 1] == 0) {
                                    if (k != HEIGHT && map[i][j] == map[i][k]) {
                                        map[i][k]++;
                                        map[i][j] = 0;
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        spr_tiles[i][k].setTexture(tex_tiles[map[i][k]]);
                                        tiles--;
                                    } else {
                                        spr_tiles[i][k - 1].setTexture(tex_tiles[map[i][j]]);
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        std::swap(map[i][j], map[i][k - 1]);
                                    }
                                    turnmade = true;
                                }
                            } else if (map[i][j] != 0 && map[i][j] == map[i][j + 1]) {
                                map[i][j + 1]++;
                                map[i][j] = 0;
                                tiles--;
                                spr_tiles[i][j].setTexture(tex_tiles[0]);
                                spr_tiles[i][j + 1].setTexture(tex_tiles[map[i][j + 1]]);
                                turnmade = true;
                            }
                        }
                    }
                }
                if (Event.key.code == sf::Keyboard::Up ||
                    Event.key.code == sf::Keyboard::Right ||
                    Event.key.code == sf::Keyboard::Left ||
                    Event.key.code == sf::Keyboard::Down) {
                    if (turnmade) {
                        if (tiles < MAX_TILES) {
                            tiles++;
                            generatetile((sf::Sprite*)spr_tiles, map, tiles, tex_tiles[0], tex_tiles[1]);
                        }
                    } else if (tiles == WIDTH * HEIGHT) {
                        return 0;
                    }
                }
                if (Event.key.code == sf::Keyboard::Space) {
                    for (int i = 0; i < WIDTH; i++) {
                        for (int j = 0; j < HEIGHT; j++) {
                            if (map[i][j] == 0) {
                                map[i][j] = 1;
                                spr_tiles[i][j].setTexture(tex_tiles[1]);
                            }
                        }
                    }
                }
            }
            if (Event.type == sf::Event::KeyReleased) {
                press_but = false;
            }
        }
        window.clear();
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                window.draw(spr_tiles[j][i]);
            }
        }
        window.display();
    }
    return 0;
}
