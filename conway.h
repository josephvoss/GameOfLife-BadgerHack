//Cell class
//Contains the cell's location and method to find neighboors

struct xyCoords
{
	int x;
	int y;
};

class Cell
{
	public:
		Cell(int x, int y);
		int getX(void);
		int getY(void);
		bool getLive(void);
		void setLocation(int x, int y);
		void findNeighboors(void);
		void calcLiveNeighboors(Cell* totalCells, int length);
		//void calcLiveNeighboors(std::vector<std::vector<Cell>> &cellMatrix);
		void calcNextState(void);
		void nextState(void);

	private:
		xyCoords myLocation;
		xyCoords neighboors[3][3]; //contains location of neighboors
		int liveNeighboors;
		bool liveNow;
		bool liveNext;
};

