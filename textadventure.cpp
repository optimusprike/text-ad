#include "textadventure.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <limits>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

string toString(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

//////////////USER CLASS METHODS BELOW/////////////////////

// constructor predefining user properties
user::user()
{
    lives = 3;
    object = "";
    points = 103;
    timeConstraints[0] = 60;
    timeConstraints[1] = 40;
    timeConstraints[2] = 30;
    timeDecreaser = 0;
}

// assigns user a name
void user::setName(string n)
{
    name = n;
}

// returns the user's name
string user::getName()
{
    return name;
}

// updates what the user is holding
void user::setObject(string o)
{
    object = o;
}

// returns what the user is holding
string user::getObject()
{
    return object;
}

// returns the number of lives the user has left
int user::getLives()
{
    return lives;
}

// decrements the user's number of lives
void user::decreaseLives()
{
    lives--;
}

// decrements points
void user::decrementPoints()
{
    points--;
}

//returns the amount of points the user has
int user::getPoints()
{
    return points;
}

// sets the user properties back to the way they started
void user::playerReset()
{
    lives = 3;
    object = "";
    points = 103;
}

// assigns new values to game time constraints
void user::setTimeConstraints(int floor, double time)
{
    timeConstraints[floor] = time;
}

// set time limits back to how they were originally
void user::defaultTimeConstraints()
{
    timeConstraints[0] = 60;
    timeConstraints[1] = 40;
    timeConstraints[2] = 30;
}

// returns the time it takes to escape the third floor
double user::getThirdFloorTimeLimit()
{
    return timeConstraints[0];
}

// returns the time it takes to escape the second floor
double user::getSecondFloorTimeLimit()
{
    return timeConstraints[1];
}

// returns the time it takes to escape the first floor
double user::getFirstFloorTimeLimit()
{
    return timeConstraints[2];
}

// displays current times constraints
void user::displayTimeConstrainsts()
{
    cout << endl;
    cout << "Current Time Limits";
    cout << endl;
    cout << "Third Floor Time: ";
    cout << timeConstraints[0];
    cout << " seconds";
    cout << endl;
    cout << "Second Floor Time: ";
    cout << timeConstraints[1];
    cout << " seconds";
    cout << endl;
    cout << "First Floor Time: ";
    cout << timeConstraints[2];
    cout << " seconds";
    cout << endl;
}

// sets the amount of time taken away from the user
void user::setTimeDecreaser(double t)
{
    timeDecreaser = t;
}

// returns the amount of time take away from the user
double user::getTimeDecreaser()
{
    return timeDecreaser;
}

//////////////USER CLASS METHODS ABOVE/////////////////////

//////////////BUILDING CLASS METHODS BELOW/////////////////////

// constructor for predefining the randFloor integer
building::building()
{
    srand(time(0));
    randFloor = rand()%3;
}

// randomly creates the rooms of the third floor
// with properties of holding a key, holding a
// a faux key, holding a riddle, being empty,
// and possibly a room that decreases the remaining time
void building::generateThirdFloor()
{
    if(randFloor == 0)
    {
        //automatically assign all rooms empty
        for(int i = 0; i < 10; i++)
        {
            rooms[i] = "empty";
        }

        //4 different random numbers to assign which room for a key, a faux key, a riddle, and a time decreaser
        int key;
        int fauxKey;
        int riddle;
        int timeDecreaser;

        srand(time(0));
        key = rand()%10;

        do
        {
            fauxKey = rand()%10;
            riddle = rand()%10;
            timeDecreaser = rand()%10;
        }
        while(key == fauxKey || key == riddle || riddle == fauxKey ||
              timeDecreaser == key || timeDecreaser == fauxKey || timeDecreaser == riddle);

        //generate riddle based on key being in an even or odd number room
        if((key + 1)%2 == 0)
        {
            rooms[riddle] = "The key is inside of an even numbered room.";
        }
        else if((key + 1)%2 != 0)
        {
            rooms[riddle] = "The key is inside of an odd numbered room.";
        }

        rooms[key] = "key";
        rooms[fauxKey] = "faux key";
        rooms[timeDecreaser] = "time decreaser";
    }
    else
    {
        //automatically assign all rooms empty
        for(int i = 0; i < 10; i++)
        {
            rooms[i] = "empty";
        }

        //3 different random numbers to assign which room for a key, a faux key, and a riddle
        int key;
        int fauxKey;
        int riddle;

        srand(time(0));
        key = rand()%10;

        do
        {
            fauxKey = rand()%10;
            riddle = rand()%10;
        }
        while(key == fauxKey || key == riddle || riddle == fauxKey);

        //generate riddle based on key being in an even or odd number room
        if((key + 1)%2 == 0)
        {
            rooms[riddle] = "The key is inside of an even numbered room.";
        }
        else if((key + 1)%2 != 0)
        {
            rooms[riddle] = "The key is inside of an odd numbered room.";
        }

        rooms[key] = "key";
        rooms[fauxKey] = "faux key";
    }
}

// randomly creates the rooms of the second floor
// with properties of holding a key, holding 2
// faux keys, holding a riddle, being empty,
// and possibly a room that decreases the remaining time
void building::generateSecondFloor()
{
    if(randFloor == 1)
    {
        //automatically assign all rooms empty
        for(int i = 0; i < 10; i++)
        {
            rooms[i] = "empty";
        }

        //5 different random numbers to assign which room for a key, 2 faux keys, a riddle, and a time decreaser
        int key;
        int firstFauxKey;
        int secondFauxKey;
        int riddle;
        int timeDecreaser;

        srand(time(0));
        key = rand()%10;

        do
        {
            firstFauxKey = rand()%10;
            secondFauxKey = rand()%10;
            riddle = rand()%10;
            timeDecreaser = rand()%10;
        }
        while(key == firstFauxKey || key == secondFauxKey || key == riddle || firstFauxKey == secondFauxKey ||
              firstFauxKey == riddle || secondFauxKey == riddle || timeDecreaser == key ||
              timeDecreaser == firstFauxKey || timeDecreaser == secondFauxKey || timeDecreaser == riddle);

        //generate riddle based on key being in an adjacent room to the riddle or not
        if(key == (riddle - 1) || key == (riddle + 1))
        {
            rooms[riddle] = "The key is inside of an adjacent room to this room.";
        }
        else
        {
            rooms[riddle] = "The key is not inside of an adjacent room to this room.";
        }

        rooms[key] = "key";
        rooms[firstFauxKey] = "faux key";
        rooms[secondFauxKey] = "faux key";
        rooms[timeDecreaser] = "time decreaser";
    }
    else
    {
        //automatically assign all rooms empty
        for(int i = 0; i < 10; i++)
        {
            rooms[i] = "empty";
        }

        //4 different random numbers to assign which room for a key, 2 faux keys, and a riddle
        int key;
        int firstFauxKey;
        int secondFauxKey;
        int riddle;

        srand(time(0));
        key = rand()%10;

        do
        {
            firstFauxKey = rand()%10;
            secondFauxKey = rand()%10;
            riddle = rand()%10;
        }
        while(key == firstFauxKey || key == secondFauxKey || key == riddle
              || firstFauxKey == secondFauxKey || firstFauxKey == riddle || secondFauxKey == riddle);

        //generate riddle based on key being in an adjacent room to the riddle or not
        if(key == (riddle - 1) || key == (riddle + 1))
        {
            rooms[riddle] = "The key is inside of an adjacent room to this room.";
        }
        else
        {
            rooms[riddle] = "The key is not inside of an adjacent room to this room.";
        }

        rooms[key] = "key";
        rooms[firstFauxKey] = "faux key";
        rooms[secondFauxKey] = "faux key";
    }
}

// randomly creates the rooms of the first floor
// with properties of holding a key, holding 3
// faux keys, holding a riddle, being empty,
// and possibly a room that decreases the remaining time
void building::generateFirstFloor()
{
    if(randFloor == 2)
    {
        //automatically assign all rooms empty
        for(int i = 0; i < 10; i++)
        {
            rooms[i] = "empty";
        }

        //6 different random numbers to assign which room for a key, 3 faux keys, a riddle, and time decreaser
        int key;
        int firstFauxKey;
        int secondFauxKey;
        int thirdFauxKey;
        int riddle;
        int timeDecreaser;

        srand(time(0));
        key = rand()%10;

        do
        {
            firstFauxKey = rand()%10;
            secondFauxKey = rand()%10;
            thirdFauxKey = rand()%10;
            riddle = rand()%10;
            timeDecreaser = rand()%10;
        }
        while(key == firstFauxKey || key == secondFauxKey || key == riddle || firstFauxKey == secondFauxKey ||
              firstFauxKey == riddle || secondFauxKey == riddle || thirdFauxKey == key ||
              thirdFauxKey == firstFauxKey || thirdFauxKey == secondFauxKey || thirdFauxKey == riddle ||
              timeDecreaser == key || timeDecreaser == firstFauxKey || timeDecreaser == secondFauxKey ||
              timeDecreaser == thirdFauxKey || timeDecreaser == riddle);

        rooms[key] = "key";
        rooms[firstFauxKey] = "faux key";
        rooms[secondFauxKey] = "faux key";
        rooms[thirdFauxKey] = "faux key";
        rooms[timeDecreaser] = "time decreaser";

        //generate riddle based on key not being in one certain room
        int emptyRoom;

        do
        {
            emptyRoom = rand()%10;
        }
        while(rooms[emptyRoom] != "empty");

        rooms[riddle] = "The key is not inside of room " + toString(emptyRoom + 1) + ".";
    }
    else
    {
        //automatically assign all rooms empty
        for(int i = 0; i < 10; i++)
        {
            rooms[i] = "empty";
        }

        //4 different random numbers to assign which room for a key, 3 faux keys, and a riddle
        int key;
        int firstFauxKey;
        int secondFauxKey;
        int thirdFauxKey;
        int riddle;

        srand(time(0));
        key = rand()%10;

        do
        {
            firstFauxKey = rand()%10;
            secondFauxKey = rand()%10;
            thirdFauxKey = rand()%10;
            riddle = rand()%10;
        }
        while(key == firstFauxKey || key == secondFauxKey || key == riddle
              || firstFauxKey == secondFauxKey || firstFauxKey == riddle || secondFauxKey == riddle
              || thirdFauxKey == key || thirdFauxKey == firstFauxKey || thirdFauxKey == secondFauxKey
              || thirdFauxKey == riddle);

        rooms[key] = "key";
        rooms[firstFauxKey] = "faux key";
        rooms[secondFauxKey] = "faux key";
        rooms[thirdFauxKey] = "faux key";

        //generate riddle based on key not being in one certain room
        int emptyRoom;

        do
        {
            emptyRoom = rand()%10;
        }
        while(rooms[emptyRoom] != "empty");

        rooms[riddle] = "The key is not inside of room " + toString(emptyRoom + 1) + ".";
    }
}

// method for searching the room the user selects,
// seeing what it holds (key, faux key, or riddle),
// giving the user an option of picking up a key,
// or trying to open the staircase door
user building::searchRoom(user player, string roomChoice, double timeRemaining)
{
    string option;
    bool doContinue;

    if(roomChoice.compare("1") == 0)
    {
        if(rooms[0].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 1 is empty";
            return player;
        }
        else if(rooms[0].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[0] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[0] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[0] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[0].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[0] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[0] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[0] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[0].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[0];
            return player;
        }
    }
    else if(roomChoice.compare("2") == 0)
    {
        if(rooms[1].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 2 is empty";
            return player;
        }
        else if(rooms[1].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[1] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[1] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[1] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[1].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[1] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[1] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[1] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[1].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[1];
            return player;
        }
    }
    else if(roomChoice.compare("3") == 0)
    {
        if(rooms[2].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 3 is empty";
            return player;
        }
        else if(rooms[2].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[2] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[2] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[2] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[2].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[2] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[2] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[2] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[2].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[2];
            return player;
        }
    }
    else if(roomChoice.compare("4") == 0)
    {
        if(rooms[3].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 4 is empty";
            return player;
        }
        else if(rooms[3].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[3] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[3] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[3] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[3].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[3] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[3] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[3] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[3].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[3];
            return player;
        }
    }
    else if(roomChoice.compare("5") == 0)
    {
        if(rooms[4].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 5 is empty";
            return player;
        }
        else if(rooms[4].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[4] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[4] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[4] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[4].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[4] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[4] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[4] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[4].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[4];
            return player;
        }
    }
    else if(roomChoice.compare("6") == 0)
    {
        if(rooms[5].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 6 is empty";
            return player;
        }
        else if(rooms[5].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[5] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[5] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[5] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[5].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[5] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[5] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[5] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[5].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[5];
            return player;
        }
    }
    else if(roomChoice.compare("7") == 0)
    {
        if(rooms[6].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 7 is empty";
            return player;
        }
        else if(rooms[6].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[6] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[6] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[6] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[6].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[6] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[6] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[6] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[6].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[6];
            return player;
        }
    }
    else if(roomChoice.compare("8") == 0)
    {
        if(rooms[7].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 8 is empty";
            return player;
        }
        else if(rooms[7].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[7] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[7] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[7] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[7].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[7] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[7] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[7] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[7].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[7];
            return player;
        }
    }
    else if(roomChoice.compare("9") == 0)
    {
        if(rooms[8].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 9 is empty";
            return player;
        }
        else if(rooms[8].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[8] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[8] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[8] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[8].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[8] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[8] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[8] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[8].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[8];
            return player;
        }
    }
    else if(roomChoice.compare("10") == 0)
    {
        if(rooms[9].compare("empty") == 0)
        {
            cout << endl;
            cout << "Room 10 is empty";
            return player;
        }
        else if(rooms[9].compare("faux key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[9] = "key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[9] = "faux key";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[9] = "empty";
                        player.setObject("faux key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[9].compare("key") == 0)
        {
            doContinue = false;

            do
            {
                cout << endl;
                cout << "You found a key!";
                cout << endl;
                cout << "Do you want to pick the key up?";
                cout << endl;
                cout << "1. Yes";
                cout << endl;
                cout << "2. No";
                cout << endl;
                cin >> option;

                if(option.compare("1") == 0)
                {
                    if(player.getObject().compare("key") == 0)
                    {
                        rooms[9] = "key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("faux key") == 0)
                    {
                        rooms[9] = "faux key";
                        player.setObject("key");
                        cout << endl;
                        cout << "You dropped the key you had and";
                        cout << endl;
                        cout << "the new key is in your possession.";
                    }
                    else if(player.getObject().compare("") == 0)
                    {
                        rooms[9] = "empty";
                        player.setObject("key");
                        cout << endl;
                        cout << "The key is in your possession.";
                    }

                    doContinue = true;
                }
                else if(option.compare("2") == 0)
                {
                    cout << endl;
                    cout << "The key is not in your possession.";
                    doContinue = true;
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue);

            return player;
        }
        else if(rooms[9].compare("time decreaser") == 0)
        {
            player.setTimeDecreaser(timeRemaining/4);
            cout << endl;
            cout << "Oh no! The guard saw you on the camera in this room.";
            cout << endl;
            cout << "A fourth of your remaining time will be taken away";
            return player;
        }
        else
        {
            cout << endl;
            cout << "You found a riddle! It reads:";
            cout << endl;
            cout << rooms[9];
            return player;
        }
    }
    else if(roomChoice.compare("11") == 0)
    {
        if(player.getObject().compare("") == 0)
        {
            cout << endl;
            cout << "You don't have a key to open the door.";
            player.decrementPoints();
            return player;
        }
        else if(player.getObject().compare("key") == 0)
        {
            player.setObject("winner");
            player.decrementPoints();
            return player;
        }
        else if(player.getObject().compare("faux key") == 0)
        {
            cout << endl;
            cout << "Oh no! Your key doesn't work for this door.";
            cout << endl;
            cout << "You will have to continue your search for the right key.";
            player.decrementPoints();
            return player;
        }
    }
    else
    {
        cout << "Error: You entered an incorrect option!";
        cout << endl;
        return player;
    }
}

//////////////BUILDING CLASS METHODS ABOVE/////////////////////

// main menu options
void StartMenu()
{
    cout << endl;
    cout << "What would you like to do?";
	cout << endl;
	cout << "1. Start Game";
	cout << endl;
	cout << "2. About/Tutorial";
	cout << endl;
    cout << "3. Settings";
	cout << endl;
	cout << "4. Highscores";
	cout << endl;
	cout << "5. Credits";
	cout << endl;
	cout << "6. Quit";
	cout << endl;
	cout << "Please selection an option using numerical values.";
	cout << endl;
}

// method for updating the time time the player
// has left when the game is in motion
double updateTime(clock_t startTime)
{
    return (clock() - startTime) / (double) CLOCKS_PER_SEC;
}

// updates the highscore list with the user's points
void updateHighscores(string name, int points)
{
    //read in highscore list from text file
    ifstream in;
    in.open("highscores.txt");

    if(in.fail())
    {
        ofstream out;
        out.open("highscores.txt");

        for(int i = 0; i < 9; i++)
        {
            out << "AAA";
            out << endl;
            out << "0";
            out << endl;
        }

        out << "AAA";
        out << endl;
        out << "0";

        out.close();

        in.open("highscores.txt");
    }

    string names[10];
    int scores[10];
    int place = 0;

    while(!in.eof())
    {
        in >> names[place];
        in >> scores[place];
        place++;
    }

    //check to see if the new score can be on the highscore list
    bool isHigh = false;

    for(int i = 0; i < 10; i++)
    {
        if(points > scores[i])
        {
            isHigh = true;
            break;
        }
    }

    //add the new score if it can be on the highscore list
    if(isHigh)
    {
        //create new list and add old values
        string newNames[11];
        int newScores[11];
        for(int i = 0; i < 10; i++)
        {
            newNames[i] = names[i];
            newScores[i] = scores[i];
        }

        //add new score to end of list
        newNames[10] = name;
        newScores[10] = points;

        //sort list using bubble sort
        for(int i = 0; i < 10; i++)
        {
            for(int j = i + 1; j < 11; j++)
            {
                string tempName;
                int tempScore;

                if(newScores[i] < newScores[j])
                {
                    tempName = newNames[i];
                    newNames[i] = newNames[j];
                    newNames[j] = tempName;

                    tempScore = newScores[i];
                    newScores[i] = newScores[j];
                    newScores[j] = tempScore;
                }
            }
        }

        //add values back to old list
        for(int i = 0; i < 10; i++)
        {
            names[i] = newNames[i];
            scores[i] = newScores[i];
        }
    }

    //write the highscores back to the text file
    ofstream out;
    out.open("highscores.txt");

    for(int i = 0; i < 10; i++)
    {
        out << names[i];
        out << endl;
        out << scores[i];
        if(i != 9)
        {
            out << endl;
        }
    }

    out.close();
}

// forward declaration for methods that call each other
void Choice1(user player);

void Choice2(user player);

void Choice3(user player);

void createHighscoreTextFile();

void viewHighscores();

// method for running the first floor of the game
void Choice3(user player)
{
    building prison;
    prison.generateFirstFloor();
    player.setTimeDecreaser(0);

    cout << endl;
    cout << "Your time starts now!";
    cout << endl;
    cout << "Hurry and escape before the prison guard comes!";
    cout << endl;

    clock_t startTime =  clock();
    double duration = updateTime(startTime);
    bool winner = false;
    string roomChoice;

    do
    {
        cout << endl;
        cout << "What would you like to do?";
        cout << endl;
        cout << "1. Search Room 1.";
        cout << endl;
        cout << "2. Search Room 2.";
        cout << endl;
        cout << "3. Search Room 3.";
        cout << endl;
        cout << "4. Search Room 4.";
        cout << endl;
        cout << "5. Search Room 5.";
        cout << endl;
        cout << "6. Search Room 6.";
        cout << endl;
        cout << "7. Search Room 7.";
        cout << endl;
        cout << "8. Search Room 8.";
        cout << endl;
        cout << "9. Search Room 9.";
        cout << endl;
        cout << "10. Search Room 10.";
        cout << endl;
        cout << "11. Try to exit the floor.";
        cout << endl;
        cout << "Time remaining: ";
        cout << player.getFirstFloorTimeLimit() - updateTime(startTime) - player.getTimeDecreaser();
        cout << " seconds";
        cout << endl;
        cin >> roomChoice;
        duration = updateTime(startTime);
        if(duration < player.getFirstFloorTimeLimit() - player.getTimeDecreaser())
        {
            player = prison.searchRoom(player, roomChoice, player.getThirdFloorTimeLimit() - duration);
        }
        if(player.getObject().compare("winner") == 0)
        {
            winner = true;
        }
    }while(!winner && updateTime(startTime) < player.getFirstFloorTimeLimit() - player.getTimeDecreaser());

    if(winner)
    {
        updateHighscores(player.getName() ,player.getPoints());

        cout << endl;
        cout << "You did it!";
        cout << endl;
        cout << "You made it out the building!";
        cout << endl;
        cout << "You earned ";
        cout << player.getPoints();
        cout << " points.";
        cout << endl;
        cout << "Would you like to start the game over or return to the main menu?";
        cout << endl;
        cout << endl;
        cout << "1. Start game over.";
        cout << endl;
        cout << "2. View Highscores";
        cout << endl;
        cout << "3. Return to main menu.";
        cout << endl;
        cin >> roomChoice;

        if(roomChoice.compare("1") == 0)
        {
            player.playerReset();
            Choice1(player);
        }
        else if(roomChoice.compare("2") == 0)
        {
            viewHighscores();
        }
        else if(roomChoice.compare("3") == 0)
        {
            //once the method ends, the user will automatically return to the main menu
        }
        else
        {
            cout << "Error: You entered an incorrect option!";
            cout << endl;
        }
    }
    else if(player.getLives() > 1)
    {
        player.decreaseLives();
        cout << endl;
        cout << "Oh no! Time's up!";
        cout << endl;
        cout << "You didn't make it out of the first floor in time.";
        cout << endl;
        cout << "However, you still have " << player.getLives() << " lives left.";
        cout << endl;
        cout << "Type anything and press enter to start playing";
        cout << endl;
        cin >> roomChoice;
        Choice3(player);
    }
    else
    {
        cout << endl;
        cout << "Oh no! Time's up!";
        cout << endl;
        cout << "You didn't make it out of the first floor in time";
        cout << endl;
        cout << "and you don't have any lives left.";
        cout << endl;
        cout << "Would you like to start the game over or return to the main menu?";
        cout << "1. Start game over.";
        cout << endl;
        cout << "2. Return to main menu.";
        cout << endl;
        cin >> roomChoice;

        if(roomChoice.compare("1") == 0)
        {
            player.playerReset();
            Choice1(player);
        }
        else if(roomChoice.compare("2") == 0)
        {
            //once the method ends, the user will automatically return to the main menu
        }
        else
        {
            cout << "Error: You entered an incorrect option!";
            cout << endl;
        }
    }
}

// method for running the second floor of the game
void Choice2(user player)
{
    building prison;
    prison.generateSecondFloor();
    player.setTimeDecreaser(0);

    cout << endl;
    cout << "Your time starts now!";
    cout << endl;
    cout << "Hurry and escape before the prison guard comes!";
    cout << endl;

    clock_t startTime =  clock();
    double duration = updateTime(startTime);
    bool winner = false;
    string roomChoice;

    do
    {
        cout << endl;
        cout << "What would you like to do?";
        cout << endl;
        cout << "1. Search Room 1.";
        cout << endl;
        cout << "2. Search Room 2.";
        cout << endl;
        cout << "3. Search Room 3.";
        cout << endl;
        cout << "4. Search Room 4.";
        cout << endl;
        cout << "5. Search Room 5.";
        cout << endl;
        cout << "6. Search Room 6.";
        cout << endl;
        cout << "7. Search Room 7.";
        cout << endl;
        cout << "8. Search Room 8.";
        cout << endl;
        cout << "9. Search Room 9.";
        cout << endl;
        cout << "10. Search Room 10.";
        cout << endl;
        cout << "11. Try to exit the floor.";
        cout << endl;
        cout << "Time remaining: ";
        cout << player.getSecondFloorTimeLimit() - updateTime(startTime) - player.getTimeDecreaser();
        cout << " seconds";
        cout << endl;
        cin >> roomChoice;
        duration = updateTime(startTime);
        if(duration < player.getSecondFloorTimeLimit() - player.getTimeDecreaser())
        {
            player = prison.searchRoom(player, roomChoice, player.getThirdFloorTimeLimit() - duration);
        }
        if(player.getObject().compare("winner") == 0)
        {
            winner = true;
        }
    }while(!winner && updateTime(startTime) < player.getSecondFloorTimeLimit() - player.getTimeDecreaser());

    if(winner)
    {
        cout << endl;
        cout << "You did it!";
        cout << endl;
        cout << "You made it out the second floor!";
        cout << endl;
        cout << "Now it's time to escape the first floor.";
        cout << endl;
        cout << "Type anything and press enter to start playing";
        cout << endl;
        cin >> roomChoice;
        player.setObject("");
        Choice3(player);
    }
    else if(player.getLives() > 1)
    {
        player.decreaseLives();
        cout << endl;
        cout << "Oh no! Time's up!";
        cout << endl;
        cout << "You didn't make it out of the second floor in time.";
        cout << endl;
        cout << "However, you still have " << player.getLives() << " lives left.";
        cout << endl;
        cout << "Type anything and press enter to start playing";
        cout << endl;
        cin >> roomChoice;
        Choice2(player);
    }
    else
    {
        cout << endl;
        cout << "Oh no! Time's up!";
        cout << endl;
        cout << "You didn't make it out of the second floor in time";
        cout << endl;
        cout << "and you don't have any lives left.";
        cout << endl;
        cout << "Would you like to start the game over or return to the main menu?";
        cout << "1. Start game over.";
        cout << endl;
        cout << "2. Return to main menu.";
        cout << endl;
        cin >> roomChoice;

        if(roomChoice.compare("1") == 0)
        {
            player.playerReset();
            Choice1(player);
        }
        else if(roomChoice.compare("2") == 0)
        {
            //once the method ends, the user will automatically return to the main menu
        }
        else
        {
            cout << "Error: You entered an incorrect option!";
            cout << endl;
        }
    }
}

// method for running the third floor of the game
void Choice1(user player)
{
    building prison;
    prison.generateThirdFloor();
    player.setTimeDecreaser(0);

    cout << endl;
    cout << "Your time starts now!";
    cout << endl;
    cout << "Hurry and escape before the prison guard comes!";
    cout << endl;

    clock_t startTime =  clock();
    double duration = updateTime(startTime);
    bool winner = false;
    string roomChoice;

    do
    {
        cout << endl;
        cout << "What would you like to do?";
        cout << endl;
        cout << "1. Search Room 1.";
        cout << endl;
        cout << "2. Search Room 2.";
        cout << endl;
        cout << "3. Search Room 3.";
        cout << endl;
        cout << "4. Search Room 4.";
        cout << endl;
        cout << "5. Search Room 5.";
        cout << endl;
        cout << "6. Search Room 6.";
        cout << endl;
        cout << "7. Search Room 7.";
        cout << endl;
        cout << "8. Search Room 8.";
        cout << endl;
        cout << "9. Search Room 9.";
        cout << endl;
        cout << "10. Search Room 10.";
        cout << endl;
        cout << "11. Try to exit the floor.";
        cout << endl;
        cout << "Time remaining: ";
        cout << player.getThirdFloorTimeLimit() - updateTime(startTime) - player.getTimeDecreaser();
        cout << " seconds";
        cout << endl;
        cin >> roomChoice;
        duration = updateTime(startTime);
        if(duration < player.getThirdFloorTimeLimit() - player.getTimeDecreaser())
        {
            player = prison.searchRoom(player, roomChoice, player.getThirdFloorTimeLimit() - duration);
        }
        if(player.getObject().compare("winner") == 0)
        {
            winner = true;
        }
    }while(!winner && updateTime(startTime) < player.getThirdFloorTimeLimit() - player.getTimeDecreaser());

    if(winner)
    {
        cout << endl;
        cout << "You did it!";
        cout << endl;
        cout << "You made it out the third floor!";
        cout << endl;
        cout << "Now it's time to escape the second floor.";
        cout << endl;
        cout << "Type anything and press enter to start playing";
        cout << endl;
        cin >> roomChoice;
        player.setObject("");
        Choice2(player);
    }
    else if(player.getLives() > 1)
    {
        player.decreaseLives();
        cout << endl;
        cout << "Oh no! Time's up!";
        cout << endl;
        cout << "You didn't make it out of the third floor in time.";
        cout << endl;
        cout << "However, you still have " << player.getLives() << " lives left.";
        cout << endl;
        cout << "Type anything and press enter to start playing";
        cout << endl;
        cin >> roomChoice;
        Choice1(player);
    }
    else
    {
        cout << endl;
        cout << "Oh no! Time's up!";
        cout << endl;
        cout << "You didn't make it out of the third floor in time";
        cout << endl;
        cout << "and you don't have any lives left.";
        cout << endl;
        cout << "Would you like to start the game over or return to the main menu?";
        cout << "1. Start game over.";
        cout << endl;
        cout << "2. Return to main menu.";
        cout << endl;
        cin >> roomChoice;

        if(roomChoice.compare("1") == 0)
        {
            player.playerReset();
            Choice1(player);
        }
        else if(roomChoice.compare("2") == 0)
        {
            //once the method ends, the user will automatically return to the main menu
        }
        else
        {
            cout << "Error: You entered an incorrect option!";
            cout << endl;
        }
    }
}

// game introduction
void StartGame(user player)
{
    //Game introduction
    string name;
    cout << endl;
    cout << "Let's get started! ";

    bool doContinue = false;

    do
    {
        cout << endl;
        cout << "Enter a 3 character name";
        cout << endl;
        cin >> name;

        if(name.size() == 3)
        {
            doContinue = true;
        }
        else if(name.size() < 3)
        {
            cout << "Error: The name you entered was too short.";
            cout << endl;
        }
        else if(name.size() > 3)
        {
            cout << "Error: The name you entered was too long.";
            cout << endl;
        }

    }while(!doContinue);

    player.setName(name);

    cout << endl;
    cout << "Hi ";
    cout << player.getName();
    cout << "!";
    cout << endl;
    cout << "Here are the rules of the game...";
    cout << endl;

    //game instructions
    cout << "1. You will try to escape each floor of the game.";
    cout << endl;
    cout << "2. You will have to search each room to find the key to the staircase.";
    cout << endl;
    cout << "3. Keep in mind there are multiple keys on each floor,";
    cout << endl;
    cout << "   but there is only one key to the staircase.";
    cout << endl;
    cout << "4. You can only hold onto one key at a time.";
    cout << endl;
    cout << "5. You will be timed for each floor.";
    cout << endl;
    cout << "6. A guard can see you on the security camera in certain rooms,";
    cout << endl;
    cout << "   which will decrease your remaining time by a quarter.";
    cout << endl;
    cout << "7. You have 3 lives for the entire game.";
    cout << endl;
    cout << "Are you ready to play?";
    cout << endl;


    //Prompt the user to begin the game
    cout << "Type anything and press enter to start playing";
    cout << endl;
    cin >> name;
    Choice1(player);
}

// text for explaining the them of the game
void displayTutorial()
{
    string temp;

    //information about the game and how's it's played
    cout << endl;
    cout << "About/Tutorial!";
    cout << endl;
    cout << "In this game the player must find their way through a 3 story prison";
    cout << endl;
    cout << "filled with guards and riddles to help them find their way out.";
    cout << endl;
    cout << "At the start of the game the player will find themselves in a hallway on";
    cout << endl;
    cout << "the 3rd floor of building. The player must search the the rooms, while";
    cout << endl;
    cout << "avoiding the guards, to find the right key that unlocks the room that sends";
    cout << endl;
    cout << "the player down to the next floor. The objective is to find the key on each ";
    cout << endl;
    cout << "floor to get to the ground floor and escape the prison.";
    cout << endl;

    cout << "Type anything and press enter to return to the main menu";
    cout << endl;
    cin >> temp;
}

// game settings for editing game time constraints
user openSettings(user player)
{
    bool doContinue = false;
    string choice;

    do
    {
        cout << endl;
        cout << "What would you like to do?";
        cout << endl;
        cout << "1. View Current Time Limits";
        cout << endl;
        cout << "2. Set Time Limits back to default";
        cout << endl;
        cout << "3. Edit a time limit";
        cout << endl;
        cout << "4. Return to the main menu";
        cout << endl;
        cin >> choice;

        if(choice.compare("1") == 0)
        {
            player.displayTimeConstrainsts();

            cout << "Type anything and press enter to return to the settings menu";
            cout << endl;
            cin >> choice;
        }
        else if(choice.compare("2") == 0)
        {
            player.defaultTimeConstraints();

            cout << endl;
            cout << "Time Limits successfully set back to default!";
            cout << endl;
            cout << "Type anything and press enter to return to the settings menu";
            cout << endl;
            cin >> choice;
        }
        else if(choice.compare("3") == 0)
        {
            bool doContinue2 = false;

            do
            {
                cout << endl;
                cout << "Which floor would you like to edit?";
                cout << endl;
                cout << "1. Third";
                cout << endl;
                cout << "2. Second";
                cout << endl;
                cout << "3. First";
                cout << endl;
                cin >> choice;

                if(choice.compare("1") == 0)
                {
                    do
                    {
                        bool inputFail;
                        string tester;
                        double newTime;

                        do
                        {
                        	inputFail = false;

                            cout << endl;
                            cout << "Enter a new time limit (integer value)";
                            cout << endl;
                            cin >> tester;

                            for(int i = 0; i < tester.length(); i++)
                            {
								if(int(tester.at(i)) < 48 || int(tester.at(i)) > 57)
								{
									inputFail = true;
								}
                            }

                            if(inputFail)
                            {
                                cout << "Error: You entered an incorrect option!";
                                cout << endl;
                            }
                            else
                            {
                                char tab2[1024];
                                strcpy(tab2, tester.c_str());
                                newTime = atof(tab2);
                            }
                        }while(inputFail);

                        doContinue2 = true;
                        player.setTimeConstraints(0 ,newTime);
                    }while(!doContinue2);
                }
                else if(choice.compare("2") == 0)
                {
                    do
                    {
                    	bool inputFail;
						string tester;
						double newTime;

						do
						{
							inputFail = false;

							cout << endl;
							cout << "Enter a new time limit (integer value)";
							cout << endl;
							cin >> tester;

							for(int i = 0; i < tester.length(); i++)
							{
								if(int(tester.at(i)) < 48 || int(tester.at(i)) > 57)
								{
									inputFail = true;
								}
							}

							if(inputFail)
							{
								cout << "Error: You entered an incorrect option!";
								cout << endl;
							}
							else
							{
								char tab2[1024];
								strcpy(tab2, tester.c_str());
								newTime = atof(tab2);
							}
						}while(inputFail);

						doContinue2 = true;
						player.setTimeConstraints(1 ,newTime);
                    }while(!doContinue2);
                }
                else if(choice.compare("3") == 0)
                {
                    do
                    {
                    	bool inputFail;
						string tester;
						double newTime;

						do
						{
							inputFail = false;

							cout << endl;
							cout << "Enter a new time limit (integer value)";
							cout << endl;
							cin >> tester;

							for(int i = 0; i < tester.length(); i++)
							{
								if(int(tester.at(i)) < 48 || int(tester.at(i)) > 57)
								{
									inputFail = true;
								}
							}

							if(inputFail)
							{
								cout << "Error: You entered an incorrect option!";
								cout << endl;
							}
							else
							{
								char tab2[1024];
								strcpy(tab2, tester.c_str());
								newTime = atof(tab2);
							}
						}while(inputFail);

						doContinue2 = true;
						player.setTimeConstraints(2 ,newTime);
                    }while(!doContinue2);
                }
                else
                {
                    cout << "Error: You entered an incorrect option!";
                    cout << endl;
                }
            }while(!doContinue2);
        }
        else if(choice.compare("4") == 0)
        {
            doContinue = true;
        }
        else
        {
            cout << "Error: You entered an incorrect option!";
            cout << endl;
        }
    }while(!doContinue);

    return player;
}

// generates a highscore list text file if none is to be found
void createHighscoreTextFile()
{
    ofstream out;
    out.open("highscores.txt");

    for(int i = 0; i < 9; i++)
    {
        out << "AAA";
        out << endl;
        out << "0";
        out << endl;
    }

    out << "AAA";
    out << endl;
    out << "0";

    out.close();

    viewHighscores();
}

// displays game highscores
void viewHighscores()
{
    ifstream in;
    in.open("highscores.txt");

    if(in.fail())
    {
        in.close();
        createHighscoreTextFile();
    }
    else
    {
        string name;
        int score;
        int place = 1;

        cout << endl;
        cout << "Highscores";
        cout << endl;
        while(!in.eof())
        {
            in >> name;
            in >> score;

            cout << place;
            cout << ".";
            cout << name;
            cout << " ";
            cout << score;
            cout << endl;

            place++;
        }

        cout << "Type anything and press enter to return to the main menu";
        cout << endl;
        cin >> name;
    }
}

// displays game credits
void displayCredits()
{
    string temp;

    //game credits
    cout << endl;
    cout << "CREDITS";
    cout << endl;
	cout << "This project was created for a Programming Fundamentals 2 (COP3503) assignment";
	cout << endl;
	cout << "Written in C++";
	cout << endl;
	cout << " ";
	cout << endl;
	cout << "Lead Programmers:";
	cout << setw(15);
	cout << "Kareem Hunte";
	cout << endl;
	cout << setw(31);
	cout << "Alex Brandt";
	cout << endl;
	cout << " ";
	cout << endl;
	cout << "Project Managers:";
	cout << setw(20);
	cout << "Prakash Pudhucode";
	cout << endl;
	cout << " ";
	cout << setw(30);
	cout << "Stanley Tan";
	cout << endl;
	cout << " ";
	cout << endl;
	cout << "Testers:";
	cout << setw(24);
	cout << "Pryana Lewis";
	cout << endl;
	cout << setw(34);
	cout << "Arthur Johnson";
	cout << endl;
	cout << " ";
	cout << endl;
	cout << "Creative Director:";
	cout << setw(16);
	cout << "Arthur Johnson";
	cout << endl;
	cout << " ";
	cout << endl;
	cout << "Level Designers: ";
	cout << setw(20);
	cout << "Prakash Pudhucode";
	cout << endl;
	cout << setw(34);
	cout << "Arthur Johnson";
	cout << endl;
	cout << " ";
	cout << endl;
	cout << "Programmers:";
	cout << setw(20);
	cout << "Pryana Lewis";
	cout << endl;
	cout << setw(37);
	cout << "Prakash Pudhucode";
	cout << endl;
	cout << setw(31);
	cout << "Stanley Tan";
	cout << endl;
	cout << setw(31);
	cout << "Alex Brandt";
	cout << endl;
	cout << setw(34);
	cout << "Arthur Johnson";
	cout << endl;
	cout << setw(32);
	cout << "Kareem Hunte";
	cout << endl;
	cout << " ";
	cout << endl;

    cout << "Type anything and press enter to return to the main menu";
    cout << endl;
    cin >> temp;
}

// stops the main game loops from running
bool Quit()
{
    return false;
}

// main method for running the game
int main()
{
    user player;
	string choice;
	bool keepRunning = true;
	cout << "Welcome to our Text Adventure Game!";

	// game loop that start with the main menu
	do{
        StartMenu();
        cin >> choice;
        //Start Game!
        if(choice.compare("1") == 0)
        {
            StartGame(player);
        }
        //Display game information and tutorial
        else if(choice.compare("2") == 0)
        {
            displayTutorial();
        }
        //Open game settings
        else if(choice.compare("3") == 0)
        {
            player = openSettings(player);
        }
        //Displays the highscores from previous players
        else if(choice.compare("4") == 0)
        {
            viewHighscores();
        }
        //Display credits for the game
        else if(choice.compare("5") == 0)
        {
            displayCredits();
        }
        //Quit Game
        else if(choice.compare("6") == 0)
        {
            keepRunning = Quit();
        }
        //Display
        else
        {
            cout << "Error: You entered an incorrect option!";
            cout << endl;
        }
	}while(keepRunning);
	return 0;
}
