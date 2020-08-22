#include <iostream>
#include <string>
using namespace std;


class CombatVehicle
{
protected:
	string type;
	string model;
	int health;
public:
	CombatVehicle() : type(""), model(""), health(0)
	{	}
	CombatVehicle(string type, string model, int health) :type(type), model(model), health(health)
	{	}
	virtual bool IsDestroyed() const
	{
		return (health <= 0);
	}

	virtual void ShowInfo() const
	{
		cout << "Type: " << type << "\nModel: " << model << "\nHealth: " << health << endl;
	}
	virtual int Attack() = 0;
	virtual void Defense(int damag) = 0;
	virtual ~CombatVehicle() = 0 {	}
};

class Tank : public CombatVehicle
{
private:
	float timeReload;
	float accuracy;
	float thickness;
public:
	Tank(string model, float timeReload, float accuracy, float thickness, int health) : CombatVehicle("Tank", model, health), timeReload(timeReload), accuracy(accuracy), thickness(thickness)
	{	}

	int Attack() override
	{
		int damage = (100 * accuracy / timeReload);
		return damage;
	}
	void Defense(int damage) override
	{
		health = health - (damage - thickness);
	}
	void ShowInfo() const override
	{
		CombatVehicle::ShowInfo();
		cout << "Time Reload: " << timeReload << " s" << "\nAccuracy: " << accuracy << "\nArmor Thickness: " << thickness << endl;
	}
};

class ArmoredCar : public CombatVehicle
{
private:
	int weaponCount;
	int speed;
public:
	ArmoredCar(string model, int weapons, int speed, int health) : CombatVehicle("Armored Car", model, health), weaponCount(weapons), speed(speed)
	{	}
	int Attack() override
	{
		int damage = 50 * weaponCount;
		return damage;
	}
	void Defense(int damage) override
	{
		health = health - (damage - speed / 2);
	}
	void ShowInfo() const override
	{
		CombatVehicle::ShowInfo();
		cout << "Weapon Count: " << weaponCount << "\nSpeed: " << speed << endl;
	}
};

class AirDefenseVehicle : public CombatVehicle
{
private:
	int rate;
	int lenght;
	int mobility;
public:
	AirDefenseVehicle(string model, int rate, int lenght, int mobility, int health) : CombatVehicle("Air Defense Vehicle", model, health), rate(rate), lenght(lenght), mobility(mobility)
	{	}
	int Attack() override
	{
		int damage = 150 + lenght * (rate / 10);
		return damage;
	}
	void Defense(int damage) override
	{
		health = health - (damage / mobility);
	}
	void ShowInfo() const override
	{
		CombatVehicle::ShowInfo();
		cout << "Rate: " << rate << "\nLenght: " << lenght << "\nMobility" << mobility << endl;
	}
};

bool Fight(CombatVehicle& v1, CombatVehicle& v2)
{
	int d = 0;
	int tmp = 0;;
	do
	{
		d = v1.Attack();
		v2.Defense(d);
		if (tmp == 0)
		{	cout << "Vehicle 1 damage = " << d << endl;tmp = 1;	}
		d = v2.Attack();
		v1.Defense(d);
		if (tmp == 1)
		{	cout << "Vehicle 2 damage = " << d << endl; tmp = 2;	}
	} while (!v2.IsDestroyed() && !v1.IsDestroyed());

	if (v1.IsDestroyed())
	{
		cout << "Vehicle 1 WIN\t bool: ";
		return 1;
	}
	else
	{
		cout << "Vehicle 2 WIN\t bool: ";
		return 0;
	}
}


int main()
{
	Tank t("T-34", 5.6, 95, 80, 10000);
	Tank t1("T-34", 6.2, 90, 70, 8000);
	cout << Fight(t, t1) << endl << endl;
	ArmoredCar k("WWS-12", 4, 65, 1000);
	ArmoredCar k1("RED-S/43", 3, 65, 2200);
	cout << Fight(k, k1) << endl << endl;
	AirDefenseVehicle a("AWS-113",13,15,30,3000);
	AirDefenseVehicle a1("AWS-113",15,13,28,2850);
	cout << Fight(a, a1) << endl;

	return 0;
}