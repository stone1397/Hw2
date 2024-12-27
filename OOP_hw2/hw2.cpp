#include<iostream>
#include<string>
#include<cstdlib> // ���� ������ ���� �߰�
#include<ctime>


class Animal {
public:
	virtual void makeSound() = 0; // ���� ���� �Լ�
	virtual void move() = 0;

};


// Zoo�� Animal�� ����ϹǷ� Animal Ŭ������ ���� ���� ����� ��
class Zoo {
private:
	Animal* animals[10] = { nullptr }; // ���� ��ü�� �����ϴ� ������ �迭
	int animal_count = 0; // ���� �������� ������ ��

public:
	// ������ �������� �߰��ϴ� �Լ�
	// - Animal ��ü�� �����͸� �޾� ������ �迭�� �����մϴ�.
	// - ���� �����̶� ���� �� �߰��� �� �ֽ��ϴ�.
	// - �Է� �Ű�����: Animal* (�߰��� ���� ��ü)
	// - ��ȯ��: ����
	void addAnimal(Animal* animal)
	{
		if (animal_count == 10) {
			std::cout << "�������� ���� �� ������ �߰��� �� �����ϴ�." << std::endl;
		}
		else {
			for (int i = animal_count; i > 0; i--) {
				animals[i] = animals[i - 1];
			}
			animals[0] = animal;
			animal_count++;
		}

	}


	// �������� �ִ� ��� ������ �ൿ�� �����ϴ� �Լ�
	// - ��� ���� ��ü�� ���� ���������� �Ҹ��� ���� �����̴� ������ �����մϴ�.
	// - �Է� �Ű�����: ����
	// - ��ȯ��: ����
	void performActions()
	{
		for (int i = 0; i < 10; i++) {
			if (animals[i] != nullptr) {
				animals[i]->makeSound();
				animals[i]->move();
			}			
		}
	}

	// Zoo �Ҹ���
	// - Zoo ��ü�� �Ҹ�� ��, ���� ���Ϳ� ����� ��� ���� ��ü�� �޸𸮸� �����մϴ�.
	// - �޸� ������ �����ϱ� ���� ���� �Ҵ�� Animal ��ü�� `delete` �մϴ�.
	// - �Է� �Ű�����: ����
	// - ��ȯ��: ����
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
		std::cout << "�п�!" << std::endl;
	}

	void move()
	{
		std::cout << "���� �ɽ��ϴ�." << std::endl;
	}
};

class Cat : public Animal {
public:
	void makeSound()
	{
		std::cout << "�߿�~" << std::endl;
	}
	void move()
	{
		std::cout << "����̰� ������ ���ϴ�." << std::endl;
	}

};

class Cow : public Animal {
public:
	void makeSound()
	{
		std::cout << "����~~" << std::endl;
	}
	void move()
	{
		std::cout << "�Ұ� ������ �̵��մϴ�." << std::endl;
	}

};

// ���� ������ �����ϴ� �Լ�
// - 0, 1, 2 �� �ϳ��� ������ �����Ͽ� ���� Dog, Cat, Cow ��ü �� �ϳ��� �������� �����մϴ�.
// - ������ ��ü�� Animal Ÿ���� �����ͷ� ��ȯ�˴ϴ�.
// - �Է� �Ű�����: ����
// - ��ȯ��: Animal* (������ ���� ��ü�� ������)
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
	
	srand(static_cast<unsigned int>(time(0)));// ���� �ʱ�ȭ, time(0)�� ���� �ð��� �õ�� �Ѵٴ� �ǹ�

	Zoo zoo;

	for (int i = 0; i < 10; i++) {
		Animal* animal = createRandomAnimal(); // ������ ���� ����
		zoo.addAnimal(animal); // ������ ���� �������� �ֱ�
	}

	zoo.performActions(); //������ �ൿ ����!

	return 0;
}

