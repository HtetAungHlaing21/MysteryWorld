//Assessment-2 Mystery World

//Header Files
#include <iostream> //For basic input output stream
#include <iomanip> //For pausing, clearing the console
#include <cstdlib> //For random
#include <ctime> //For time
using namespace std;

//Classes Starts Here!
class Room  //Room Class
{
public:
    char entity [10][10];
    void add() //This method is to add the entities into two-dimensional array
    {
        for (int row=0; row<10; ++row)
        {
            for (int column=0; column<10; ++column)
            {
                entity[row][column] = '.'; //Start initialize the dots (meaning - vacant), later will put the real symbols
            }
        }
    }

    void display() //This method is to display the entities on the grid
    {
        cout<<"\nX 0 1 2 3 4 5 6 7 8 9"<<endl; //Header Line
        for (int row=0; row<10; ++row)
        {
            cout<<row<<" ";
            for (int column=0; column<10; column++)
            {
                cout<<entity[row][column]<<" "; //Displaying the entities on the grid
            }
            cout<<endl;
        }
    }
};

class Main //Main class
{
public:
    void showMenu () //The method to display the menu of the game!
    {
        cout<<"\nEnter a number from the options."<<endl;
        cout<<"1. Display Room"<<endl;
        cout<<"2. Move all the animated entities."<<endl;
        cout<<"3. Display the entity state by coordinates"<<endl;
        cout<<"4. Reset the room."<<endl;
        cout<<"5. Finish"<<endl;
    }

    int askXCoord () //This method is to ask the x coordinate to the user. (To display the properties of the location)
    {
        int xCoord;  //To store the x coordinate of the entity
        cout<<"Enter x-coordinate from 0 to 9: ";
        while (true) //This loop works if the user enters invalid x coordinate (less than 0 and greater than 9)
        {
            cin>>xCoord;
            if (xCoord<0 ||xCoord>9)
            {
                cout<<"Invalid Input! Type again: ";
            }
            else
            {
                break;
            }
        }
        return xCoord;
    }

    int askYCoord () //This method is to ask the y coordinate to the user. (To display the properties of the location)
    {
        int yCoord; //To store the y coordinate of the entity
        cout<<"Enter y-coordinate from 0 to 9: ";
        while (true) //This loop works if the user enters invalid x coordinate (less than 0 and greater than 9)
        {
            cin>>yCoord;
            if (yCoord<0 || yCoord>9)
            {
                cout<<"Invalid Input! Type again: ";
            }
            else
            {
                break;
            }
        }
        return yCoord;
    }

};

class Entity //This class the parent Class For all entities (both inanimate and animate)
{
public:
    int location[2]; //The location of the entity on the grid

    void plot(Room &r) //To determine the x and y location of the entity
    {
        do
        {
            location[0] = rand()%10; //choose the x location randomly from 0 to 9
            location[1] = rand()%10; //choose the y location randomly from 0 to 9
        }
        while (r.entity[location[0]][location[1]] != '.'); //If the [x][y] location is not '.' (meaning - not vacant), the location will be chosen again.
    }

    void place (Room &r, char symbol) //To place the entity on the grid (2 Parameters - room object and the symbol to place)
    {
        plot(r); //Above function to determine the x and y location of the entity
        r.entity[location[0]][location[1]] = symbol; //The symbol will be assigned in that location
    }
};

class AnimateEntity //Virtual Parent Class For only animate entities
{
public:
    int health; //Health of animate entities
    virtual void movement(Room &r) = 0; //Virtual Function for movement
    void setHealth (int h ) //This method is to set the health of the an animate entity
    {
        health = h;
    }
    void moveOneStepRandom(Room &r, int location[]) //This method is to move one step in random direction (For child classes to use)
    {
        bool hasMoved=false; //First, we will initialize the flag as false.
        do
        {
            int direction = rand()%4; //A random number 0 to 3 will be chosen.
            //Based on the random number, the move direction will be chosen.
            //In every case, there are two conditions to be met. (The place which it is chosen must be vacant and it should not be on the edge of the room)
            //If these conditions are met, the location changes and the flag will change to true.
            //If one of these conditions is not met, the location will still be the same and the flag will still be false.
            //The loop will run as long as the flag is false.

            switch (direction)
            {
            case 0: //If the number is 0, left direction will be chosen and the entity will move one step left.
                if (r.entity[location[0]][location[1]-1] == '.' && location[1]!=0) //To move left, the target position should be vacant and y coordinate should not be 0.
                {
                    location[1]-=1; //The y coordinate is reduced by one to move one step left.
                    hasMoved=true;
                }
                break;
            case 1: //If the number is 1, right direction will be chosen and the entity will move one step right.
                if (r.entity[location[0]][location[1]+1] == '.' && location[1]!=9) //To move right, the target position should be vacant and y coordinate should not be 9.
                {
                    location[1]+=1; //The x coordinate is added by one to move one step right.
                    hasMoved=true;
                }
                break;
            case 2: //If the number is 2, down direction will be chosen and the entity will move one step down.
                if (r.entity[location[0]+1][location[1]] == '.' && location[0]!=9)//To move down, the target position should be vacant and x coordinate should not be 9.
                {
                    location[0]+=1; //The x coordinate is added by one to move one step down.
                    hasMoved=true;
                }
                break;
            case 3: //If the number is 3, up direction will be chosen and the entity will move one step up.
                if (r.entity[location[0]-1][location[1]] == '.' && location[0]!=0)//To move up, the target position should be vacant and x coordinate should not be 0.
                {
                    location[0]-=1; //The x coordinate is reduced by one to move one step up.
                    hasMoved=true;
                }
                break;
            default:
                cout<<"Default Move"<<endl;
                break;
            }
        }
        while (hasMoved != true); //This loop will run as long as the flag does not change to true.
    }
};

