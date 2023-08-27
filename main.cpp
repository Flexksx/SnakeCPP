#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include </home/cristi/Documents/Code/cpp/Snake.cpp>
#include <ctime>  // Include <ctime> for time() function
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif // _WIN32


bool kbhit() {
#ifdef _WIN32
    return _kbhit();
#else
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
#endif // _WIN32
}

char getkey() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif // _WIN32
}



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

    //Rules
    cout<<"Control with W-up, S-down, D-right, A-left. Press Q to quit."<<endl;


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
        if (kbhit()) {
        char input = getkey();
        switch (input) {
            case 'w':
                snake->Up();
                break;
            case 's':
                snake->Down();
                break;
            case 'a':
                snake->Left();
                break;
            case 'd':
                snake->Right();
                break;
            case 'q':
                cout<<"Game quit."<<endl;
                return 1;
                break;
        }
    }
        cout << f.getX() << " " << f.getY() << endl;
        game.ShowFrame(snake->head(), f);
        mysleep(200);
    }

    // Free allocated memory for snake
    delete snake;

    return 0;
}
