#pragma once

#include "repeat.h"
#include <time.h>

class solve_game {
public:
	cards first;
	cards second;
	game_node* root;
	repeat_hash repeat_test;
	solve_game(vector<uchar>& first_, vector<uchar>& second_) {
		first.init2(first_);
		second.init2(second_);
		root = new game_node;
	}

	void generate_next(game_node* node) {
		//���ݴ˽ڵ�������һ���ڵ���Ϣ
		//���Է�Ӧ�Դ˽ڵ�������з�
		//����Ϊ�Է�����,������һ�ڵ���Ϣ
		//�����׽ڵ�Ҫ�ҵ�Ӧ�Դ˽ڵ���з�
		deque<porker_hands> x = node->father->card.what_to_deal(node->own);//�õ����е�Ӧ���з�
		node->th = 0;
		for (int i = 0; i < x.size(); i++) {
			game_node* gn = new game_node;
			gn->own = x[i];//��ֵ�з�
						   //x[i].show_self();
			gn->card = node->father->card.play_cards(x[i]);//��������ƺ����
			gn->father = node;
			gn->color = !node->color;//˳��ȡ��
			auto repeat_node = repeat_test.is_repeat(gn);

			if (repeat_node) {
				//�����������ظ��ĵ�,֮ǰ�Ѿ������
				*gn = *repeat_node;
				gn->father = node;
				node->son.push_front(gn);
			}

			else if (gn->card.nums == 0) {
				gn->win = 1;//�˽ڵ�Ӧ�����ȿ���
				node->son.push_front(gn);
			}

			else {
				node->son.push_back(gn);
			}
		}
	}

	void compute() {
		//��һ���ٶ�����:�Ľ�Ϊ��ϣ��,�ѵ������ҵ���Ч��ϣ����
		//�����ڴ����
		cout <<"������..." << endl;
		root->father = new game_node;
		root->father->card = first;
		root->card = second;
		root->own = porker_hands(porker_hands::none);
		generate_next(root);//�ɸ��ڵ����ɳ�ʼ��Ϸ��Ϣ
		root->color = 1;

		game_node* temp_node = root;
		int layer = 0;
		auto t1 = clock();

		while (root->win == -1) {
			if (!temp_node->has_next()) {
				//��ǰ�ڵ�ĺ����Ѿ��������
				//����ǰ�ڵ����к��ӽڵ��Ǳ����
				//��ǰ�ڵ��Ǳ�ʤ��
				temp_node->win = 1;
				temp_node = temp_node->father;

				temp_node->win = 0;
				temp_node = temp_node->father;
				layer -= 2;

			}

			else {
				temp_node = temp_node->get_next_node();
				layer += 1;

				if (layer == 1) {
					cout << "���������з�:";
					temp_node->own.show_self();
				}

				switch (temp_node->win)
				{
				case 1:
					//��ǰ�ڵ��Ǳ�ʤ��
					temp_node = temp_node->father;//���ص���һ���ڵ�
					temp_node->win = 0;//��һ���ڵ����
					temp_node = temp_node->father;//���ص���һ���ڵ�
					layer -= 2;
					break;

				case 0:
					//��ǰ�ڵ��Ǳ����

					temp_node = temp_node->father;//ת����һ���ڵ�
					layer -= 1;
					break;
				default:
					//�޷�ȷ����ǰ�ڵ��ʤ����	

					generate_next(temp_node);//������һ�ڵ���Ϣ����temp_node�ĺ���

					break;
				}
			}
		}
		auto t2 = clock();
		cout << "�������.." << endl;
		cout << "����ʱ��:" << t2 - t1 << "ms" << endl;
		//cout << "�ܽڵ�:" << repeat_test.get_node_nums() << endl;
	}

	void inter_active() {

		auto temp = root;
		int choose;
		if (!temp->win) {
			while (true) {
				cout << endl<<"������:";
				for (int i = 0; i < temp->son.size(); i++) {
					if (temp->son[i]->win == 1) {
						temp = temp->son[i];
						temp->own.show_self();//�ҵ���ʤ�з�
						break;
					}
				}
				cout << endl;

				if (temp->son.empty()) {
					cout << "������" << endl;
					break;
				}
				cout << "��׼����ʲô,��ѡ��һ�����:" << endl;

				for (int i = 0; i < temp->son.size(); i++) {
					cout << i << ":    ";
					temp->son[i]->own.show_self();
				}


				while (true) {
					cout << "��ѡ��:";
					cin >> choose;
					if (choose < temp->son.size() && choose >= 0) {
						break;
					}
					else {
						cout << "ѡ�����,��Ҫ����ѡ��" << endl;
					}
				}
				temp = temp->son[choose];
			}
		}

		else {
			cout << "��������" << endl;
		}
	}
};
