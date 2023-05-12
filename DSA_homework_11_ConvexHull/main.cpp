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

vector<Vec2d> quickHull (Vec2d p1, Vec2d p2, vector<Vec2d> points, Graphics& g, int& count)
{
  //  g.line(p1,p2,YELLOW);

    vector<Vec2d> returnVec;
    count++;

    Vec2d Vec;
    Vec.x = (p1.x - p2.x);
    Vec.y = p1.y - p2.y;
    Vec2d yVec;
    yVec.x = -Vec.y;
    yVec.y =  Vec.x;
    yVec = yVec.unit();
    Vec2d longestPoint = points[0];
    double distance = 0;
    double localDistance = 0;
    int position = -10;
    //double bottom = sqrt(pow(yVec.x,2)+pow(yVec.y,2));
    Vec2d xVec;

    vector<Vec2d> nextVec;

    for (int e = 0; e < points.size(); e++)
    {
        xVec = points[e]-p2;
        if (points[e].exactlyEquals(p1) || points[e].exactlyEquals(p2))
        {
            continue;
        }
        localDistance = (yVec.x*xVec.x) + (yVec.y*xVec.y);
        if (localDistance>0) {nextVec.push_back(points[e]);}
        if (localDistance > distance)
        {
            distance = localDistance;
            longestPoint = points[e];
            position = e;
        }
    }

    if (position != -10)
    {
     //   g.ellipse(longestPoint, 5,5,GREEN,GREEN);
        points.erase(points.begin()+position);
        returnVec = quickHull(p1,longestPoint,nextVec,g,count);
        returnVec.push_back(longestPoint);
        vector<Vec2d> more = quickHull(longestPoint,p2,nextVec,g,count);
        for (int f = 0; f < more.size(); f++)
        {
            returnVec.push_back(more[f]);
        }
    }
    cout << count << endl;
    return returnVec;

}

vector<Vec2d> convexHull (vector<Vec2d> points, Graphics& graph)
{
    vector<Vec2d> hull;

    vector<Vec2d> compass;
    for (int b = 0; b < 4; b++)
    {
        compass.push_back(points[0]);
    }

    for (int a = 0; a < points.size(); a++)
    {
        if (points[a].y <= compass[0].y) {compass[0] = points[a];} //high
        if (points[a].x >= compass[1].x) {compass[1] = points[a];} //right
        if (points[a].y >= compass[2].y) {compass[2] = points[a];} //low
        if (points[a].x <= compass[3].x) {compass[3] = points[a];} //left
    }

    hull.push_back(compass[1]);
    hull.push_back(compass[3]);

//    for (int c = 0; c < compass.size(); c++)
//    {
//        if ((hull.size() <= 0 || compass[c].x != hull[0].x || compass[c].y != hull[0].y) &&
//            (hull.size() <= 1 || compass[c].x != hull[1].x || compass[c].y != hull[1].y) &&
//            (hull.size() <= 2 || compass[c].x != hull[2].x || compass[c].y != hull[2].y) &&
//            (hull.size() <= 3 || compass[c].x != hull[3].x || compass[c].y != hull[3].y))
//        {hull.push_back(compass[c]);}
//    }

//    for (int i = 0; i < hull.size(); i++)
//    {
//        graph.line(hull[i],hull[(i+1)%hull.size()],YELLOW);
//    }
    int count = 0;
    for (int g = 0; g < hull.size(); g++)
    {
        int h = (g+1)%hull.size();
        vector<Vec2d> quickSort = quickHull(hull[g],hull[h],points,graph,count);

        for (int k = 0; k < quickSort.size(); k++)
        {
            hull.insert(hull.begin()+g+k+1,quickSort[k]);
        }
    }

    return hull;
}

int main(int argc, char* argv[])
{
    vector<Vec2d> randomPoints;
    Graphics g("Convex Hull", 1024, 768);

    for (int i = 0; i < 5; i++)
    {
        randomPoints.push_back({g.randomInt(100,g.width()-100),g.randomInt(100,g.height()-100)});
    }

//    vector<Vec2d> randomLines = convexHull(randomPoints,g);

    while (g.draw()) {

            if (g.onKeyPress(' ')) {
                randomPoints.clear();
                for (int i = 0; i < 15; i++)
                {
                    randomPoints.push_back({g.randomInt(100,g.width()-100),g.randomInt(100,g.height()-100)});
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
        vector<Vec2d> randomLines = convexHull(randomPoints,g);

        g.polygon(randomLines,GREEN);
        g.points(randomPoints,WHITE);
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



