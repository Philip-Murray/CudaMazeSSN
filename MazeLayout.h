#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Position.h"


class MazeLayout {
public:
	bool* grid;
	int dim;


	MazeLayout(int dim) {
		this->dim = dim;
		grid = new bool[dim * dim];
		for (int i = 0; i < dim * dim; i++) {
			grid[i] = false;
		}
	}
	~MazeLayout() {
		delete grid;
	}
	void set(int x, int y, bool state) {

		if (x < 0 || x >= dim || y < 0 || y >= dim) {
			printf("set invalid position");
			exit(0);
		}
		grid[y * dim + x] = state;
	}
	bool get(const int x, const int y) const {
		if (x < 0 || x >= dim || y < 0 || y >= dim) {
			printf("get invalid position %d  %d %d", dim, x, y);
			exit(0);
		}
		return grid[y * dim + x];
	}
	void visit(const Position& p) {
		set(p.getX(), p.getY(), true);
	}
	void set(const Position& p, const bool state) {
		set(p.getX(), p.getY(), state);
	}
	bool get(const Position& p) const {
		return get(p.getX(), p.getY());
	}
	int getDim() {
		return dim;
	}
	bool operator[](const Position& p) const {
		return get(p.getX(), p.getY());
	}
	bool operator==(const MazeLayout& p) const {
		//std::cout << "OPERATOR OVERLOAD " << std::endl;
		for (int i = 0; i < p.dim * p.dim; i++) {
			//std::cout << i << " " << p.grid[i] << " " << this->grid[i] << " " << (p.grid[i] != this->grid[i]) << std::endl;
			if (p.grid[i] != this->grid[i]) {
				return false;
			}
		}
		return true;
	}


	bool inBounds(const Position& p) const {
		if (0 <= p.getX() && p.getX() < dim && 0 <= p.getY() && p.getY() <= dim) {
			return true;
		}
		return false;
	}

	void print(std::string wall_symbol) {

		for (int y = dim - 1; y >= 0; y--) {
			std::string line = "";
			for (int x = 0; x < dim; x++) {
				line += (get(x, y) ? ". " : wall_symbol + " ");
			}
			std::cout << line << std::endl;
		}
	}
	/*
	MazeLayout(const MazeLayout& p2) { 
		this->dim = p2.dim;
		grid = new bool[dim * dim];
		for (int i = 0; i < dim * dim; i++) {
			grid[i] = false;
		}
	} */
};