#include "ofMain.h"
#include "ofApp.h"
#include "../MazeLayout.h"
#include "../Position.h"
#include "../TrainingSet.h"

//========================================================================

class Obj {
public:
	int id = 7;
};

bool contains(vector<TrainingSet*>& v, TrainingSet& ts) {
	for (TrainingSet* t : v) {
	//	std::cout << "compare" << std::endl;
	//	t->XTrain.print("X");
	//	ts.XTrain.print("X");
		if (t->XTrain == ts.XTrain) {
			

			return true;
		}
		
	}
	return false;
}

int main(){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());

	
	NumberGenerator* ng = new RandomGenerator();

	vector<TrainingSet*> tss;

	int i = 0;
	while (ng->canProduceMore()) {
		TrainingSet* ts = new TrainingSet(*ng, 9);
		if (contains(tss, *ts)) {
			continue;
		}
		tss.push_back(ts);
	
		//ts->XTrain.print("X"); //
		//std::cout << "" << std::endl;
		i++;
		if (i == 3) {
			break;
		}
	}
	std::cout << tss.size() << std::endl;
	for (int i = 0; i < tss.size(); i++) {
		tss[i]->print();
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
	}
	std::cout << tss.size() << std::endl;

}

/*
float x = random(3);

	Obj* o = new Obj();

	Obj& r = *o;

	//Obj* p = &r;
	std::vector<Obj*> q;
	q.push_back(o);
	std::vector<Obj*>::reverse_iterator itt = q.rbegin();
	Obj* get = *itt;

	printf("%p and %p", o, get);

*/




/*
*  use *A to supply a method A& and it will affect A
* 
	MazeLayout* ml = new MazeLayout(5);
	ml->print("X");
	ml->set(2, 2, true);
	ml->set(2, 0, true);
	ml->set(1, 0, true);
	//std::cout << "" << std::endl;
	ml->print("X");
	*/

	/*
	Without copy constructor, xml's grid points to ml's grid, so it looks like same reference upon dereference

	MazeLayout* ml = new MazeLayout(5);
	ml->set(2, 2, true);

	MazeLayout xml = *ml;
	xml.set(1, 0, true);

	ml->print("X");
	std::cout << "" << std::endl;
	xml.print("X");
	*/

/*
Obj* a = new Obj(5);

std::vector<Obj> x;
x.push_back(*a);
x[0].ID = 7;

Obj b(88);


Obj c = *a;
c.ID = 10;

std::cout << a->ID << std::endl;
std::cout << x[0].ID << std::endl;

//printf("%p %p", &ml, &xml);
*/