//Two inanimate entities (Stone and Hole)

class Stone : public Entity //Stone class inherited from entity
{
    //No attributes and methods for stone class (Just inherited from entity parent class)
};

class Hole : public Entity //Hole class inherited from entity
{
public:
    int depth; //The depth of the hole.
    void setDepth (int dep)  //This method is to set the depth of a hole
    {
        depth = dep;
    }
};

//Three animate entities (Human, dragon and monster)

class Human : public Entity, public AnimateEntity //Human class inherited from two classes (Entity and Animate Entity)
{
public:
    string name; //The name of the human
    Human (string humanName) //This is a constructor to initialize the name of the human
    {
        name = humanName;
    }
    void movement(Room &r) //This method is to perform the movement of a human
    {
        r.entity[location[0]][location[1]] = '.'; //First, the initial places for humans should be made vacant. (Meaning - put '.' again.)

        //According to the rules, it will move one step right as long as the position is vacant and it is not on the right edge of the room
        if (r.entity[location[0]][location[1]+1] == '.' && location[1]!=9)
        {
            location[1]+=1; //The y coordinate is added one to move one step right.
        }
        else //If one of the above two conditions is not met, it will move one step to the random direction
        {
            moveOneStepRandom(r, location);
        }
        r.entity[location[0]][location[1]] = '@'; //If we got the new locations, the symbol of the human is assigned to the new locations.
        health--; //Health is reduced by one.
    }
};

class Dragon : public Entity, public AnimateEntity //Dragon class inherited from two classes (Entity and Animate Entity)
{
public:
    void movement(Room &r) //This method is to perform the movement of a dragon
    {
        r.entity[location[0]][location[1]] = '.'; //First, the initial places for dragons should be made vacant. (Meaning - put '.' again.)
        moveOneStepRandom(r, location); //According to the rules, the dragons will move to one random cell. So, this method is called to move one random step.
        r.entity[location[0]][location[1]] = '#'; //If we got the new locations, the symbol of the dragon is assigned to the new locations.
        health-=rand()%6; //The health is reduced by a random number from 0 to 5 every time it moves.
        if (health <0) //There is no negative health, so, if the health goes beyond 0, it will be 0.
        {
            health = 0;
        }
    }
};

