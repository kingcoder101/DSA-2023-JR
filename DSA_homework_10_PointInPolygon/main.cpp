#include "graphics.h"

using namespace std;
using namespace mssm;

class PointPair {
public:
    Vec2d p1;
    Vec2d p2;
};

bool pointInPolygon(Vec2d point, vector<Vec2d> points)
{
    int hits = 0;
    vector<PointPair> lines;
    //get all the possible lines we can hit
    for (int i = 0; i < points.size(); i++)
    {
        int j = (i+1)%points.size();
        Vec2d& p1{points[i]};
        Vec2d& p2{points[j]};
        bool a = p1.x <= p2.x ? (p1.x <= point.x) : (p2.x <= point.x);//left
        bool b = p1.x >= p2.x ? (p1.x >= point.x) : (p2.x >= point.x);//right
        bool c = p1.y <= p2.y ? (p1.y <= point.y) : (p2.y <= point.y);//below
        if (a && b && c)
        {
            PointPair hitLine;
            hitLine.p1 = points[i];
            hitLine.p2 = points[j];
            lines.push_back(hitLine);
        }
    }


    for (int i = 0; i < lines.size(); i++)
    {
        double slope = (lines[i].p1.y - lines[i].p2.y)/(lines[i].p1.x - lines[i].p2.x);
        if (point.y - lines[i].p1.y >= slope*(point.x - lines[i].p1.x))
        {
            if (lines[i].p2.x == point.x || lines[i].p1.x == point.x)
            {
                if (lines[i].p2.x == point.x)
                {
                    if (lines[i].p1.x >= point.x)
                    {
                        hits += 1;
                    }
                } else
                {
                    if (lines[i].p2.x >= point.x)
                    {
                        hits += 1;
                    }
                }

            } else
            {
                hits += 1;
            }
        }
    }
    return hits%2 == 0 ? false : true;
}

int main(int argc, char* argv[])
{
    vector<Vec2d> randomPoints;
    randomPoints.push_back({800,600});
    randomPoints.push_back({1000,700});
    randomPoints.push_back({910,710});
    randomPoints.push_back({810,730});
    randomPoints.push_back({610,530});
    bool test = pointInPolygon({750,650},randomPoints);

    Graphics g("Polygon", 1024, 768);

    while (g.draw()) {

        if (g.onMouseRelease(MouseButton::Left))
        {
            randomPoints.push_back({g.mousePos().x,g.mousePos().y});
        }

        for (int i = 0; i < randomPoints.size() - 1; i++)
        {
            if (randomPoints.size() > 3) {g.line(randomPoints[i],randomPoints[i + 1]);}
        }
        if (randomPoints.size() > 3) {g.line(randomPoints[0],randomPoints[randomPoints.size()-1]);}
        //g.point({750,650},BLUE);

        if (randomPoints.size() > 3)
        {
            for (int j = 0; j < 100; j++)
            {
                for (int k = 0; k < 100; k++)
                {
                    Vec2d f = {(g.width()/2)-50+(j*5),(g.height()/2)-50+(k*5)};
                    if (pointInPolygon(f,randomPoints))
                    {
                        g.point(f,GREEN);
                    } else
                    {
                        g.point(f,RED);
                    }
                }
            }
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


}


