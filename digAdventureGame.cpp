#include "digAdventureGame.h"

using namespace std;

void dig_adventure_game::allocateGrid() {
	//checks to see if grid has memory allready
	if (game_grid != nullptr)
	{
		//calls deallocate if something was found
		deallocateGrid();
	}
	else
	{
		//allocates dimensions
		game_grid = new entity**[game_height];
		//puts nullptrs into array
		for (int i = 0; i < game_height; i++)
		{
			//initializes all pointers to nullptrs
			game_grid[i] = new entity*[game_width];
			for (int j = 0; j < game_width; j++)
			{
				game_grid[i][j] = nullptr;
			}
		}	
	}
}

void dig_adventure_game::deallocateGrid() {
	//Checks if grid is empty
	if (game_grid == nullptr)
	{
		return;
	}
	else
	{
		//deallocates
		for (int i = 0; i < game_height; i++)
		{
			for (int j = 0; j < game_width; j++)
			{
				//deletes small objects
				delete game_grid[i][j];
			}
			//deletes array
			delete[] game_grid[i];
		}
		//deletes whole array
		delete[] game_grid;
		game_grid = nullptr;
	}
	
}

entity *dig_adventure_game::allocateEntity(unsigned int i) {
	
	//if statements for all diff params
	//Wall
	if (i == WALL)
	{
		return(new hardened_wall());
	}
	//EXIT
	if (i == EXIT)
	{
		return(new mine_exit());
	}
	//NOTHING
	if (i == NOTHING)
	{
		return(new empty_space());
	}
	//ROCK
	if (i == ROCK)
	{
		return(new rock());
	}
	//SILVERFISH
	if (i == SILVERFISH)
	{
		return(new carnivorous_silverfish());
	}
	//ARMOR
	if (i == ARMOR)
	{
		return(new spike_armor());
	}
	//TREASURE
	if (i == TREASURE)
	{
		return(new hidden_treasure());
	}
	//MINER
	if (i == MINER)
	{
		return(new miner());
	}

	//return nullptr if program fails
	return nullptr;
}

void dig_adventure_game::moveMiner(unsigned int nh, unsigned int nw) {
	
	//deletes object at new location
	//game_grid[nh][nw]->destroy();
	delete game_grid[nh][nw];

	//puts player in new location
	game_grid[nh][nw] = player;

	//puts empty space into players old location
	game_grid[player->getHeight()][player->getWidth()] = new empty_space;

	//updates miners height and width
	player->updateLocation(nh,nw);
	//moveMiner(nh,nw);
	
}

