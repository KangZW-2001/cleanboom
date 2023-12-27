#include <iostream>
#include <memory>
using namespace std;

class Entity
{
	public:
		int x;
		Entity(int x):x(x){cout << "CONSTRUCT ENTITY WITH" << x << endl;}
		Entity(){cout << "CONSTRUCT Entity" << endl;}
		~Entity(){cout << "Deconstruct Entity" << x << endl;}
		void func(){cout << "call func" << endl;}
};

int main()
{
	shared_ptr<Entity> s;
	weak_ptr<Entity> weak_entity;
	{
		shared_ptr<Entity> share_entity = make_shared<Entity>(20);
	
		weak_entity = share_entity; 
		// unique_ptr<Entity> p = make_unique<Entity>();
		// shared_ptr<Entity> p1 = make_shared<Entity>(20);
		weak_entity.lock() -> func();
	}
	cout << "hello world" << endl;
	return 0;
}

