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
        void addPoints(int n);
        int getPoints();
        void playerReset();
        void setTimeConstraints(int floor, double time);
        void defaultTimeConstraints();
        double getThirdFloorTimeLimit();
        double getSecondFloorTimeLimit();
        double getFirstFloorTimeLimit();
        void displayTimeConstrainsts();

    private:
        string name;
        string object;
        int points;
        int lives;
        double timeConstraints[3];
};

// building class for creating and keeping track of the game properties
class building
{
    public:
        void generateThirdFloor();
        void generateSecondFloor();
        void generateFirstFloor();
        void generateBonusRound();
        user searchRoom(user player, string roomChoice);
    private:
        string rooms[8];
};

#endif // TEXTADVENTURE_H
