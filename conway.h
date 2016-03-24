//Cell class
//Contains the cell's location and method to find neighboors

/*
NOTATION NOTE
(i,j) 
 j j j
i
i
i
*/

struct xyCoords
{
	int x;
	int y;
};

class CellArray; //forward declaration

class Cell
{
	public:
		Cell(int x, int y);
		int getX(void);
		int getY(void);
		bool getLive(void);
		void setLive(bool live);
		void findNeighboors(void);
		void calcLiveNeighboors(CellArray& totalCells, int lengthx, int lengthy);
		void calcNextState(void);
		void nextState(void);

	private:
		xyCoords myLocation;
		xyCoords neighboors[3][3]; //contains location of neighboors
		int liveNeighboors;
		bool liveNow;
		bool liveNext;
};

class CellArray
{
	public:
		CellArray(int x, int y);
		~CellArray();
		Cell& operator()(int x, int y);
		void iterate(void);
	
	private:
		Cell* rootLocation;
		int lengthx;
		int lengthy;
};