class Monster : public Entity, public AnimateEntity //Monster class inherited from two classes (Entity and Animate Entity)
{
public:
    int strength; //The strength of a monster
    void setStrength (int str) //This method is to set the strength of a monster
    {
        strength = str;
    }
    void movement(Room &r) //This method is to perform the movement of a monster
    {
        r.entity[location[0]][location[1]] = '.'; //First, the initial places for monsters should be made vacant. (Meaning - put '.' again.)
        char left = r.entity[location[0]][location[1]-strength]; //The target place on the left
        char right = r.entity[location[0]][location[1]+strength]; //The target place on the right
        char down = r.entity[location[0]+strength][location[1]]; //The target place Down
        char up = r.entity[location[0]-strength][location[1]]; //The target place Up
        bool hasMoved=false; //The flag is initialized as false.

        if (strength > 0) //The monster cannot move if its strength is 0. So, only if the strength is greater than 0, it will move.
        {
            //According to the rules, the monsters move to a random direction to as many cells as their strength.
            //If one of these directions is vacant, the monster will move to one random direction as its strength.
            //If all of these directions are not vacant and not possible to move, they move to one cell to the random direction as a default move.

            if ((left == '.' && location[1]-strength >=0) || (right == '.' && location[1]+strength <=9) || (down == '.' && location[0] + strength <=9) || (up == '.' && location[0] - strength>=0))
                //It is the condition to test whether one of the target cells are vacant and valid to move
                //If the condition is met, the following loop will be executed. If not met, it will move one step to the random direction
            {
                do
                {
                    int direction = rand()%4; //A random number 0 to 3 will be chosen.
                    //Based on the random number, the move direction will be chosen. They move as much as their strength.
                    //In every case, there are two conditions to be met. (The target place which it is chosen must be vacant and it should be possible to move)
                    //If these conditions are met, the location changes and the flag will change to true.
                    //If one of these conditions is not met, the location will still be the same and the flag will still be false.
                    //The loop will run as long as the flag is false.

                    switch (direction)
                    {
                    case 0:  //If the number is 0, left direction will be chosen and the entity will move left according to its strength.
                        if (left == '.' && location[1]-strength >=0) //To move left, the target position should be vacant and should not exceed 0.
                        {
                            location[1]-=strength; //The y coordinate is reduced to move left.
                            hasMoved=true;
                        }
                        break;
                    case 1:  //If the number is 1, right direction will be chosen and the entity will move right according to its strength.
                        if (right == '.' && location[1]+strength <=9) //To move right, the target position should be vacant and should not exceed 9.
                        {
                            location[1]+=strength; //The y coordinate is added to move right.
                            hasMoved=true;
                        }
                        break;
                    case 2: //If the number is 0, down direction will be chosen and the entity will move down according to its strength.
                        if (down == '.' && location[0] + strength <=9) //To move down, the target position should be vacant and should not exceed 9.
                        {
                            location[0]+=strength; //The x coordinate is added to move down.
                            hasMoved=true;
                        }
                        break;
                    case 3: //If the number is 0, up direction will be chosen and the entity will move up according to its strength.
                        if (up == '.' && location[0] - strength>=0) //To move up, the target position should be vacant and should not exceed 0.
                        {
                            location[0]-=strength; //The x coordinate is reduced to move up.
                            hasMoved=true;
                        }
                        break;
                    default:
                        cout<<"Default Move"<<endl;
                        break;
                    }
                }
                while (hasMoved != true); //This loop will run as long as the flag does not change to true.
            }
            else //If all of the directions are not vacant and not possible to move, it will move one step to the random direction
            {
                moveOneStepRandom(r, location);
            }
        }
        r.entity[location[0]][location[1]] = '*'; //If we got the new locations, the symbol of the dragon is assigned to the new locations.
        health-=strength;  //The health is reduced by its strength every time it moves.
    }
};


