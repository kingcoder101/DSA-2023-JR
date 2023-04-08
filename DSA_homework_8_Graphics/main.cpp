#include "graphics.h"

using namespace std;
using namespace mssm;

int main(int argc, char* argv[])
{
    Graphics g("Hello Graphics!", 1024, 768);

    vector<Vec2d> arrows;
    while (g.draw()) {
        if(g.onMousePress(MouseButton::Left))
        {
            arrows.push_back(g.mousePos());
        }

        for (int i = 0; i + 2 <= arrows.size(); i += 2)
        {
            g.line(arrows[i],arrows[i+1]);
            g.cout << acos(arrows[i].magnitude()*arrows[i+1].magnitude()/(arrows[i].x*arrows[i+1].x+arrows[i].x*arrows[i+1].x)) * (crossProduct(arrows[i],arrows[i+1]) < 0 ? -1 : 1) << endl;
        }
    }

////2. cone creator
//  while (g.draw()) {
//        //x^2-10000=y^2
//        Vec2d mouse = g.mousePos();

//        //mouse line variables
//        int mouseDistance = sqrt(mouse.x*mouse.x + mouse.y*mouse.y);
//        double maxDistance = sqrt(1024*1024 + 768*768);

//        for(int i = 0; i < 360; i++)
//        {
//            Vec2d location;
//            location.y = sin(i)*100;
//            location.x = cos(i)*100;
//            int mouseDistance = sqrt(pow(mouse.x-location.x,2) + pow(mouse.y-location.y,2));
//            int a = 0+(255*mouseDistance/maxDistance);
//            int b = 255-(255*mouseDistance/maxDistance);
//            g.line({location.x+512,location.y+384},mouse,{0,a,b});
//            g.line({-location.x+512,-location.y+384},mouse,{0,a,b});
//            g.line({location.x+512,-location.y+384},mouse,{0,a,b});
//            g.line({-location.x+512,location.y+384},mouse,{0,a,b});
//        }

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


