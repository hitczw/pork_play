#pragma once
#include "cards.h"

class game_node {
public:
	cards card;//�Լ�������
	porker_hands own;//�Լ��ĳ���
	game_node* father;//��һ���ڵ�ĳ���
	deque<game_node*> son;//����Ӧ����һ���ڵ�
	bool color;//�ж�����һ��
	char win = -1;//1:�˽ڵ��ʤ,0:�˽ڵ����,-1:��ȷ��
	int th;


	bool operator<(const game_node& b)const {

		re rrr;
		if (color != b.color) { return color < b.color; }
		//��ͬһ����ɫ

		rrr = own.compare(b.own);
		if (!rrr.equal) { return rrr.smaller; }
		//��ͬһ���з�

		rrr = card.compare(b.card);
		if (!rrr.equal) { return rrr.smaller; }
		//��ͬһ����

		rrr = father->card.compare(b.father->card);
		if (!rrr.equal) { return rrr.smaller; }
		//������Ҳ��ͬ

		return false;
	}
	game_node* get_next_node() {
		game_node* result;
		if (th < son.size()) {
			result = son[th];
			th += 1;
		}
		else { result = 0; }

		return result;
	}

	bool has_next() {
		return th < son.size();
	}
};



