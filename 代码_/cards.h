#pragma once
#include"porker_hands.h"
#include<deque>

class cards {
	//3 4 5 6 7 8 9 10 J  Q  K  A  2  k  K
	//3 4 5 6 7 8 9 10 11 12 13 14 16 17 18
public:

	//vector<uchar> card = vector<uchar>(20, 0);
	uchar card[20]{};
	uchar nums;//����

	bool operator==(const cards& b)const {
		if (nums != b.nums) { return false; }
		for (int i = 3; i < 18; i++) {
			if (card[i] != b.card[i]) { return false; }
		}
		return true;
	}
	

	void show_self()const {
		for (int i = 3; i <= 18; i++) {
			cout << (int)card[i] << " ";
		}
		cout << endl;
	}

	re compare(const cards& b)const {
		for (int i = 0; i < 20; i++) {
			if (card[i] != b.card[i])
				return re(false, card[i] < b.card[i]);
		}
		//����ֵ�����
		return re(true, false);
	}

	void init2(vector<uchar>& c) {
		nums = c.size();

		for (int i = 0; i < nums; i++) {
			card[c[i]] += 1;
		}
	}

	void get_single(porker_hands& input,
					deque<porker_hands>& result,
		int nums) {
		for (uchar i = 18; i >= input.main_value + 1; i--) {
			if (card[i] == nums) {
				porker_hands mid(input.tp, i);
				result.push_front(mid);
			}
			else if (card[i] > nums) {
				porker_hands mid(input.tp, i);
				result.push_back(mid);
			}
		}
	}

	void get_bring(porker_hands& input,
		           deque<porker_hands>& result,
		           int nums1, int nums2) {
		if (nums1 == 3) {
			//���������
			for (uchar i = 16; i >= input.main_value + 1; i--) {
				if (card[i] < nums1) { continue; }
				for (uchar j = 18; j >= 3; j--) {
					if (card[j] < nums2) { continue; }
					if (i == j) { continue; }
					//����ֵ�͸�ֵ�����㹻ʱ��
					porker_hands mid(input.tp, i, j);
					if (card[i] == 4 || card[j] > nums2) //����̫�õ�Ԫ�ط���back
						result.push_back(mid);
					else
						result.push_front(mid);
				}
			}
		}


		//�Ĵ���δ�Ż�
		else if (nums1 == 4) {
			//������Ĵ�
			for (uchar i = input.main_value + 1; i <= 16; i++) {
				if (card[i] < nums1) { continue; }
				for (uchar j = 3; j <= 18; j++) {
					if (j == i) { continue; }
					if (card[j] < nums2) { continue; }
					if (card[j] >= nums2 * 2) {
						//�Ĵ�2�����Ǵ�������ͬ������
						porker_hands mid(input.tp,i,j,j);
						//mid.sig = true;
						result.push_back(mid);
					}

					for (uchar k = j + 1; k <= 18; k++) {
						if (k == i) { continue; }
						if (card[k] < nums2) { continue; }
						//�Ĵ�2,��ͬ������
						porker_hands mid(input.tp,i,j,k);
						result.push_back(mid);
					}
				}
			}
		}
	}

	void get_continue(porker_hands& input,
		              deque<porker_hands>& result,
		              int nums) {
		int cnt = 0;
		for (int i = input.main_value + 1; i <= 14; i++) {
			if (card[i] < nums) {
				cnt = 0;
				continue;
			}
			else {
				//
				cnt += 1;
				if (cnt == input.value1) {
					porker_hands mid(input.tp,i-input.value1+1,input.value1);
					result.push_back(mid);
					cnt -= 1;
				}
			}
		}
	}

	void get_king(deque<porker_hands>& result) {
		if (card[17] == 1 && card[18] == 1) {
			porker_hands mid(porker_hands::king);
			result.push_back(mid);
		}
	}
	void get_all_bomb(deque<porker_hands>& result) {
		//�������е�ը��,������ը
		for (int i = 3; i <= 16; i++) {
			if (card[i] == 4) {
				porker_hands mid(porker_hands::bomb,i);
				result.push_back(mid);
			}
		}
		get_king(result);
	}

