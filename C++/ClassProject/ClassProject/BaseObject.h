#pragma once
#include <string>
#include <iostream>
using namespace std;

class BaseObject
{
protected:
	string name;
	double speed;
	double mass;
public:
	BaseObject() :name("default"), speed(0), mass(0) {};
	BaseObject(string n, double s, double m) { name = n; speed = s; mass = m; }
	BaseObject(BaseObject& a) { name = a.name; speed = a.speed; mass = a.mass; }
	virtual string GetName() { return name; }
	virtual double GetMass() { return mass; }
	virtual double GetSpeed() { return speed; }
	virtual BaseObject& operator=(BaseObject& a) { this->name = a.name; this->speed = a.speed; this->mass = a.mass; return *this; }
	~BaseObject();
};
class Plane :public virtual BaseObject
{
protected:
	double max_fly_distanse;
public:
	Plane() : BaseObject(), max_fly_distanse(0) {};
	Plane(double maxf) :BaseObject(name, speed, mass) { max_fly_distanse = maxf; };
	Plane(Plane& a) { name = a.name; speed = a.speed; mass = a.mass; max_fly_distanse = a.max_fly_distanse; }
	virtual double GetMaxFlyDistanse() { return  max_fly_distanse; }
	virtual Plane& operator=(Plane& a) { this->max_fly_distanse = a.max_fly_distanse; this->name = a.name; this->speed = a.speed; this->mass = a.mass; return *this; };
	~Plane();
};
class PassangerPlane :public virtual Plane
{
protected:
	int num_of_passangers;
public:
	PassangerPlane() : Plane(), num_of_passangers(0) {};
	PassangerPlane(int num) : Plane(max_fly_distanse) { num_of_passangers = num; }
	PassangerPlane(PassangerPlane& a) { max_fly_distanse = a.max_fly_distanse; name = a.name; speed = a.speed; mass = a.mass; num_of_passangers = a.num_of_passangers; }
	virtual int GetNumOfPassangers() { return num_of_passangers; }
	virtual PassangerPlane& operator=(PassangerPlane& a) { this->max_fly_distanse = a.max_fly_distanse; this->name = a.name; this->speed = a.speed; this->mass = a.mass; this->num_of_passangers = a.num_of_passangers; return *this; };
	~PassangerPlane();
};
class Airfreighter :public virtual Plane
{
protected:
	string class_of_cargo;
	double max_cargo_weight;
public:
	Airfreighter() :Plane(), class_of_cargo(""), max_cargo_weight(0) {};
	Airfreighter(string c, double maxc) : Plane(max_fly_distanse) { class_of_cargo = c; max_cargo_weight = maxc; }
	Airfreighter(Airfreighter& a) { max_fly_distanse = a.max_fly_distanse; name = a.name; speed = a.speed; mass = a.mass; class_of_cargo = a.class_of_cargo; max_cargo_weight = a.max_cargo_weight; }
	virtual string GetClassOfCargo() { return class_of_cargo; }
	virtual double GetMaxCargoWeight() { return max_cargo_weight; }
	virtual Airfreighter& operator=(Airfreighter& a) { this->max_fly_distanse = a.max_fly_distanse; this->name = a.name; this->speed = a.speed; this->mass = a.mass; this->class_of_cargo = a.class_of_cargo; this->max_cargo_weight = a.max_cargo_weight; return *this; };
	~Airfreighter();
};
class MultiPlane : public Airfreighter, public PassangerPlane
{
private:

public:
	MultiPlane() : PassangerPlane(), Airfreighter() {};
	MultiPlane() :PassangerPlane(num_of_passangers), Airfreighter(class_of_cargo, max_cargo_weight) {};
	MultiPlane(MultiPlane& a) { max_fly_distanse = a.max_fly_distanse; name = a.name; speed = a.speed; mass = a.mass; class_of_cargo = a.class_of_cargo; max_cargo_weight = a.max_cargo_weight; num_of_passangers = a.num_of_passangers; }
	MultiPlane& operator=(MultiPlane& a) { this->max_fly_distanse = a.max_fly_distanse; this->name = a.name; this->speed = a.speed; this->mass = a.mass; this->class_of_cargo = a.class_of_cargo; this->max_cargo_weight = a.max_cargo_weight; num_of_passangers = a.num_of_passangers; return *this; };
	~MultiPlane();
};

