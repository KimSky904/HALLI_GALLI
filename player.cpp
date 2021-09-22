class Player {
	//플레이순서
	int playOrder;
	//카드 개수
	int cardCount;
	//플레이 가능 여부
	bool isAvailPlay;
public:
	Player() {}
	Player(int order) {
		this->playOrder = order;
	}
	//카드 분배받기
	void initCard() {
		cardCount = 28;
	}
	//카드 내기
	void putCard() {
		cardCount--;
	}
	//카드 얻기
	void getCard() {
		cardCount++;
	}
	//여분 카드 확인
	void setAvailPlay() {
		if (cardCount > 0)
			this->isAvailPlay = true;
		else
			this->isAvailPlay = false;
	}

};