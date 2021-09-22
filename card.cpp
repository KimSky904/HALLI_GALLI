class Card
{
	char type;
	int number;
public:
	Card() {}
	Card(char type, int num) {
		this->type = type;
		this->number = number;
	}
	char getType() {
		return type;
	}
	int getNumber() {
		return number;
	}
};