unsigned int dig_adventure_game::playerMove() {
	if (player == nullptr) {
		return GAME_ERROR;
	}
	string selection;
	cout << "Where will the miner go?" << endl;
	cout << "(l)eft, (r)ight, (u)p, (d)own :" << endl;
	cin >> selection;
	while (true) {
		if (selection.length() >= 1) {
			if (selection[0] == 'l' || selection[0] == 'r' || selection[0] == 'u' || selection[0] == 'd') {
				break;
			}
		}
		cout << "Invalid entry!" << endl;
		cout << "(l)eft, (r)ight, (u)p, (d)own :" << endl;
		cin >> selection;
	}
	char direction = selection[0];

	int newHeight = 0;
	int newWidth = 0;
	//switch statement for direction
	switch (direction)
	{
	//left
	case 'l':
		newHeight = player->getHeight();
		newWidth = player->getWidth()-1;
		break;
	//right
	case 'r':
		newHeight = player->getHeight();
		newWidth = player->getWidth()+1;
		break;
	//up
	case 'u':
		newHeight = player->getHeight()-1;
		newWidth = player->getWidth();
		break;
	//up
	case 'd':
		newHeight = player->getHeight()+1;
		newWidth = player->getWidth();
		break;
	
	//default just in case of an error
	default:
		return GAME_ERROR;
	}

	//calls destory on the item the miner is moving to
	unsigned int result = game_grid[newHeight][newWidth]->destroy();
	//nothing
	if (result == NOTHING) //GetShape maybe??
	{
		moveMiner(newHeight,newWidth);
		return GAME_CONTINUE;
	}
	//rock
	else if (result == ROCK)
	{
		//moves miner
		moveMiner(newHeight,newWidth);
		//gives one point
		player->givePoints(1);
		//returns game continue
		return GAME_CONTINUE;
	}
	//silverfish
	else if (result == SILVERFISH)
	{
		//tries to call destroy
		player->destroy();
		//gives -5 points
		player->givePoints(-5);
		//checks if player is alive
		if (player->isStillAlive())
		{
			//moves miner
			moveMiner(newHeight,newWidth);
			//returns game continue
			return GAME_CONTINUE;
		}
		//updates to nullptr if dead
		else
		{
			int height = player->getHeight();
			int width = player->getWidth();
			delete player;
			game_grid[height][width] = nullptr;
			player = nullptr;
			return GAME_EXIT_LOSE;
		}	
	}
	//armor
	else if (result == ARMOR)
	{
		//moves miner
		moveMiner(newHeight,newWidth);
		//calls armor up
		player->armorUp();
		//returns game continue
		return GAME_CONTINUE;
	}
	//treasure
	else if (result == TREASURE)
	{
		//gives 3 points
		player->givePoints(3);
		//moves miner
		moveMiner(newHeight,newWidth);
		//returns game continue
		return GAME_CONTINUE;
	}
	//exit
	else if (result == EXIT)
	{
		//moves miner
		moveMiner(newHeight,newWidth);
		//returns game win
		return GAME_EXIT_WIN;
	}
	//wall
	else if (result == WALL)
	{
		//returns game continue
		return GAME_CONTINUE;
	}

	return GAME_ERROR; // You may want to replace. 
}

void dig_adventure_game::populateGrid() {
	if(game_width < 2 || game_height < 2){
		return;
	}
	// Place the miner
	player = new miner(1, 1);
	game_grid[1][1] = player;
	/* Place the exit */
	game_grid[game_height - 2][game_width - 1] = allocateEntity(EXIT);
	/* Put up the walls */
	for (unsigned int h = 0; h < game_height; h++) {
		// Vertical Walls
		if(game_grid[h][0] == nullptr){
			game_grid[h][0] = allocateEntity(WALL);
		}
		if (h != (game_height - 2) && game_grid[h][game_width - 1] == nullptr) {
			game_grid[h][game_width - 1] = allocateEntity(WALL);
		}
	}
	for (unsigned int w = 0; w < game_width; w++) {
		// Horizontal Walls
		if(game_grid[0][w] == nullptr){
			game_grid[0][w] = allocateEntity(WALL);
		}
		if(game_grid[game_height - 1][w] == nullptr){
			game_grid[game_height - 1][w] = allocateEntity(WALL);
		}
	}
	/* Place the events */
	unsigned int sflh, sflw, htlh, htlw, salh, salw;
	unsigned int quadrant = 4;
	// Quadrant height
	for (unsigned int qh = 0; qh < quadrant / 2; qh++) {

		unsigned int startH, startW;
		startH = (qh * (game_height / 2));
		// Quadrant width
		for (unsigned int qw = 0; qw < quadrant / 2; qw++) {

			startW = (qw * (game_width / 2));
			// Add silverfish
			for (unsigned int d = 0; d < difficulty; d++) {
				
				do {
					sflh = startH + (rand() % (game_height / 2));
					sflw = startW + (rand() % (game_width / 2));
				} while (game_grid[sflh][sflw] != nullptr);
				game_grid[sflh][sflw] = allocateEntity(SILVERFISH);
				
			}
			// Add treasure
			do {
				htlh = startH + (rand() % (game_height / 2));
				htlw = startW + (rand() % (game_width / 2));
			} while (game_grid[htlh][htlw] != nullptr);
			game_grid[htlh][htlw] = allocateEntity(TREASURE);
			// add armor
			do {
				salh = startH + (rand() % (game_height / 2));
				salw = startW + (rand() % (game_width / 2));
			} while (game_grid[salh][salw] != nullptr);
			game_grid[salh][salw] = allocateEntity(ARMOR);
		}
	}
	/* Fill the rest with rock */
	for (unsigned int i = 0; i < game_height; i++) {
		for (unsigned int j = 0; j < game_width; j++) {
			if (game_grid[i][j] == nullptr) {
				game_grid[i][j] = allocateEntity(ROCK);
			}
		}
	}
}

