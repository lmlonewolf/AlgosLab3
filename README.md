# Лабораторная работа 3

# Проверка скобочных выражений (Stack)

## В ходе работы был реализован следующий функционал
### Обязательная часть
* Функция проверки строки
* Поддержка `(), [], {}`
### Вариативная часть
1. Добавить поддержку `< >`
2. Вернуть позицию первой ошибки
3. Подсчитать количество пар скобок в строке: ([]) -> 2, ()[]{} -> 3
4. Проверять строку и игнорировать все символы, кроме скобок a + (b * c) -> true, if (a[2] > b) -> true
5. Вывести, каких скобок в строке больше: открывающих, закрывающих, ровно
6. Определить максимальную глубину вложенности скобок
7. Вывести сообщение с причиной ошибки Например: «лишняя закрывающая скобка» или «не хватает закрывающей скобки»
8. Показывать содержимое стека после каждого шага

## Реализация
### `Стек`
**Структура**
``` cpp
class Stack {
	char* arr = nullptr;
	size_t capacity = 0;
	int top_index = -1;
	int max_deep = 0;

public:
	Stack(size_t size);
	~Stack(void);

	bool is_empty(void) const;
	char top(void) const;
	void push(char ch);
	char pop(void);
	int get_max_deep(void) const;
	void print(void);
};
```

**Конструктор и деструктор**
``` cpp
Stack::Stack(size_t size) {
	capacity = size;
	if (size != 0)
		arr = new char[capacity];
}

Stack::~Stack() {
	delete[] arr;
}
```

**Основные методы**
``` cpp
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
```

**Вспомогательные методы**
``` cpp
int Stack::get_max_deep() const  {
	return max_deep;
}

void Stack::print() {
	std::cout << "Stack now:" << std::endl;
	for (int i = top_index; i > -1; i--)
		std::cout << arr[i] << std::endl;
}
```

### `BracketsTest`
**Структура**
``` cpp
class BracketsTest{
	std::string str = "";
	size_t len = 0;

	bool correct = false;
	int first_error = -1;
	int count_pair = 0;
	int max_deep = 0;
	int type_error = -1;

	const std::string alph = "<>{}[]()";
	const std::map<char, char> dict = {
		{'>', '<'},
		{'}', '{'},
		{']', '['},
		{')', '('}
	};

	bool in_alph(char ch) const;
	bool test(void);

public:
	BracketsTest(std::string str);
	
	std::string get_type_error(void) const;
	std::string get_brackets_balance(void) const;
	void print_full_test(void);	
};
```

**Конструктор**
``` cpp
BracketsTest::BracketsTest(std::string str) {
	this->str = str;
	len = str.length();
	correct = test();
}
```

**Основной метод (Тест)** 
``` cpp
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
		return false;
	}
	return true;
}
```

**Вспомогательные методы**
``` cpp
// Тип ошибки
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

// Баланс открывающих и закрывающих скобок
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

// Проверка наличия в алфавите скобок
bool BracketsTest::in_alph(char ch) const {
	for (int i = 0; i < 8; i++) {
		if (alph[i] == ch)
			return true;
	}
	return false;
}

// Вывод паолного отчёта
void BracketsTest::print_full_test() {
	std::cout << "Is correct test: " << correct << std::endl;
	std::cout << "First error: " << first_error << std::endl;
	std::cout << "Type error: " << get_type_error() << std::endl;
	std::cout << "Count pair: " << count_pair << std::endl;
	std::cout << "Max deep: " << max_deep << std::endl;
	std::cout << "Brackets balance: " << get_brackets_balance() << std::endl;
}
```