int main() //This is the main function to be executed.
{
    int option; //Option 1-5 from the menu
    int holeNum, dragonNum, humanNum, monsterNum; //To classify the entities which have more than one in number
    int coordinate[2]; //Coordinate to search the entity
    char target, ans; //Target to find the entity in the graph, ans to ask the player to continue or not
    string playerName; //The name of the player
    srand (time(0)); //To generate different random numbers.

    //Welcome the player
    cout<<"Welcome to 'Mystery World'!"<<endl;
    cout<<"Enter your name: ";
    getline(cin, playerName);

    //Creating objects for all classes (Entities + Room + Main). The arrays of objects are also created.
    Stone stone1, stone2;
    Stone stones[2]= {stone1, stone2};

    Hole hole1, hole2;
    Hole holes[2] = {hole1, hole2};

    Human human1("Harold"), human2("David"), human3("Clare");
    Human humans[3] = {human1, human2, human3};

    Dragon dragon1, dragon2;
    Dragon dragons[2] = {dragon1, dragon2};

    Monster monster1, monster2, monster3;
    Monster monsters[3] = {monster1, monster2, monster3};

    Room room;
    Main main;

reset:  //This is the place to start running the codes when resetting the game (When the user enters '4')

    //Choosing the random number for the properties of entities & setting it into the entity class
    for (int hole=0; hole<2; ++hole)
    {
        holes[hole].setDepth(rand()%21);    //Depth of the hole from 0 to 20
    }
    for (int human =0; human<3; ++human)
    {
        humans[human].setHealth(100);  //Health of human (100 at the beginning of the game)
    }
    for (int monster=0; monster<3; ++monster)
    {
        monsters[monster].setStrength(rand()%6); //Strength of monster from 0 to 5
        monsters[monster].setHealth(100); //Health of monster (100 at the beginning of the game)
    }
    for (int dragon =0; dragon<2; ++dragon)
    {
        dragons[dragon].setHealth(100); //Health of dragon (100 at the beginning of the game)
    }

    //Plotting the entities

    room.add(); //setting the basic coordinates of the room

    for (int i=0; i<2; ++i)
    {
        stones[i].place(room, 'S'); //For 2 stones
    }
    for (int i=0; i<2; ++i)
    {
        holes[i].place(room, 'O'); //For 2 holes
    }
    for (int i=0; i<3; ++i)
    {
        humans[i].place(room, '@'); //For 3 humans
    }
    for (int i=0; i<2; ++i)
    {
        dragons[i].place(room, '#'); //For 2 dragons
    }
    for (int i=0; i<3; ++i)
    {
        monsters[i].place(room, '*'); //For 3 monsters
    }

    //The game starts functioning here.
    room.display(); //Display the grid
    main.showMenu(); //Show the menu

    do
    {
        cout<<"\nType your option number: ";  //Ask the option and perform according to the player's choice.
        cin>>option;

        //The actions will depend on the option from the user's input
        switch (option)
        {
        case 1: //To display the room
            room.display();
            break;

        case 2: //To move the animate entities
            for (int i=0; i<3; ++i)
            {
                if (humans[i].health>0)
                {
                    humans[i].movement(room);
                }
            }
            for (int i=0; i<2; ++i)
            {
                if (dragons[i].health>0)
                {
                    dragons[i].movement(room);
                }
            }
            for (int i=0; i<3; ++i)
            {
                if (monsters[i].health>=monsters[i].strength)
                {
                    monsters[i].movement(room);
                }
            }
            room.display(); //After moving, displaying the room again
            break;

        case 3: //To display the properties of the entity
            do
            {
                coordinate[0] = main.askXCoord(); //Ask x and y coordinates
                coordinate[1] = main.askYCoord();
                target = room.entity[coordinate[0]][coordinate[1]]; //Find the symbol of the entity
                cout<<"\nEntity Properties:"<<endl;

                switch (target) //The target symbol determines the output. But we have to differentiate between different objects of the same class
                {
                case 'S': //Stone
                    cout<<"Type: Stone"<<endl; //Type
                    break;

                case 'O': //Hole
                    for (int i=0; i<2; ++i) //Checking hole 1 or hole 2
                    {
                        if (coordinate[0] == holes[i].location[0] && coordinate[1] == holes[i].location[1])
                        {
                            holeNum = i;
                        }
                    }
                    cout<<"Type: Hole"<<endl; //Type
                    cout<<"Depth: "<<holes[holeNum].depth<<" m"<<endl; //Property - depth
                    break;

                case '#': //Dragon
                    for (int i=0; i<2; ++i) //Checking dragon 1 or 2
                    {
                        if (coordinate[0] == dragons[i].location[0] && coordinate[1] == dragons[i].location[1])
                        {
                            dragonNum = i;
                        }
                    }
                    cout<<"Type: Dragon"<<endl; //Type
                    cout<<"Health: "<<dragons[dragonNum].health<<endl; //Property - health
                    break;

                case '@': //Human
                    for (int i=0; i<3; ++i) //Checking human 1 or 2 or 3
                    {
                        if (coordinate[0] == humans[i].location[0] && coordinate[1] == humans[i].location[1])
                        {
                            humanNum = i;
                        }
                    }
                    cout<<"Type: Human"<<endl; //Type
                    cout<<"Name: "<<humans[humanNum].name<<endl; //Properties - name and health
                    cout<<"Health: "<<humans[humanNum].health<<endl;
                    break;

                case '*': //Monster
                    int monsterID;
                    for (int i=0; i<3; ++i) //Checking human 1 or 2 or 3
                    {
                        if (coordinate[0] == monsters[i].location[0] && coordinate[1] == monsters[i].location[1])
                        {
                            monsterNum = i;
                            monsterID = i;
                        }
                    }
                    cout<<"Type: Monster"<<endl; //Type
                    cout<<"Strength: "<<monsters[monsterNum].strength<<endl; //Properties - strength and health
                    cout<<"Health: "<<monsters[monsterNum].health<<endl;
                    break;

                case '.': //Vacant Location
                    cout<<"There is no entity in this coordinate."<<endl;
                    break;

                default: //Default is an error
                    cout<<"Error!"<<endl;
                    break;
                }
                cout<<"\nDo you want to display more attributes? If yes, type 'y', If no, type 'n'. Your answer: ";
                cin>>ans;
            }
            while (ans == 'y'); //It will loop as long as the user's answer is 'y'.
            break;

        case 4: //To reset the game
            cout<<"Resetting the game. . ."<<endl<<endl;
            goto reset; //Start to run the codes from the reset section.
            break;

        case 5: //Stop the game
            cout<<"Thanks for playing 'Mystery World!' Have a nice day, "<<playerName<<endl;
            break;

        default: //Default Case
            cout<<"Invalid Input! Choose from 1 to 5."<<endl;
            cin.clear();
            cin.ignore();
            break;
        }

    }
    while (option != 5); //The game will loop and run until the user types '5' to terminate.
    return 0;
}
