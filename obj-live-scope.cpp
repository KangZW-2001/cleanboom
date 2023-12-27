#include <iostream>
#include <memory>
using namespace std;


class Entity{
public:
	int x,y;
	Entity(){
		cout << "Construct Entity" << endl;
	}
	Entity(int x, int y):x(x), y(y){}
	~Entity(){
		cout << "Deconstruct Entity" << endl;
	}
};

class ScopePointer{
public:
	Entity * e;
	ScopePointer(Entity* e)
	:e(e)
	{}
	~ScopePointer(){delete e;}
};



int main(){
	{
		ScopePointer s = new Entity();
	}
	return 0;
}
