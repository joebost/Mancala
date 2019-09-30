# Mancala
Disclaimer: This is an assignment for the course CPSC 2120 taught by Dr. Goddard in Spring 2018.  The description below is taken from the [assignment specification on his website](https://people.cs.clemson.edu/~goddard/handouts/cpsc2120/ASG/asg3.pdf)

# Introduction
Mancala is played with 6 “holes” arranged in a circle. One hole is designated “bank”. Each
hole contains some number of “stones”. In our simplified version, the player starts a move by
picking up all the stones in one hole (but not the bank); she then proceeds clockwise (starting
in the next hole) placing the stones one in each hole, until all the stones are placed. Note
that the player gets to choose which of the 5 holes to start with; after that the process is
mechanical.

The objective is to get all the stones into the bank. The game is usually played as a race
between two players, and there are rules allowing interaction. But here we consider a singleplayer solitaire version.

# The Problem
Design and implement a C++ program that, given any initial configuration of
stones, determines the minimum number of moves to the goal-state, and the sequence of moves required.
