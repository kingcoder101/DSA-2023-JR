#include "graphics.h"

using namespace std;
using namespace mssm;

class PointPair {
public:
    Vec2d p1;
    Vec2d p2;
    double distance;
};

PointPair closestPair(const vector<Vec2d>& points)
{

}

int main(int argc, char* argv[])
{
    Graphics g("Hello Graphics!", 1024, 768);

    vector<Vec2d> randomPoints;
    for (int i = 0; i < 50; i++)
    {
        randomPoints.push_back({randomInt(0,g.width()),randomInt(0,g.height())});
    }

    while (g.draw()) {

        for (int i = 0; i < 50; i++)
        {
            g.point(randomPoints[i],WHITE);
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


