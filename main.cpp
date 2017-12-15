#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <SFML/Graphics.hpp>
const int TILES_COUNT=29;
const int HEIGHT=10;
const int WIDTH=10;
void generatetile(sf::Sprite *spr_tiles,int (&map)[WIDTH][HEIGHT],int &tiles,sf::Texture empty,sf::Texture &n1) {
    if(tiles==HEIGHT*WIDTH) {
        return;
    }
    int x=rand()%WIDTH;
    int y=rand()%HEIGHT;
    while(map[x][y]!=0) {
        x=rand()%WIDTH;
        y=rand()%HEIGHT;
    }
    (*(spr_tiles+x*WIDTH+y)).setTexture(n1);
    map[x][y]=1;
}
int main() {
    srand(time(0)); //иниализация рандома
    sf::RenderWindow window(sf::VideoMode(66*WIDTH, 66*HEIGHT), "rprtr258's 2048"); //основное окно программы
    sf::Texture tex_tiles[TILES_COUNT]; //все виды текстур
    int tiles=1; //количество всех тайлов
    //int score=0; //TODO:сделать счет
    std::ifstream in("save.txt");
    //in << WIDTH << HEIGHT << score;
    in.close();
    bool press_but=false;
    for(int i=0;i<TILES_COUNT;i++) { //чтение и установка текстур
        std::ostringstream str;
        str << "img\\" << i << ".png";
        if (!tex_tiles[i].loadFromFile(str.str())) {
            return 1;
        }
    }
    sf::Sprite spr_tiles[WIDTH][HEIGHT];
    int map[WIDTH][HEIGHT];
    for(int i=0;i<HEIGHT;i++) {
        for(int j=0;j<WIDTH;j++) {
            spr_tiles[j][i].setTexture(tex_tiles[0]);
            spr_tiles[j][i].setPosition(j*66,i*66);
            map[j][i]=0;
        }
    }
    generatetile((sf::Sprite*)spr_tiles,map,tiles,tex_tiles[0],tex_tiles[1]);
    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            if (Event.type==sf::Event::Closed) {
                window.close();
                return 0;
            }
            if (Event.type==sf::Event::KeyPressed) {
                if (Event.key.code==sf::Keyboard::Up && press_but==false) {
                    press_but=true;
                    bool turnmade=false;
                    for(int i=0;i<WIDTH;i++) { //перебор х
                        for(int j=1;j<HEIGHT;j++) { //перебор у
                            if(map[i][j]!=0 && map[i][j-1]==0) {
                                int k;
                                for(k=j-1;k>=0 && map[i][k]==0;k--); //перебор по y вверх
                                if(map[i][j]!=0 && map[i][k+1]==0) {
                                    if(map[i][j]==map[i][k]) {
                                        map[i][k]++;
                                        map[i][j]=0;
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        spr_tiles[i][k].setTexture(tex_tiles[map[i][k]]);
                                        tiles--;
                                    } else {
                                        spr_tiles[i][k+1].setTexture(tex_tiles[map[i][j]]);
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        std::swap(map[i][j],map[i][k+1]);
                                    }
                                    turnmade=true;
                                }
                            } else if(map[i][j]!=0) {
                                if(map[i][j]==map[i][j-1]) {
                                    map[i][j-1]++;
                                    map[i][j]=0;
                                    tiles--;
                                    spr_tiles[i][j].setTexture(tex_tiles[0]);
                                    spr_tiles[i][j-1].setTexture(tex_tiles[map[i][j-1]]);
                                    turnmade=true;
                                }
                            }
                        }
                    }
                    if(turnmade) {
                        if(tiles<HEIGHT*WIDTH) {
                            tiles++;
                            generatetile((sf::Sprite*)spr_tiles,map,tiles,tex_tiles[0],tex_tiles[1]);
                        }
                        //TODO:сделать конец игры
                    } else if(tiles==WIDTH*HEIGHT) {
                        return 0;
                    }
                }
                if (Event.key.code==sf::Keyboard::Right && press_but==false) {
                    press_but=true;
                    bool turnmade=false;
                    for(int j=0;j<HEIGHT;j++) { //перебор y
                        for(int i=WIDTH-1;i>=0;i--) { //перебор x
                            if(map[i][j]!=0 && map[i+1][j]==0) {
                                int k;
                                for(k=i+1;k<WIDTH && map[k][j]==0;k++); //перебор по x вправо
                                if(map[i][j]!=0 && map[k-1][j]==0) {
                                    if(map[i][j]==map[k][j]) {
                                        map[k][j]++;
                                        map[i][j]=0;
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        spr_tiles[k][j].setTexture(tex_tiles[map[k][j]]);
                                        tiles--;
                                    } else {
                                        spr_tiles[k-1][j].setTexture(tex_tiles[map[i][j]]);
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        std::swap(map[i][j],map[k-1][j]);
                                    }
                                    turnmade=true;
                                }
                            } else if(map[i][j]!=0) {
                                if(map[i][j]==map[i+1][j]) {
                                    map[i+1][j]++;
                                    map[i][j]=0;
                                    tiles--;
                                    spr_tiles[i][j].setTexture(tex_tiles[0]);
                                    spr_tiles[i+1][j].setTexture(tex_tiles[map[i+1][j]]);
                                    turnmade=true;
                                }
                            }
                        }
                    }
                    if(turnmade) {
                        if(tiles<HEIGHT*WIDTH) {
                            tiles++;
                            generatetile((sf::Sprite*)spr_tiles,map,tiles,tex_tiles[0],tex_tiles[1]);
                        }
                    } else if(tiles==WIDTH*HEIGHT) {
                        return 0;
                    }
                }
                if (Event.key.code==sf::Keyboard::Left && press_but==false) {
                    press_but=true;
                    bool turnmade=false;
                    for(int j=0;j<HEIGHT;j++) { //перебор y
                        for(int i=1;i<WIDTH;i++) { //перебор x
                            if(map[i][j]!=0 && map[i-1][j]==0) {
                                int k;
                                for(k=i-1;k>=0 && map[k][j]==0;k--); //перебор по x вправо
                                if(map[i][j]!=0 && map[k+1][j]==0) {
                                    if(map[i][j]==map[k][j]) {
                                        map[k][j]++;
                                        map[i][j]=0;
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        spr_tiles[k][j].setTexture(tex_tiles[map[k][j]]);
                                        tiles--;
                                    } else {
                                        spr_tiles[k+1][j].setTexture(tex_tiles[map[i][j]]);
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        std::swap(map[i][j],map[k+1][j]);
                                    }
                                    turnmade=true;
                                }
                            } else if(map[i][j]!=0) {
                                if(map[i][j]==map[i-1][j]) {
                                    map[i-1][j]++;
                                    map[i][j]=0;
                                    tiles--;
                                    spr_tiles[i][j].setTexture(tex_tiles[0]);
                                    spr_tiles[i-1][j].setTexture(tex_tiles[map[i-1][j]]);
                                    turnmade=true;
                                }
                            }
                        }
                    }
                    if(turnmade) {
                        if(tiles<HEIGHT*WIDTH) {
                            tiles++;
                            generatetile((sf::Sprite*)spr_tiles,map,tiles,tex_tiles[0],tex_tiles[1]);
                        }
                    } else if(tiles==WIDTH*HEIGHT) {
                        return 0;
                    }
                }
                if (Event.key.code==sf::Keyboard::Down && press_but==false) {
                    press_but=true;
                    bool turnmade=false;
                    for(int i=0;i<WIDTH;i++) { //перебор х
                        for(int j=HEIGHT-2;j>=0;j--) { //перебор у
                            if(map[i][j]!=0 && map[i][j+1]==0) {
                                int k;
                                for(k=j+1;k<HEIGHT && map[i][k]==0;k++); //перебор по y вниз
                                if(map[i][j]!=0 && map[i][k-1]==0) {
                                    if(k!=HEIGHT && map[i][j]==map[i][k]) {
                                        map[i][k]++;
                                        map[i][j]=0;
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        spr_tiles[i][k].setTexture(tex_tiles[map[i][k]]);
                                        tiles--;
                                    } else {
                                        spr_tiles[i][k-1].setTexture(tex_tiles[map[i][j]]);
                                        spr_tiles[i][j].setTexture(tex_tiles[0]);
                                        std::swap(map[i][j],map[i][k-1]);
                                    }
                                    turnmade=true;
                                }
                            } else if(map[i][j]!=0) {
                                if(map[i][j]==map[i][j+1]) {
                                    map[i][j+1]++;
                                    map[i][j]=0;
                                    tiles--;
                                    spr_tiles[i][j].setTexture(tex_tiles[0]);
                                    spr_tiles[i][j+1].setTexture(tex_tiles[map[i][j+1]]);
                                    turnmade=true;
                                }
                            }
                        }
                    }
                    if(turnmade) {
                        if(tiles<HEIGHT*WIDTH) {
                            tiles++;
                            generatetile((sf::Sprite*)spr_tiles,map,tiles,tex_tiles[0],tex_tiles[1]);
                        }
                    } else if(tiles==WIDTH*HEIGHT) {
                        return 0;
                    }
                }
                if (Event.key.code==sf::Keyboard::Space) {
                    for(int i=0;i<WIDTH;i++) { //перебор х
                        for(int j=0;j<HEIGHT;j++) { //перебор у
                            if(map[i][j]==0) {
                                map[i][j]=1;
                                spr_tiles[i][j].setTexture(tex_tiles[1]);
                            }
                        }
                    }
                }
            }
            if(Event.type==sf::Event::KeyReleased) {
                press_but=false;
                std::cout<<tiles<<std::endl;
            }
        }
        window.clear();
        //system("cls");
        for(int i=0;i<HEIGHT;i++) {
            for(int j=0;j<WIDTH;j++) {
                window.draw(spr_tiles[j][i]);
            }
        }
        window.display();
    }
    return 0;
}
