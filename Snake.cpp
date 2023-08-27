struct SnakeSegment
{
    int x;
    int y;
    SnakeSegment *next;
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