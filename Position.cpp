// Position.cpp - Joe Bost - 4/24/18
#include "Position.h"
using namespace std;

int Position::created = 0; //Number of created objects
int Position::destroyed = 0; //Number of destroyed objects

Position::Position(vector<int> vec) : positions(vec)
{
  created++;
}

Position::Position(const Position& other)
: positions(other.positions), hole(other.hole)
{
  if (other.previous != nullptr)
    previous = new Position(*other.previous);
  created++;
}

Position::~Position()
{
    delete previous;
    destroyed++;
}

bool Position::isDone()
{
  for (int i = 0; i < 5; i++) //Checks each hole
  {
    if (positions.at(i) != 0) //Checks if the hole isn't empty
    {
      return false; //The game is not complete
    }
  }
  return true; //Every position on the board is = 0, so the game is complete
}

Position* Position::afterMove(int hole)
{
  if (positions.at(hole) == 0) //If there is nothing in the hole
  {
    return nullptr;
  }
  else
  {
    Position *newBoard = new Position(positions);
    newBoard->positions[hole] = 0; //Picks up the pieces from current hole
    int currentHole = hole+1;

    for(int i = 0; i < positions.at(hole); i++) //While there are extra pieces
    {
      if(currentHole == 5) //Checks if hole is the bank
      {
        currentHole = 0;
      }
      else //Adds one piece to the hole and advances to the next hole
      {
        newBoard->positions[currentHole]++;
        currentHole++;
      }
    }
    return newBoard; //Returns the new board after the move is complete
  }
}

ostream& operator<<(ostream& out, const Position& right)
{
  out << "[";
  for (int i = 0; i < 5; i++)
  {
    out << right.positions.at(i);
    if (i != 4)
      out << ".";
  }
  out << "]";

  return out;
}

bool Position::operator==(const Position& right) const
{
  for (int i = 0; i < 5; i++)
  {
    if (positions.at(i) != right.positions.at(i))
    {
      return false;
    }
  }
  return true;
}

int Position::getHole()
{
  return hole;
}

vector<int> Position::getPositions() const
{
  return positions;
}

Position* Position::getPrevious()
{
  return previous;
}

void Position::setPrevious(const Position& pos, int hole)
{
  previous = new Position(pos);
  this->hole = hole;
}
