class Player {
	//�÷��̼���
	int playOrder;
	//ī�� ����
	int cardCount;
	//�÷��� ���� ����
	bool isAvailPlay;
public:
	Player() {}
	Player(int order) {
		this->playOrder = order;
	}
	//ī�� �й�ޱ�
	void initCard() {
		cardCount = 28;
	}
	//ī�� ����
	void putCard() {
		cardCount--;
	}
	//ī�� ���
	void getCard() {
		cardCount++;
	}
	//���� ī�� Ȯ��
	void setAvailPlay() {
		if (cardCount > 0)
			this->isAvailPlay = true;
		else
			this->isAvailPlay = false;
	}

};