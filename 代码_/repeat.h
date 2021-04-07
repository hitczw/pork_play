#pragma once
#include "game_node.h"
#include <unordered_set>
#include <set>

//�����ظ����жϷ���:1.ͨ�������� 2.ͨ����ϣ��
//���з������Թ�ϣ���ٶȿ�һ������

class repeat_set {
	//���������������Ĳ����ж�
	class cmp {
	public:
		bool operator()(const game_node*x, const game_node* y)const {
			return *x < *y;
		}
	};
	set<game_node*, cmp> ss;
public:
	game_node* is_repeat(game_node* input) {
		auto result = ss.find(input);
		if (result != ss.end()) {
			//�ҵ��ظ��ڵ�
			return *result;
		}
		//���ظ��ڵ�
		ss.insert(input);
		return 0;
	}

	int get_node_nums() {
		return ss.size();
	}
};

class repeat_hash {
	//���ݹ�ϣ�����Ĳ����ж�
	//�ؼ�����֮:���Ѱ�Ҹ���Ĺ�ϣ����
	class get_size_t {
	public:
		size_t operator()(const game_node*x)const {
			static int p = 2;
			size_t hash = 0;
		   
			hash = (hash<<p)-hash+x->color;
			hash = (hash<<p)-hash+x->own.tp;
			hash = (hash<<p)-hash+x->own.main_value;
			hash = (hash<<p)-hash+x->own.value1;
			////hash = (hash<<p)-hash+x->own.value2;
			//result = result*131  + card[i];//BKDR�㷨
			for (int i = 3; i <= 18; i++) {
				if (i != 15) {
					hash = (hash << p) - hash + x->card.card[i];
				}
			}
			
			for (int i = 3; i <= 18; i++) {
				if (i != 15) {
					hash = (hash << p) - hash + x->father->card.card[i];
				}
			}
			return hash;
		}
	};

	class cmp {
	public:
		bool  operator()(const game_node* x,const game_node* y)const{
			if (x->color != y->color) { return false; }
			if (!(x->own == y->own)) { return false; }
			if (!(x->card == y->card)) { return false; }
			if (!(x->father->card == y->father->card)) { return false; }
			
			return true;
		}
	};
	unordered_set<game_node*, get_size_t,cmp> ss;

public:
	game_node* is_repeat(game_node* input) {
		auto result = ss.find(input);
		if (result != ss.end()) {
			//�ҵ��ظ��ڵ�
			return *result;
		}
		//���ظ��ڵ�
		ss.insert(input);
		return 0;
	}

	int get_node_nums() {
		return ss.size();
	}
};
