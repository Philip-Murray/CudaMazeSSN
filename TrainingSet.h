#pragma once
#include "MazeLayout.h"
#include "Position.h"
#include "RandomNumberGenerator.h"
#include <vector>
#include <random>

using namespace std;
vector<Position> recursiveBacktracker(NumberGenerator& ng, MazeLayout& maze, const Position& pos, const Position& finish);
vector<Position> validmoves(const MazeLayout& maze, const Position& pos);
vector<Position> validmoves(const MazeLayout& maze, const Position& pos, const int dx, const int dy);
void markVisited(MazeLayout& maze, const Position& A, const Position& B);

class TrainingSet {
public:

	MazeLayout XTrain; 
	vector<Position> pathSolution;

	Position start;
	Position finish;



	TrainingSet(NumberGenerator& ng, int dim) : XTrain(dim) {

		start = Position((int)(dim / 2), 0);
		finish = Position((int)(dim / 2), dim - 1);

		XTrain.visit(start);
		pathSolution = recursiveBacktracker(ng, XTrain, start, finish);

		ng.next();

	}
	MazeLayout* get_YTest() {
		MazeLayout* ml = new MazeLayout(XTrain.dim);
		ml->visit(start);
		for (int i = pathSolution.size() - 1; i > 0; i--) {
			markVisited(*ml, pathSolution[i], pathSolution[i - 1]);
		}
		return ml;
	}
	void print() {
		XTrain.print("X");
		std::cout << "" << std::endl;
		get_YTest()->print(" ");
	}
};


//Class contains methods for carving out a maze from a TrainingSet's MazeLayout

#define visited true
#define singleStepMode true

int random(int size) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	std::cout << dis(gen) << std::endl;
	std::cout << dis(gen) << std::endl;

	std::cout << dis(gen) << std::endl;
	return (int)(dis(gen) * size);
}


vector<Position> recursiveBacktracker(NumberGenerator& ng, MazeLayout& maze, const Position& pos, const Position& finish) {
	
	vector<Position> pathSequence;
	if (pos == finish) {
		pathSequence.push_back(pos);
		return pathSequence;
	}
	//vector<Position> moves = validmoves(maze, pos);

	for (auto moves = validmoves(maze, pos); moves.size() > 0; moves = validmoves(maze, pos)) { //moves.size() decreases by 1 as markVisited() is called

		Position nextpos = moves[ng.generate(moves.size())];

		markVisited(maze, pos, nextpos);

		vector<Position> potentialPath = recursiveBacktracker(ng, maze, nextpos, finish);
		if (potentialPath.size() > 0) {
			if (pathSequence.size() != 0) {
				std::cout << "UH OH ALREADY FOUND PATH" << std::endl;
			}
			pathSequence = potentialPath;
			pathSequence.push_back(pos);
		}
	}
	return pathSequence;
}

vector<Position> validmoves(const MazeLayout& maze, const Position& pos) {

	vector<Position> rightmoves = validmoves(maze, pos,  2,  0);
	auto             leftmoves  = validmoves(maze, pos, -2,  0);
	auto             upmoves    = validmoves(maze, pos,  0,  2);
	auto             downmoves  = validmoves(maze, pos,  0, -2);

	vector<Position> moves;
	moves.insert(moves.end(), rightmoves.begin(), rightmoves.end());
	moves.insert(moves.end(), leftmoves.begin(),  leftmoves.end());
	moves.insert(moves.end(), upmoves.begin(),    upmoves.end());
	moves.insert(moves.end(), downmoves.begin(),  downmoves.end());

	return moves;
}
vector<Position> validmoves(const MazeLayout& maze, const Position& pos, const int dx, const int dy) {

	vector<Position> moves;
	for (Position ptr = pos.plus(dx, dy); maze.inBounds(ptr); ptr.increment(dx, dy)) {
		if (maze[ptr] == visited) {
			break;
		}
		moves.push_back(ptr);

		if (singleStepMode) {
			break;
		}
	}
	return moves;
}

void markVisited(MazeLayout& maze, const Position& A, const Position& B) {
	int dy = B.getY() - A.getY();
	if (dy != 0) {
		dy = abs(dy) / dy;
	}
	int dx = B.getX() - A.getX();
	if (dx != 0) {
		dx = abs(dx) / dx;
	}
	for (Position ptr = A.plus(dx, dy); ptr != B; ptr.increment(dx, dy)) {
		maze.visit(ptr);
	}
	maze.visit(B);
}




/*
#define visited true
class TrainingSetGenerator {
private:
	TrainingSet* ts;

public:
	TrainingSet& generate() {

	}

private:
	vector<Position> recursiveBacktracker() {

	}
	vector<Position> validmoves(Position& pos) {

		int dim = ts->XTrain.getDim();

		for (int x = pos.x + 2; x < dim; x += 2) {
			if()
		}
	
	}

};


void markVisited() {

}
*/