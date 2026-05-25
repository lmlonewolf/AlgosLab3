#include "Header.h"


Stack::Stack(size_t size) {
	capacity = size;
	if (size != 0)
		arr = new char[capacity];
}

Stack::~Stack() {
	delete[] arr;
}


bool Stack::is_empty() const {
	return top_index == -1;
}

char Stack::top() const {
	if (is_empty())
		throw std::out_of_range("Stack is empty");
	return arr[top_index];
}

void Stack::push(char ch) {
	if (top_index + 1 == capacity) {
		capacity *= 2;
		char* temp = new char[capacity];
		for (int i = 0; i <= top_index; i++)
			temp[i] = arr[i];
		delete[] arr;
		arr = temp;
	}
	arr[++top_index] = ch;
	if (top_index + 1 > max_deep)
		max_deep = top_index + 1;
}

char Stack::pop() {
	if (is_empty())
		throw std::out_of_range("Stack is empty");
	return arr[top_index--];
}

int Stack::get_max_deep() const  {
	return max_deep;
}

void Stack::print() {
	std::cout << "Stack now:" << std::endl;
	for (int i = top_index; i > -1; i--)
		std::cout << arr[i] << std::endl;
}



BracketsTest::BracketsTest(std::string str) {
	this->str = str;
	len = str.length();
}


std::string BracketsTest::get_type_error() const  {
	switch (type_error) {
		case -1:
			return "All correct";
		case 1:
			return "Extra closing brackets";
		case 2:
			return "Incorrect brackets order";
		case 3:
			return "missing closing brackets";
	}
}

std::string BracketsTest::get_brackets_balance() const {
	int counter = 0;

	if (str == "")
		throw std::out_of_range("String is empty");

	Stack stack(len);
	for (int i = 0; i < len; i++) {
		char el = str[i];
		if (in_alph(el)) {
			if (dict.find(el) != dict.end())
				counter--;
			else
				counter++;
		}
	}
	
	if (counter == 0)
		return "Equal opening and closing brackets";
	if (counter > 0)
		return "More opening brackets";
	return "More closing brackets";
}

bool BracketsTest::in_alph(char ch) const {
	for (int i = 0; i < 8; i++) {
		if (alph[i] == ch)
			return true;
	}
	return false;
}

bool BracketsTest::test() {
	if (str == "")
		throw std::out_of_range("String is empty");

	Stack stack(len);
	for (int i = 0; i < len; i++) {
		char el = str[i];

		std::cout << std::endl << i << ' ';
		stack.print();

		if (in_alph(el)) {
			if (stack.is_empty()) {
				if (dict.find(el) != dict.end()) { // Ошибка начала стека
					first_error = i;
					type_error = 1;
					std::cout << "Is correct test: " << false << std::endl;
					return false;
				}

				stack.push(el);
				continue;
			}
			bool flag = 0;
			if (dict.find(el) != dict.end()) {
				if (stack.top() == dict.at(el)) {
					stack.pop();
					count_pair++;
					flag = 1;
				}
				else { // Ошибка порядка
					first_error = i;
					type_error = 2;
					max_deep = stack.get_max_deep();
					std::cout << "Is correct test: " << false << std::endl;
					return false;
				}
			}
			if (!flag)
				stack.push(el);
			else
				flag = 0;
		}
		std::cout << std::endl << i + 1 << ' ';
		stack.print();
	}
	max_deep = stack.get_max_deep();
	if (!stack.is_empty()) { // Проверка конца стека
		first_error = static_cast<int> (len);
		type_error = 3;
		std::cout << "Is correct test: " << false << std::endl;
		return false;
	}
	std::cout << "Is correct test: " << true << std::endl;
	return true;
}