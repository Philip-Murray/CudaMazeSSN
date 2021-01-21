#pragma once
#include <random>
#include <stack>
#include <queue>

class NumberGenerator {
public: 
	virtual int generate(int range) = 0;
	virtual void next() {};
	virtual bool canProduceMore() { return true; }
};

class RandomGenerator : public NumberGenerator {
private:
	std::mt19937 gen;
	std::uniform_real_distribution<> dis;

public:
	RandomGenerator() {
		std::random_device rd;
		gen = std::mt19937(rd());
		dis = std::uniform_real_distribution<>(0, 1);
	}
	virtual int generate(int range) {
		return (int) (dis(gen) * range);
	}
};



class Node {
public:
	int number;

	int outof;

	Node* parent;
	std::vector<Node>* children = nullptr;

	Node(Node* parent, int n, int of) {
		this->parent = parent;
		number = n;
		outof = of;
	}
};

std::vector<Node>* makeOptionsVector(Node* parent, int resultingRange);

class NextRouteGenerator : public NumberGenerator {
private:
	std::vector<Node>* root = nullptr;

	std::stack<Node*> untestedMoveSequenceLeafs;

	bool onFirstGeneration = true;

	std::stack<Node*> sequenceToNextUntestedLeaf;

public:
	

	virtual int generate(int range) {

		if (onFirstGeneration) { // The maze generated will always explore the first move presented in it's recursive backtracker
			if (root == nullptr) {
				root = makeOptionsVector(nullptr, range);
				for (std::vector<Node>::reverse_iterator itt = root->rbegin(); itt != root->rend(); ++itt) {
					untestedMoveSequenceLeafs.push(&(*itt));
				}
				return 0;
			}
			Node* lowerleftmostMoveIndex = untestedMoveSequenceLeafs.top();
			untestedMoveSequenceLeafs.pop();
			lowerleftmostMoveIndex->children = makeOptionsVector(lowerleftmostMoveIndex, range);
			for (std::vector<Node>::reverse_iterator itt = lowerleftmostMoveIndex->children->rbegin(); itt != lowerleftmostMoveIndex->children->rend(); ++itt) {
				untestedMoveSequenceLeafs.push(&(*itt));
			}
			return 0;
		}

		if (!sequenceToNextUntestedLeaf.empty()) { //set on next()

			Node* ptr = sequenceToNextUntestedLeaf.top(); 
			sequenceToNextUntestedLeaf.pop();
	
			if (range != ptr->outof) {
				printf("RANGE NOT EQUAL IN goal != ptr");
				exit(0);
			}
			return ptr->number;
		}
		Node* untestedIndex = untestedMoveSequenceLeafs.top();
		untestedMoveSequenceLeafs.pop();
		untestedIndex->children = makeOptionsVector(untestedIndex, range);
		for (std::vector<Node>::reverse_iterator itt = untestedIndex->children->rbegin(); itt != untestedIndex->children->rend(); ++itt) {
			untestedMoveSequenceLeafs.push(&(*itt));
		}
		return 0;
	}
	void next() override {
		onFirstGeneration = false;
		untestedMoveSequenceLeafs.pop();
		if (!untestedMoveSequenceLeafs.empty()) {
			sequenceToNextUntestedLeaf = getSequenceToLeaf(untestedMoveSequenceLeafs.top());
		}
		else {
			std::cout << "empty empty empty empty" << std::endl;
		}
	
		
	}
	bool canProduceMore() override {
		if (untestedMoveSequenceLeafs.size() == 0 && root != nullptr) {
			return false;
		}
		return true;
	}
	std::stack<Node*> getSequenceToLeaf(Node* leaf) {
		std::stack<Node*> sequence;
		Node* ptr;
		for (ptr = leaf; ptr->parent != nullptr; ptr = ptr->parent) {
			sequence.push(ptr);
		}
		sequence.push(ptr);
		return sequence;
	}
};


std::vector<Node>* makeOptionsVector(Node* parent, int range) {

	std::vector<Node>* options = new std::vector<Node>();
	options->reserve(range);
	for (int i = 0; i < range; i++) {
		options->emplace_back(parent, i, range);

	}
	return options;
}




/*

	virtual int generate(int range) {

		if (onFirstCase) {
			if (root == nullptr) {
				root = makeOptionsVector(nullptr, range);
				for (std::vector<Node*>::reverse_iterator itt = root->rbegin(); itt != root->rend(); ++itt) {
					unvisitedMoveOptions.push(*itt);
				}
				return 0;
			}
			Node* lowerleftmostMoveIndex = unvisitedMoveOptions.top();
			unvisitedMoveOptions.pop();
			return lowerleftmostMoveIndex->number;
		}
		else {

		}
	}
	void next() override {
		onFirstCase = false;
		unvisitedMoveOptions.pop();
	}*/