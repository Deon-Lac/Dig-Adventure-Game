#include "digAdventureObjects.h"
using namespace std;

/*************************************
 * entity function definitions
*************************************/
//char ctor
entity::entity(char s)
{
    //initialized shape as char
    shape = s;
}

//initialize display_messages
bool entity::display_messages = true;

//GetShape
char entity::getShape() const
{
    //returns shape
    return shape;
}

entity::~entity(){}

//destroy
unsigned int entity::destroy() const
{
    //prints NOTH_MS_DTSY
    cout << NOTH_MSG_DTSY<< endl;

    //returns NOTHING
    return NOTHING;
}
/*************************************
 * miner function definitions
*************************************/
//ctor
miner::miner() : entity('M')
{
    spike_armor = 0;
    point_total = 0;
    is_alive = true;
    height = 1;
    width = 1;
}

//ctor inlining to entity
miner::miner(unsigned int h, unsigned int w) : entity('M')
{
    //initializes the variables
    spike_armor = 0;
    point_total = 0;
    is_alive = true;
    height = h;
    width = w;
}

//miner dtor
miner::~miner()
{
    //checks display_messages to see if it should print
    if (entity::display_messages)
    {
        //prints if true
        cout << MINR_MSG_DTOR << endl;
        //sets display_messages to false
        entity::display_messages = false;
    }
}

//destroy
unsigned int miner::destroy()
{
    //prints message
    cout << MINR_MSG_DSTY << endl;

    //checks armor
    if (spike_armor > 0)
    {
        //subtracts 1 from armor if available
        spike_armor--;
    }
    else
    {
        //sets alive to false since no armor
        is_alive = false;
    }

    //returns miner
    return MINER;
}

//givePoints
void miner::givePoints(int p)
{
    //adds points to points_total
    point_total+=p;
}

//getPoints
int miner::getPoints() const
{
    //returns total points
    return point_total;
}

//armorUp
void miner::armorUp()
{
    //adds 1 to spike armor
    spike_armor+=1;
}

//isStillAlive
bool miner::isStillAlive() const
{
    //returns is alive
    return is_alive;
}

//updateLocation
void miner::updateLocation(unsigned int nh, unsigned int nw)
{
    //updates height and width
    height = nh;
    width = nw;
}

//getHeight
unsigned int miner::getHeight() const
{
    //returns height
    return height;
}

//getwidth
unsigned int miner::getWidth() const
{
    //returns width
    return width;
}

//getArmor
unsigned int miner::getArmor() const
{
    //returns armor
    return spike_armor;
}

/*************************************
 * empty_space function definitions
*************************************/
//inlines entity
empty_space::empty_space() : entity(' ')
{
}
/*************************************
 * hardened_wall function definitions
*************************************/
//ctor
hardened_wall::hardened_wall() : entity('#')
{
}

//destroy
unsigned int hardened_wall::destroy() const
{
    //prints message
    cout << WALL_MSG_DTSY << endl;
    //returns WALL
    return WALL;
}
/*************************************
 * rock function definitions
*************************************/
//ctor
rock::rock() : entity('0')
{
}

//dtor
rock::~rock()
{
    //checks if true
    if (entity::display_messages)
    {
        cout << ROCK_MSG_DTOR << endl;
    }
}

//destroy
unsigned int rock::destroy() const
{
    //prints message
    cout << ROCK_MSG_DTSY << endl;
    //returns rock
    return ROCK;
}
/*************************************
 * carnivorous_silverfish function definitions
*************************************/
//ctor
carnivorous_silverfish::carnivorous_silverfish() : entity('0')
{
}

//dtor
carnivorous_silverfish::~carnivorous_silverfish()
{
    //checks if true
    if (entity::display_messages)
    {
        cout << FISH_MSG_DTOR << endl;
    }
}

//destroy
unsigned int carnivorous_silverfish::destroy() const
{
    //prints message
    cout << FISH_MSG_DTSY << endl;
    //returns carnivorous_silverfish
    return SILVERFISH;
}
/*************************************
 * spike_armor function definitions
*************************************/
//ctor
spike_armor::spike_armor() : entity('^')
{
}

//dtor
spike_armor::~spike_armor()
{
    //checks if true
    if (entity::display_messages)
    {
        cout << ARMR_MSG_DTOR << endl;
    }
}

//destroy
unsigned int spike_armor::destroy() const
{
    //prints message
    cout << ARMR_MSG_DTSY << endl;
    //returns spike_armor
    return ARMOR;
}
/*************************************
 * hidden_treasure function definitions
*************************************/
//ctor
hidden_treasure::hidden_treasure() : entity('$')
{
}

//dtor
hidden_treasure::~hidden_treasure()
{
    //checks if true
    if (entity::display_messages)
    {
        cout << TRSR_MSG_DTOR << endl;
    }
}

//destroy
unsigned int hidden_treasure::destroy() const
{
    //prints message
    cout << TRSR_MSG_DTSY << endl;
    //returns hidden_treasure
    return TREASURE;
}
/*************************************
 * mine_exit function definitions
*************************************/
//ctor
mine_exit::mine_exit() : entity('E')
{
}

//dtor
mine_exit::~mine_exit()
{
    //checks if true
    if (entity::display_messages)
    {
        cout << EXIT_MSG_DTOR << endl;
        entity::display_messages = false;

    }
}

//destroy
unsigned int mine_exit::destroy() const
{
    //prints message
    cout << EXIT_MSG_DTSY << endl;
    //returns mine_exit
    return EXIT;
}
