// Position.h - Joe Bost - 4/24/18
#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <vector>
using namespace std;

class Position
{
  public:
    static int created;
    static int destroyed;
    Position(vector<int> init);
    Position(const Position& pos);
    ~Position();
    bool isDone();
    Position* afterMove(int hole);
    friend ostream& operator<<(ostream& os, const Position &right);
    bool operator==(const Position& right) const;
    int getHole(); //ADDED
    vector<int> getPositions() const; //ADDED
    Position* getPrevious(); //ADDED
    void setPrevious(const Position& pos, int hole); //ADDED
  private:
    vector<int> positions;
    Position *previous = nullptr;
    int hole;
};
#endif