	void get_none(deque<porker_hands>& result) {

		porker_hands mid(porker_hands::none);
		result.push_back(mid);
	}

	void get_all_conti(vector<uchar>& sig,
		               deque<porker_hands>& result,
		               int basic_num,
		               uchar nums_) {
		uchar cnt = 1;
		uchar start = 0;
		for (uchar i = 1; i < sig.size(); i++) {
			//˼·:�ҵ����������
			if (sig[i] - sig[i - 1] == 1) {
				//������
				cnt += 1;
			}

			if (sig[i] - sig[i - 1] != 1 || i == sig.size() - 1) {
				//������
				if (cnt >= basic_num) {
					for (uchar ii = basic_num; ii <= cnt; ii++) {
						for (uchar j = start; j <= start + cnt - ii; j++) {
							porker_hands mid(porker_hands::conti, sig[j], ii);
							switch (nums_)
							{
							case 1:
								result.push_front(mid);
								break;
							case 2:
								mid.tp = porker_hands::double_conti;
								result.push_front(mid);
								break;
							default:
								break;
							}
						}
					}
				}

				cnt = 1;
				start = i;
			}
		}
		//cout << cnt << endl;
	}

	void get_all(deque<porker_hands>& result) {
		//�������п��Գ�������
		vector<uchar> sig;
		vector<uchar> doub;
		vector<uchar> tree;
		vector<uchar> four;

		for (uchar i = 3; i <= 18; i++) {
			switch (card[i])
			{
			case 1:
				sig.push_back(i);
				break;

			case 2:
				sig.push_back(i);
				doub.push_back(i);
				break;

			case 3:
				sig.push_back(i);
				doub.push_back(i);
				tree.push_back(i);
				break;

			case 4:
				sig.push_back(i);
				doub.push_back(i);
				tree.push_back(i);
				four.push_back(i);
				break;
			}
		}

		for (auto f_main : four) {
			//�Ĵ�
			for (int i = 0; i < sig.size(); i++) {
				if (sig[i] == f_main) { continue; }
				if (card[sig[i]] >= 2) {
					porker_hands mm(porker_hands::bomb_two,f_main,sig[i],sig[i]);
					result.push_back(mm);
				}

				if (card[sig[i]] == 4) {
					porker_hands mm(porker_hands::bomb_two_pair, 
						            f_main,sig[i],sig[i]);
					result.push_back(mm);
				}

				for (int j = i + 1; j < sig.size(); j++) {
					if (sig[j] == f_main) { continue; }

					porker_hands mm(porker_hands::bomb_two, 
						            f_main, sig[i], sig[j]);
					result.push_back(mm);

					if (card[sig[i]] >= 2 && card[sig[j]] >= 2) {
						porker_hands mm(porker_hands::bomb_two_pair, 
							            f_main, sig[i],sig[j]);
						result.push_back(mm);
					}
				}
			}
		}

		//for (auto t_main : tree) {
		for (int i = tree.size() - 1; i >= 0; i--) {
			//����
			//for (auto s : sig) {
			for (int j = sig.size() - 1; j >= 0; j--) {
				auto t_main = tree[i];
				auto s = sig[j];
				if (s == t_main) { continue; }

				porker_hands mm1(porker_hands::three_one, t_main,s);
				porker_hands mm2(porker_hands::three_two, t_main, s);
				//��Ϊswitch ���
				if (card[t_main]>3) {
					if (card[s] == 1) {
						result.push_back(mm1);
					}
					else {
						result.push_back(mm1);
						result.push_back(mm2);
					}
				}
				else {
					if (card[s] == 1) {
						result.push_front(mm1);
					}

					else if (card[2] == 2) {
						result.push_back(mm1);
						result.push_front(mm2);
					}
					else {
						result.push_back(mm1);
						result.push_back(mm2);
					}
				}
			}
		}

		//for (auto m : doub) {
		for (int i = doub.size() - 1; i >= 0; i--) {
			auto m = doub[i];
			porker_hands mm(porker_hands::two,m);
			if (card[m] == 2) 
				result.push_front(mm);
			else 
				result.push_back(mm);
			
		}

		for (int i = sig.size() - 1; i >= 0; i--) {
			auto m = sig[i];
			porker_hands mm(porker_hands::one, m);
			if (card[m] == 1) 
				result.push_front(mm);
			
			else 
				result.push_back(mm);
			
		}

		for (int i = tree.size() - 1; i >= 0; i--) {
			auto m = tree[i];
			porker_hands mm(porker_hands::three, m);
			result.push_back(mm);
		}

		get_all_conti(sig, result, 5, 1);//˳��
		get_all_conti(doub, result, 3, 2);//����

		for (auto m : four) {
			//ը��
			porker_hands mm(porker_hands::bomb,m);
			result.push_back(mm);
		}

		get_king(result);//��ը

	}

