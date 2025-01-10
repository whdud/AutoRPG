#include <iostream>
#include <string>
#include <vector>

class Animal {

public:
	Animal(){}
	virtual void makeSound() = 0;
	virtual ~Animal(){}

};

class Dog : public Animal
{
public:
	void makeSound() override {
		std::cout << "Dog: 멍!멍!" << std::endl;
	}
};

class Cat : public Animal {
public:
	void makeSound() override {
		std::cout << "Cat: 냐옹~" << std::endl;
	}
};

class Cow : public Animal {
public:
	void makeSound() override {
		std::cout << "Cow: 음메~" << std::endl;
	}
};
// 도전기능 시작
int main() {
	std::vector<Animal*>animals;

	animals.push_back(new Dog());
	animals.push_back(new Cat());
	animals.push_back(new Cow());

	for (auto& animal : animals) {
		animal->makeSound();
	}
	
	for (auto& animal : animals) {
		delete animal;
	}
	return 0;
};