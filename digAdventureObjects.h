#include <iostream>
using namespace std;

#define NOTHING     0
#define ROCK        1
#define SILVERFISH  2
#define ARMOR       3
#define TREASURE    4
#define WALL        5
#define EXIT        6 
#define MINER       7

/* empty_space and entity messages */
#define NOTH_MSG_DTSY "There is nothing here to dig..."
/* miner messages */
#define MINR_MSG_DSTY "The miner is attacked by Carnivorous Silverfish!"
#define MINR_MSG_DTOR "AAAAAAAGHHHHHHHHH!"
/* hardened_wall messages */
#define WALL_MSG_DTSY "The miner attempts to dig through the hardened wall. It cannot be destroyed."
/* rock messages */
#define ROCK_MSG_DTSY "The miner digs through some ordinary rock."
#define ROCK_MSG_DTOR "*crumbles*"
/* carnivorous_silverfish messages */
#define FISH_MSG_DTSY "The miner digs into rock invested with Carnivorous Silverfish!"
#define FISH_MSG_DTOR "*the silverfish hiss as they perish to the miner's spike armor*"
/* armor messages */
#define ARMR_MSG_DTSY "The miner digs up a component of the Spike Armor set!"
#define ARMR_MSG_DTOR "*the miner equips the spike armor*"
/* hidden_treasure messages */
#define TRSR_MSG_DTSY "The miner digs up some Hidden Treasure!"
#define TRSR_MSG_DTOR "*the miner stuffs shiny gems into their bag*"
/* exit messages */
#define EXIT_MSG_DTSY "The miner digs through the Exit!"
#define EXIT_MSG_DTOR "Congrats! You WIN!"

/*************************************
 * entity
*************************************/
class entity
{
        private:
		//shape
		char shape;

    protected:
        //display_message initialized as true
        static bool display_messages;

        //ctors
        entity(char);

	public:
        //Getshape
        char getShape() const;

        //destroy function
        virtual unsigned int destroy() const;

        //pure virtual dtor
        virtual ~entity() = 0;
};
/*************************************
 * miner
*************************************/
class miner : public entity
{
	private:
        //spike_armor
        unsigned int spike_armor = 0;

        //point_total
        int point_total = 0;

        //is_alive
        bool is_alive = true;

        //height
        unsigned int height = 1;

        //Width
        unsigned int width = 1;

	public:

        //default ctor
        miner();
                

        //ctor inlining to entity
        miner(unsigned int h, unsigned int w);

        //dtor
        ~miner();

        //Destroy
        unsigned int destroy();
        
        //givePoints
        void givePoints(int);

        //getPoints
        int getPoints() const;

        //armorUp
        void armorUp();

        //isStillAlive
        bool isStillAlive() const;

        //updateLocation
        void updateLocation(unsigned int, unsigned int);

        //getwidth
        unsigned int getWidth() const;

        //getHeight
        unsigned int getHeight() const;

        //getArmor
        unsigned int getArmor() const;

};
/*************************************
 * empty_space
*************************************/
class empty_space : public entity
{
	public:
                //ctor
                empty_space();
};

/*************************************
 * hardened_wall
*************************************/
class hardened_wall : public entity
{
	public:
                //ctor
                hardened_wall();
                unsigned int destroy() const;
};
/*************************************
 * rock
*************************************/
class rock : public entity
{
	public:
                //ctor
                rock();
                //dtor
                ~rock();
                //destroy
                unsigned int destroy() const;
};
/*************************************
 * carnivorous_silverfish
*************************************/
class carnivorous_silverfish : public entity
{
	public:
                //ctor
                carnivorous_silverfish();
                //dtor
                ~carnivorous_silverfish();
                //destroy
                unsigned int destroy() const;
};
/*************************************
 * spike_armor
*************************************/
class spike_armor : public entity
{
	public:
                //ctor
                spike_armor();
                //dtor
                ~spike_armor();
                //destroy
                unsigned int destroy() const;
};
/*************************************
 * hidden_treasure
*************************************/
class hidden_treasure : public entity
{
	public:
                //ctor
                hidden_treasure();
                //dtor
                ~hidden_treasure();
                //destroy
                unsigned int destroy() const;
};
/*************************************
 * mine_exit
*************************************/
class mine_exit : public entity
{
	public:
                //ctor
                mine_exit();
                //dtor
                ~mine_exit();
                //destroy
                unsigned int destroy() const;
};
