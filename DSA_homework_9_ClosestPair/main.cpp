#include "graphics.h"

using namespace std;
using namespace mssm;

class PointPair {
public:
    Vec2d p1;
    Vec2d p2;
    double distance;
};

PointPair smallestDistance(const vector<Vec2d>& localPoints)
{
    PointPair returnPair2; //establishes the returnPair
    returnPair2.p1 = localPoints[0];
    returnPair2.p2 = localPoints[1];
    returnPair2.distance = sqrt(pow(returnPair2.p1.x-returnPair2.p2.x,2)+pow(returnPair2.p1.y-returnPair2.p2.y,2));

    for (int a = 0; a < localPoints.size(); a++) //finds the smallest distance
    {
        for (int b = 0; b < localPoints.size(); b++)
        {
            if (b == a) {continue;}
            double c = sqrt(pow(localPoints[a].x-localPoints[b].x,2)+pow(localPoints[a].y-localPoints[b].y,2));
            if (c > (returnPair2.p2.y-returnPair2.p1.y)) {break;}

            if (returnPair2.distance > c)
            {
                returnPair2.distance = c;
                returnPair2.p1 = localPoints[a];
                returnPair2.p2 = localPoints[b];
            }
        }
    }

    return returnPair2;
}

PointPair recursiveYSort(vector<Vec2d>& localPoints, Graphics& g)
{
    PointPair returnPair;
    if (localPoints.size() <= 3) //smallest amount, no recursion
    {
        sort(localPoints.begin(),localPoints.end(),[](Vec2d a,Vec2d b){return a.y < b.y;}); // sorts by y
        returnPair = smallestDistance(localPoints);
    } else
    {
        vector<Vec2d> vecP1;
        vector<Vec2d> vecP2;

        PointPair pointPairP1;
        PointPair pointPairP2;

        int t = 0; //splits by x
        for (int s = 0; s < localPoints.size()/2; s++)
        {
            vecP1.push_back(localPoints[s]);
            t++;
        }
        for (int s = t; s < localPoints.size(); s++)
        {
            vecP2.push_back(localPoints[s]);
        }

        double middleLine = (vecP1[vecP1.size()-1].x + vecP2[0].x) / 2;

        //recursive call
        pointPairP1 = recursiveYSort(vecP1,g);
        pointPairP2 = recursiveYSort(vecP2,g);

        returnPair = pointPairP1.distance < pointPairP2.distance ? pointPairP1 : pointPairP2;

        int p1Pos = 0;
        int p2Pos = 0;

        //Merge
        for(int r = 0; r < vecP1.size() + vecP2.size(); r++)
        {
            if (p2Pos == vecP2.size() || (p1Pos != vecP1.size() && vecP1[p1Pos].y < vecP2[p2Pos].y))
            {
                localPoints[r] = vecP1[p1Pos];
                p1Pos++;
            } else
            {
                localPoints[r] = vecP2[p2Pos];
                p2Pos++;
            }
        }

        //forming the strip
        vector<Vec2d> middleVec;
        for (int s = 0; s < localPoints.size(); s++)
        {
            if (localPoints[s].x < middleLine + returnPair.distance && localPoints[s].x > middleLine - returnPair.distance)
            {
                middleVec.push_back(localPoints[s]);
            }
        }

        //searching the strip
        for (int g = 0; g < middleVec.size(); g++)
        {
            for (int h = g + 1; h < middleVec.size(); h++)
            {
                if (middleVec[g].y - middleVec[h].y >= returnPair.distance) {break;}
                double f = (middleVec[g]-middleVec[h]).magnitude();
                if (returnPair.distance > f)
                {
                    returnPair.distance = f;
                    returnPair.p1 = localPoints[g];
                    returnPair.p2 = localPoints[h];
                }
            }
        }
    }
    return returnPair;
}

PointPair closestPair(vector<Vec2d> points, Graphics& g)
{
    sort(points.begin(),points.end(),[](Vec2d a,Vec2d b){return a.x < b.x;}); // sorts by x
    return recursiveYSort(points, g);
}

PointPair bruteForce(const vector<Vec2d>& points, Graphics& g)
{
    PointPair returnPair;
    returnPair.distance = g.width()*g.height();
    for (int a = 0; a < points.size(); a++)
    {
        for (int b = 0; b < points.size(); b++)
        {
            if (b == a) {continue;}
            double c = sqrt(pow(points[a].x-points[b].x,2)+pow(points[a].y-points[b].y,2));
            if (returnPair.distance > c)
            {
                returnPair.distance = c;
                returnPair.p1 = points[a];
                returnPair.p2 = points[b];
            }
        }
    }
    return returnPair;
}

int main(int argc, char* argv[])
{
    Graphics g("Hello Graphics!", 1024, 768);

    int numberOfPoints = 50;

    vector<Vec2d> randomPoints;
    for (int i = 0; i < numberOfPoints; i++)
    {
        randomPoints.push_back({randomInt(0,g.width()),randomInt(0,g.height())});
    }

    PointPair brute = bruteForce(randomPoints,g);
    PointPair smart = closestPair(randomPoints,g);

    while (g.draw()) {

        for (int i = 0; i < numberOfPoints; i++)
        {
            g.point(randomPoints[i],WHITE);
            g.text({0,758},10,to_string(brute.distance),GREEN);
            g.text({0,748},10,to_string(brute.p2.x),GREEN);
            g.text({60,748},10,to_string(brute.p2.y),GREEN);
            g.text({0,738},10,to_string(brute.p1.x),GREEN);
            g.text({60,738},10,to_string(brute.p1.y),GREEN);

            g.text({0,728},10,to_string(smart.distance),BLUE);
            g.text({0,718},10,to_string(smart.p2.x),BLUE);
            g.text({60,718},10,to_string(smart.p2.y),BLUE);
            g.text({0,708},10,to_string(smart.p1.x),BLUE);
            g.text({60,708},10,to_string(smart.p1.y),BLUE);

            g.line(brute.p1,brute.p2,GREEN);
            g.ellipse(brute.p1,10,10,GREEN);
            g.ellipse(brute.p2,10,10,GREEN);
            g.ellipse(smart.p1,20,20,BLUE);
            g.ellipse(smart.p2,20,20,BLUE);
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


