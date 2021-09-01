#include <iostream>
#include <vector>
#include <time.h>
#include <string>

using namespace std;

// Component interface
class IUnit
{
public:
	virtual int GetStrength() = 0;
	virtual string GetInfo(int level) = 0;
	virtual void AddUnit(IUnit* unit) {}
	virtual ~IUnit() {}
};

// Leafs class
class Infantery : public IUnit
{
public:
	int GetStrength() override
	{
		return 1;
	}
	string GetInfo(int level) override
	{
		return "Infantery - 1\n";
	}
};

class Archer : public IUnit
{
public:
	int GetStrength() override
	{
		return 2;
	}
	string GetInfo(int level) override
	{
		return "Archer - 2\n";
	}
};

class Cavalery : public IUnit
{
public:
	int GetStrength() override
	{
		return 3;
	}
	string GetInfo(int level) override
	{
		return "Cavalery - 3\n";
	}
};

// Composite class
class UnitComposite : public IUnit
{
	vector<IUnit*> chUnits;
public:
	int GetStrength() override
	{
		int total{ 0 };
		for (int i = 0; i < chUnits.size(); i++)
			total += chUnits[i]->GetStrength();
		return total;
	}
	string GetInfo(int level) override
	{
		string str{ "" };
		string temp{ "" };
		for (int i = 0; i < level; i++)
			temp += "\t";
		for (int i = 0; i < chUnits.size(); i++)
		{
			str += temp + chUnits[i]->GetInfo(level + 1);
		}
		return str;
	}

	void AddUnit(IUnit* unit) override
	{
		chUnits.push_back(unit);
	}
	~UnitComposite()
	{
		for (int i = 0; i < chUnits.size(); i++)
			delete chUnits[i];
	}
};

IUnit* CreateLegion(int count = 1)
{
	IUnit* legion = nullptr;

	int choise = rand() % 3;

	if (count == 1)
	{
		switch (choise)
		{
		case 0: legion = new Infantery(); break;
		case 1: legion = new Archer(); break;
		case 2: legion = new Cavalery(); break;
		}
		//return legion;
	}
	else
	{
		legion = new UnitComposite();

		for (int i = 0; i < count; i++)
		{
			IUnit* unit;
			choise = rand() % 3;
			switch (choise)
			{
			case 0: unit = new Infantery(); break;
			case 1: unit = new Archer(); break;
			case 2: unit = new Cavalery(); break;
			default: unit = nullptr;
			}
			legion->AddUnit(unit);
		}
	}

	return legion;
}

int main()
{
	srand(time(nullptr));

	UnitComposite* army = new UnitComposite();

	UnitComposite* army2 = new UnitComposite();
	army2->AddUnit(CreateLegion(4));

	army->AddUnit(CreateLegion());
	army->AddUnit(CreateLegion(5));

	army->AddUnit(CreateLegion());
	army->AddUnit(army2);
	army->AddUnit(CreateLegion(10));

	cout << army->GetInfo(0);
	cout << army2->GetStrength();

	delete army;

	return 0;
}