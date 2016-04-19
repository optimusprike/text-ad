#ifndef TEXTADVENTURE_H
#define TEXTADVENTURE_H
#include <string>

using namespace std;

// user class for keeping track of player's properties
class user
{
    public:
        user();
        void setName(string n);
        string getName();
        void setObject(string o);
        string getObject();
        int getLives();
        void decreaseLives();
        void decrementPoints();
        int getPoints();
        void playerReset();
        void setTimeConstraints(int floor, double time);
        void defaultTimeConstraints();
        double getThirdFloorTimeLimit();
        double getSecondFloorTimeLimit();
        double getFirstFloorTimeLimit();
        void displayTimeConstrainsts();
        void setTimeDecreaser(double t);
        double getTimeDecreaser();

    private:
        string name;
        string object;
        int points;
        int lives;
        double timeConstraints[3];
        double timeDecreaser;
};

// building class for creating and keeping track of the game properties
class building
{
    public:
        building();
        void generateThirdFloor();
        void generateSecondFloor();
        void generateFirstFloor();
        user searchRoom(user player, string roomChoice, double timeRemaining);
    private:
        string rooms[10];
        int randFloor;
};

#endif // TEXTADVENTURE_H
