#include "solve_game.h"
#include<sstream>
#include<fstream>

vector<uchar> split(string s,const char flag) {
	vector<uchar> result;
	istringstream iss(s);

	string temp;

	while (getline(iss, temp, flag)) {
		result.push_back(stoi(temp));
	}
	return result;
}

int main() {

	//�Ż�:�ڴ�����:����ɾ������������ӽڵ�,����ڴ��������
	//�ٶ�:��������һ��ѡ��,���ȿ�������//���Ż�
	//     һ�μ���ֻȡһ���ڵ�

	ifstream file_read;
	file_read.open("������.txt", ios::in);

	if (!file_read) {
		cout << "box.txt dose not exist!" << endl;
		system("pause");
		return 100;
	}

	string x;
	string y;
	getline(file_read, x);
	getline(file_read, y);
	file_read.close();
	

	//cout << "������������(�÷ֺŸ���):";
	//cin >> x;
	//cout << "�����������(�÷ֺŸ���):";
	//cin >> y;

	vector<uchar>xxx = split(x, ';');
	vector<uchar>yyy = split(y, ';');
	solve_game t(xxx, yyy);
	t.compute();
	t.inter_active();
	system("pause");


}



//�ȼ����ظ����жϹ���,�������Ƿ�������,�ٽ���ϸ���Ż