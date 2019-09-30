// Mancala.cpp - Joe Bost - 4/24/18
#include "Position.h"
#include <cstdlib>
#include <queue>
#include <stack>
#include <unordered_set>
#include <string>
using namespace std;

struct position_hash //Hashing function for hashtable
{
  size_t operator()(const Position& pos) const
  {
    string tohash;
    for (int i = 0; i < 5; i++) //Loops through each hole on board
    {
      tohash += to_string(pos.getPositions().at(i)); //Combines into string
    }
    return hash<string>()(tohash); //Creates hash using # of pieces at each hole
  }
};

int main(int argc, char *argv[])
{
  if (argc < 6) //Checks for incorrect amount of args
  {
    cout << "Usage: " << argv[0] << " pos1 pos2 pos3 pos4 pos5 [hash]" << endl;
  }
  else //Correct amount of args were passed
  {
    vector<int> startVec; //Creates starting vector
    cout << "Running: Mancala ";
    for(int i = 1; i < 6; i++)
    {
      cout << argv[i] << " ";
      startVec.push_back(atoi(argv[i]));
    }
    cout << endl;

    Position* start = new Position(startVec); //Starting board
    Position* cursor = new Position(startVec); //Cursor for searching

    queue<Position> q; //Queue used for BFS
    unordered_set<Position, position_hash> dups; //Hashtable for checking dups

    bool checkDups = (argc == 7); //Toggles hashtable function
    int positions = 0; //Counter for number of positions
    bool solved = false; //Solved variable

    while(!solved) //Continuously tries to solve the board
    {
      for(int i = 0; i < 5; i++) //Tries moving pieces at every position
      {
        bool isDup = false; //Keeps track of if the board is a duplicate
        Position* checker = cursor->afterMove(i); //Checks boards b4 + to queue

        if(checker != nullptr)
        {
          if(checkDups) //Will check if the board is a dup
            isDup = !(dups.find(*checker) == dups.end());

          if(!isDup || !checkDups) //If its not a dup or not checking for dups
          {
            checker->setPrevious(*cursor, i); //Adds the checker to the tree
            q.push(*checker); //Adds the checker to the queue

            if(checker->isDone()) //Checks if the board is solved
            {
              solved = true; //Marks the board as solved
              i = 5; //Breaks the for loop on next iteration
            }
            positions++; //Increments number of boards tried

            if(checkDups)
              dups.insert(*checker); //Adds current board to the possible dups
          }
          delete checker; //Clears the checker
        }
      }

      if (!solved) //Checks if the board isn't solved
      {
        delete cursor; //Clears the cursor for next iteration
        cursor = new Position(q.front()); //Moves cursor down queue
        q.pop(); //Removes the board in the front of the queue
      }
    }

    delete cursor; //Clears cursor
    dups.clear(); //Clears hashtable

    cursor = new Position(q.back()); //Pulls the solved board from the queue

    while(!q.empty()) //Removes all boards from the queue
      q.pop();

    cout << "Positions Found: " << positions << endl;

    stack<Position> moves; //Stack of moves needed to reach goal
    while(!(*cursor == *start)) //Creates the stack of moves needed to solve
    {
      Position* next = new Position(*cursor->getPrevious()); //Next move
      moves.push(*cursor); //Adds move to the stack
      delete cursor; //Clears cursor for next iteration
      cursor = next; //Moves cursor to next move
    }
    delete cursor; //Clears cursor

    cout << "NUMBER OF MOVES: " << moves.size() << endl << *start << endl;
    delete start; //Clears starting board

    while(!moves.empty()) //Clears the stack and prints moves to the console
    {
      cursor = new Position(moves.top()); //Gets the move from the stack
      cout << "Move:" << cursor->getHole()+1 << " yields " << *cursor << endl;
      moves.pop(); //Removes the move from the stack
      delete cursor; //Clears cursor for next iteration
    }

    cout << endl << "Created " << Position::created << " and Destroyed " << Position::destroyed << endl;
  }
  return 0;
}
