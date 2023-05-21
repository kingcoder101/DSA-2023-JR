#include "graphics.h"

using namespace std;
using namespace mssm;

class Cell {
public:
    bool east;//0=closed
    bool south;
    int start; //1=start, 2=end
    bool visited;
};

class Maze {
public:
    vector<vector<Cell>> walls;
public:
    void recursion (Vec2d pos);
    void makeMaze (int width, int height);
};

void Maze::recursion (Vec2d pos)
{
    if (pos.x >= walls.size() || pos.x < 0 || pos.y >= walls[pos.x].size() || pos.y < 0)
    {
        return;
    }

    walls[pos.x][pos.y].visited = true;

    for (int j = 0; j < 4; j++)
    {
        int move = randomInt(0,3);
        bool left = (pos.x > 0 && !walls[pos.x-1][pos.y].visited);
        bool right = (pos.x < walls.size()-1 && !walls[pos.x+1][pos.y].visited);
        bool up = (pos.y > 0 && !walls[pos.x][pos.y-1].visited);
        bool down = (pos.y < walls[pos.x].size()-1 && !walls[pos.x][pos.y+1].visited);

        int target = -1;
        for (int a = 0; a < move; a++)
        {
            switch (a)
            {
            case 0:
                if (left)
                {
                    target = 0;
                    break;
                }
            case 1:
                if (right)
                {
                    target = 1;
                    break;
                }
            case 2:
                if (up)
                {
                    target = 2;
                    break;
                }
            case 3:
                if (down)
                {
                    target = 3;
                }
                break;
            }
        }

        switch (target)
        {
        case 0:
            walls[pos.x-1][pos.y].east = true;
            recursion({pos.x-1,pos.y});
            break;
        case 1:
            walls[pos.x][pos.y].east = true;
            recursion({pos.x+1,pos.y});
            break;
        case 2:
            walls[pos.x][pos.y-1].south = true;
            recursion({pos.x,pos.y-1});
            break;
        case 3:
            walls[pos.x][pos.y].south = true;
            recursion({pos.x,pos.y+1});
            break;
        }
    }
}

void Maze::makeMaze (int width, int height)
{
    walls = vector<vector<Cell>>(width,vector<Cell>(height));
    Vec2d pos;

    if (randomInt(0,1))
    {pos=Vec2d{randomInt(0,walls.size()-1),0};} else
    {pos=Vec2d{0,randomInt(0,walls[0].size()-1)};}

    walls[pos.x][pos.y].start++;

    recursion(pos);
}

int main(int argc, char* argv[])
{
    Maze randomMaze;
    Graphics g("Convex Hull", 500, 250);

    randomMaze.makeMaze(20,10);

    while (g.draw()) {

            if (g.onKeyPress(' ')) {
                randomMaze.makeMaze(20,10);
            }

            g.rect({0,0},500,250,WHITE,WHITE);
            g.rect({0,0},500,10,BLACK,BLACK);
            //g.rect({0,240},500,10,BLACK,BLACK);
            g.rect({0,0},10,250,BLACK,BLACK);
            //g.rect({490,0},10,250,BLACK,BLACK);

            for (int m = 0; m < randomMaze.walls.size(); m++)
            {
                for (int n = 0; n < randomMaze.walls[0].size(); n++)
                {
                    if (randomMaze.walls[m][n].visited == 0) {g.rect({10+m*20,10+n*20},10,10,BLACK,BLACK);}
                    if (!randomMaze.walls[m][n].east) {g.rect({20+m*20,10+n*20},10,10,BLACK,BLACK);}
                    if (!randomMaze.walls[m][n].south){g.rect({10+m*20,20+n*20},10,10,BLACK,BLACK);}
                    g.rect({20+m*20,20+n*20},10,10,BLACK,BLACK);
                }
            }



//        Vec2d Vec;
//        Vec.x = (randomPoints[0].x - randomPoints[1].x);
//        Vec.y = randomPoints[0].y - randomPoints[1].y;
//        Vec2d yVec;
//        yVec.x = -Vec.y;
//        yVec.y =  Vec.x;
//        yVec = yVec.unit();
//        Vec2d xVec;
//        xVec = g.mousePos()-randomPoints[1];
//        g.text({10,730},20,to_string((yVec.x*xVec.x) + (yVec.y*xVec.y)));


//        g.line(randomPoints[0],randomPoints[1]);
//        g.line(randomPoints[1],randomPoints[1]+yVec*100,YELLOW);

//        if(g.onMousePress(MouseButton::Left))
//        {
//            randomPoints[0]=randomPoints[1];
//            randomPoints[1]=g.mousePos();
//        }
    }
}

////1. lightspeed creator
//     while (g.draw()) {
//        Vec2d mouse = g.mousePos();
//        int mouseDistance = sqrt(mouse.x*mouse.x + mouse.y*mouse.y);
//        double maxDistance = sqrt(1024*1024 + 768*768);
//        int a = 0+(255*mouseDistance/maxDistance);
//        int b = 255-(255*mouseDistance/maxDistance);
//        Vec2d location;
//        for(int i = 0; i < 250; i++)
//        {
//            location = {g.randomInt(0,1024),g.randomInt(0,768)};
//            g.line(mouse,location, {0,a,b});
//        }
//     }


//        g.cout << "Press H to say Hi" << endl;
//        if (g.onKeyPress('H')) {
//            g.cerr << "Hello!!" << endl;
//        }

//        auto key = g.getKeyPressed();
//        if (key != Key::None) {
//            g.cerr << key << endl;
//        }

//        if (g.onKeyPress(Key::ESC)) {
//            break;
//        }

//        if (g.isKeyPressed(' ')) {
//            g.cout << "Space bar is pressed" << endl;
//        }

//        if (g.isMousePressed(MouseButton::Left)) {
//            Vec2d pos = g.mousePos();
//            double x = pos.x;
//            double y = pos.y;

//            stringstream ss;
//            ss << "Left Mouse: " << x << " " << y;

//            g.text(pos, 20, ss.str());
//        }



