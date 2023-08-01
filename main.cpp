#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
// include the libs based on the OS
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // _WIN32

using namespace std;
void clearscr() // Cross-platform clear screen function
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif // _WIN32
}
void mysleep(int milliseconds) // Cross-platform sleep function
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif // _WIN32
}
struct SnakeSegment
{
    int x;
    int y;
    SnakeSegment *next;
};

// Ik a structure would suffice, but let the classes be
class Fruit
{
private:
    int x;
    int y;

public:
    // Construct Fruit with random coordinates values assigned
    Fruit(int n)
    {
        int tempx = rand() % n;
        while (tempx >= n || tempx <= 0)
            tempx = rand() % n;
        int tempy = rand() % (2 * n);
        while (tempy >= 2 * n || tempy <= 0)
            tempy = rand() % (2 * n);
        this->x = tempx;
        this->y = tempy;
    }
    // Safety first, always wear a rubber
    int getX() { return this->x; }
    int getY() { return this->y; }
};

class Snake
{
private:
    SnakeSegment *snakehead;
    char direction=' ';
public:
    Snake()
    {
        this->snakehead = new SnakeSegment{10, 10, nullptr};
        SnakeSegment *snakeseg1 = new SnakeSegment{9, 10, nullptr};
        SnakeSegment *snakeseg2 = new SnakeSegment{8, 10, nullptr};
        this->snakehead->next = snakeseg1;
        snakeseg1->next = snakeseg2;
        snakeseg2->next = nullptr;
        this->direction='r';
    }

    SnakeSegment *head() { return this->snakehead; }
    
    bool is_alive(int l, int h){
        if(this->snakehead->x==0 || this->snakehead->x==l-1|| this->snakehead->y==h-1 || this->snakehead->y==0){
            return false;
        }
        SnakeSegment *current = this->snakehead;
        while (current->next!=nullptr)
        {
            if(this->direction=='r' && (current->x==this->snakehead->x+1)){
                return false;
            }
            else if (this->direction=='l' && (current->x==this->snakehead->x-1)) 
            {
                return false;
            }
            current=current->next;
        }
        return true;
    }


    void Right()
    {
        this->direction='r';
        this->snakehead->x++;
    }

    void Left()
    {
        this->direction='l';
        this->snakehead->x--;
    }
    //Idk why, but it got reversed, I'll try to fix it later
    void Down(){
        this->direction='d';
        this->snakehead->y++;
    }
    void Up(){
        this->direction='u';
        this->snakehead->y--;
    }
    void Follow()
    {
        SnakeSegment *current = this->snakehead->next;
        while (current->next != nullptr)
        {
        }
    }
};

class GameMap
{
private:
    int h;
    int l;
    string *map;

public:
    // Constructor that initializez the map.
    // The length is 2 times bigger
    // because of the size of the characters
    GameMap(int _h)
    {
        this->h = _h;
        this->l = 2 * this->h;
        this->map = new string[h];
        for (int i = 0; i < this->h; i++)
        {
            this->map[i].resize(this->l);
            for (int j = 0; j < this->l; j++)
                (i == this->h - 1 || j == this->l - 1 || i == 0 || j == 0) ? this->map[i][j] = '#' : this->map[i][j] = ' ';
        }
    }

    void PutSnake(SnakeSegment *snake)
    {
        do
        {
            this->map[snake->y][snake->x] = '@';
            snake = snake->next;
        } while (snake->next != NULL);
        this->map[snake->y][snake->x] = '@';
    }

    void MakeFruit(Fruit &f)
    {
        this->map[f.getX()][f.getY()] = '%';
    }

    void ShowFrame(SnakeSegment *snake, Fruit &f)
    {
        for (int i = 0; i < this->h; i++)
        {
            this->map[i].resize(this->l);
            for (int j = 0; j < this->l; j++)
                (i == this->h - 1 || j == this->l - 1 || i == 0 || j == 0) ? this->map[i][j] = '#' : this->map[i][j] = ' ';
        }
        MakeFruit(f);
        PutSnake(snake);
        for (int i = 0; i < this->h; i++)
        {
            cout << map[i] << endl;
        }
    }
    int height() { return this->h; }
    int length() { return this->l; }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int size = 25;

    // Create the game map
    GameMap game = GameMap(size);

    // Initialize the snake
    Snake *snake = new Snake();

    // Initialize the fruit
    Fruit f = Fruit(size);

    // Game Mainloop
    for (int i = 0; i < 300; i++) {
        clearscr();
        if (!snake->is_alive(game.length(), game.height())) {
            cout << "Game over" << endl;
            break;
        }
        cout << f.getX() << " " << f.getY() << endl;
        game.ShowFrame(snake->head(), f);
        snake->Down();
        mysleep(200);
    }

    // Free allocated memory for snake
    delete snake;

    return 0;
}
