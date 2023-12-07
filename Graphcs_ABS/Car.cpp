#include"Car.h"

Car::Car()
{
	Curr_Position = 0;
	load = 0;
}

Car::Car(int Curr_Position, int load)
{
	this->Curr_Position = Curr_Position;
	this->load = load;
}