#include<iostream>
#include<string>
#include<cstdlib> // 난수 생성을 위해 추가
#include<ctime>


class Animal {
public:
	virtual void makeSound() = 0; // 순수 가상 함수
	virtual void move() = 0;

};


// Zoo가 Animal을 사용하므로 Animal 클래스를 전방 선언 해줘야 함
class Zoo {
private:
	Animal* animals[10] = { nullptr }; // 동물 객체를 저장하는 포인터 배열
	int animal_count = 0; // 현재 동물원의 동물의 수

public:
	// 동물을 동물원에 추가하는 함수
	// - Animal 객체의 포인터를 받아 포인터 배열에 저장합니다.
	// - 같은 동물이라도 여러 번 추가될 수 있습니다.
	// - 입력 매개변수: Animal* (추가할 동물 객체)
	// - 반환값: 없음
	void addAnimal(Animal* animal)
	{
		if (animal_count == 10) {
			std::cout << "동물원이 가득 차 동물을 추가할 수 없습니다." << std::endl;
		}
		else {
			for (int i = animal_count; i > 0; i--) {
				animals[i] = animals[i - 1];
			}
			animals[0] = animal;
			animal_count++;
		}

	}


	// 동물원에 있는 모든 동물의 행동을 수행하는 함수
	// - 모든 동물 객체에 대해 순차적으로 소리를 내고 움직이는 동작을 실행합니다.
	// - 입력 매개변수: 없음
	// - 반환값: 없음
	void performActions()
	{
		for (int i = 0; i < 10; i++) {
			if (animals[i] != nullptr) {
				animals[i]->makeSound();
				animals[i]->move();
			}			
		}
	}

	// Zoo 소멸자
	// - Zoo 객체가 소멸될 때, 동물 벡터에 저장된 모든 동물 객체의 메모리를 해제합니다.
	// - 메모리 누수를 방지하기 위해 동적 할당된 Animal 객체를 `delete` 합니다.
	// - 입력 매개변수: 없음
	// - 반환값: 없음
	~Zoo()
	{
		for (int i = 0; i < animal_count; i++) {
			if (animals[i] != nullptr) {
				delete animals[i];
				animals[i] = nullptr;
			}
			
		}
	}

};




class Dog : public Animal {
public:
	void makeSound()
	{
		std::cout << "왈왈!" << std::endl;
	}

	void move()
	{
		std::cout << "개가 앉습니다." << std::endl;
	}
};

class Cat : public Animal {
public:
	void makeSound()
	{
		std::cout << "야옹~" << std::endl;
	}
	void move()
	{
		std::cout << "고양이가 꼬리를 흔듭니다." << std::endl;
	}

};

class Cow : public Animal {
public:
	void makeSound()
	{
		std::cout << "으무~~" << std::endl;
	}
	void move()
	{
		std::cout << "소가 밭으로 이동합니다." << std::endl;
	}

};

// 랜덤 동물을 생성하는 함수
// - 0, 1, 2 중 하나의 난수를 생성하여 각각 Dog, Cat, Cow 객체 중 하나를 동적으로 생성합니다.
// - 생성된 객체는 Animal 타입의 포인터로 반환됩니다.
// - 입력 매개변수: 없음
// - 반환값: Animal* (생성된 동물 객체의 포인터)
Animal* createRandomAnimal()
{

	int animal_number = rand() % 3;


	switch (animal_number) {
	case 0:
		return new Dog();
		break;

	case 1:
		return new Cat();
		break;

	case 2:
		return new Cow();
		break;

	default:
		return nullptr;
	}
}

int main()
{
	Dog dog;
	Cat cat;
	Cow cow;
	Animal* pAnimal_arr[3] = { &dog, &cat, &cow };
	Animal* pAnimal;
	for (int i = 0; i < 3; i++) {
		pAnimal = pAnimal_arr[i];
		pAnimal->makeSound();
	}
	
	srand(static_cast<unsigned int>(time(0)));// 난수 초기화, time(0)는 현재 시간을 시드로 한다는 의미

	Zoo zoo;

	for (int i = 0; i < 10; i++) {
		Animal* animal = createRandomAnimal(); // 무작위 동물 생성
		zoo.addAnimal(animal); // 무작위 동물 동물원에 넣기
	}

	zoo.performActions(); //동물들 행동 시작!

	return 0;
}