dig_adventure_game::dig_adventure_game(unsigned int h, unsigned int w, unsigned int d) : game_height(h), game_width(w), difficulty(d){
	// Sanatize parameters
	if (w < 10) {
		game_width = 10;
	}
	if (h < 10) {
		game_height = 10;
	}

	if (d == 0) {
		d = 1;
	}
	else {
		unsigned int hd = d, wd = d;
		if (d > (((game_height - 2) / 2) - 1)) {
			hd = (((game_height - 2) / 2) - 1);
		}
		if (d > (((game_width - 2) / 2) - 1)) {
			wd = (((game_width - 2) / 2) - 1);
		}
		d = (wd < hd) ? wd : hd;
	}
	difficulty = d;
	// Allocate the grid
	allocateGrid();
	// Populate with objects
	populateGrid();
}

dig_adventure_game::~dig_adventure_game() {
	// Check to see if player still exists
	if (player != nullptr) {
		game_grid[player->getHeight()][player->getWidth()] = nullptr;
		delete player;
	}
	// Deallocate the grid
	deallocateGrid();	
}

void dig_adventure_game::playGame() {
	while (true) {
		// Print the game board
		printGrid();
		// Let the player move
		unsigned int rslt = playerMove();
		// If error
		if (rslt == GAME_ERROR) {
			cout << "An Error Ocurred. Please report this incident to yourself." << endl;
			return;
		}
		// If player loses or wins
		if (rslt == GAME_EXIT_LOSE || rslt == GAME_EXIT_WIN) {
			return;
		}
	}
}

void dig_adventure_game::printGrid() const {
	// Use a string so output happens all at once. 
	string output("");
	output += "\n";
	output += "------------------\n";
	output += string("| Current Score: |  ") + to_string(player->getPoints()) + string("\n");
	output += string("------------------\n");
	output += string(" * Armor Bonus: *  ") + to_string(player->getArmor()) + string("\n\n");
	for (unsigned int i = 0; i < game_height; i++) {
		for (unsigned int j = 0; j < game_width; j++) {
			if (game_grid[i][j] == nullptr) {
				// In case your grid contains nullptrs, you will question marks
				output += string("|?");
			}
			else {
				output += '|';
				output += game_grid[i][j]->getShape();
			}
		}
		output += "|\n";
	}
	output += '\n';
	cout << output;
}

// Copy ctor is here to prevent memory problems. 
// Does not make an identical copy
dig_adventure_game::dig_adventure_game(const dig_adventure_game &copy) {
	game_grid = nullptr; 
	player = nullptr;
	game_width = 0;
	game_height = 0;
	(*this) = copy;
}

// Operator= is here to prevent memory problems. 
// Does not make an identical copy
void dig_adventure_game::operator=(const dig_adventure_game &copy) {
	cout << "WARNING: You have called the Copy Ctor or Operator= for game object." << endl;
	cout << "A new game will be made instead because Mr.P was too lazy to do a deep copy." << endl;
	cout << "If you are a student who is still completing the assignment, you should not be seeing this message." << endl;
	deallocateGrid();
	if (player != nullptr) {
		delete player;
	}
	game_width = copy.game_width;
	game_height = copy.game_height;
	difficulty = copy.difficulty;
	allocateGrid();
	populateGrid();
}