	deque<porker_hands> what_to_deal(porker_hands& input) {
		//���ݶԷ�������з�,���ǿ��е�Ӧ���ֶ�
		//�Ż�:���Ը�Ϊһ�μ���ֻȡһ�ַ���,�����ٶ�,�Ż��ڴ�
		deque<porker_hands> result;

		
		switch (input.tp) {

		case porker_hands::one:
			//��
			get_single(input, result,1);
			break;

		case porker_hands::two:
			//˫
			get_single(input, result, 2);
			break;

		case porker_hands::three:
			//��
			get_single(input, result, 3);
			break;

		case porker_hands::three_one:
			//����һ
			get_bring(input, result,3,1);
			break;
		
		case porker_hands::three_two:
			//������
			get_bring(input, result, 3, 2);
			break;

		case porker_hands::bomb_two:
			//�Ĵ���
			get_bring(input, result, 4, 1);
			break;

		case porker_hands::bomb_two_pair:
			//�Ĵ�����
			get_bring(input, result, 4, 2);
			break;

		case porker_hands::conti:
			//˳��
			get_continue(input, result,1);
			break;

		case porker_hands::double_conti:
			//����
			get_continue(input, result, 2);
			break;

		case porker_hands::bomb:
			//ը��
			get_single(input, result,4);
			get_king(result);
			get_none(result);
			return result;
			break;

		case porker_hands::king:
			//��ը
			get_none(result);
			return result;
			break;

		case porker_hands::none:
			//����
			get_all(result);
			return result;
			break;

		}

		get_all_bomb(result);
		get_none(result);
		return result;
	}

	cards play_cards(porker_hands& cd) {
		//����
		cards result = *this;

		switch (cd.tp)
		{

		case porker_hands::one:
			result.card[cd.main_value] -= 1;
			result.nums -= 1;
			break;

		case porker_hands::two:
			result.card[cd.main_value] -= 2;
			result.nums -= 2;
			break;

		case porker_hands::three:
			result.card[cd.main_value] -= 3;
			result.nums -= 3;
			break;

		case porker_hands::three_one:
			result.card[cd.main_value] -= 3;
			result.card[cd.value1] -= 1;
			result.nums -=4;
			break;

		case porker_hands::three_two:
			result.card[cd.main_value] -= 3;
			result.card[cd.value1] -= 2;
			result.nums -= 5;
			break;

		case porker_hands::bomb_two:
			result.card[cd.main_value] -= 4;
			result.card[cd.value1] -= 1;
			result.card[cd.value2] -= 1;
			result.nums -= 6;
			break;

		case porker_hands::bomb_two_pair:
			result.card[cd.main_value] -= 4;
			result.card[cd.value1] -= 2;
			result.card[cd.value2] -= 2;
			result.nums -= 8;
			break;

		case porker_hands::conti:
			for (int i = cd.main_value; i <= cd.main_value + cd.value1 - 1; i++) {
				result.card[i] -= 1;
				result.nums -= 1;
			}
			break;
		
		case porker_hands::double_conti:
			for (int i = cd.main_value; i <= cd.main_value + cd.value1 - 1; i++) {
				result.card[i] -= 2;
				result.nums -= 2;
			}
			break;

		case porker_hands::bomb:
			result.card[cd.main_value] -= 4;
			result.nums -= 4;
			break;

		case porker_hands::king:
			result.card[17] -= 1;
			result.card[18] -= 1;
			result.nums -= 2;
			break;
		}
		return result;
	}
};
