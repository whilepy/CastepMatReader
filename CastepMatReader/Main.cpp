#include "MatReader.h"

 
int main() {
	char filename[30],output[30];
	int nk, nev, ns;
	output[0] = '\0';
	std::cout << "�������ļ���(���·�������·���Կ�):" << std::endl;
	std::cin >> filename;
	std::cout << "������k���� ����ֵ���� ������(����bands�ļ�,�ո�ָ�):" << std::endl;
	std::cin >> nk >> nev >> ns;
	MatReader mr(filename, nk, nev, ns);
	std::cout << "����������ļ���:" << std::endl;
	std::cin >> output;
	bool a = false;
	a = mr.OutputMat(output);
	if (a) 
	{
		std::cout << "�ɹ�����!" << std::endl;
	}
	else 
	{
		std::cout << "����ʧ��!" << std::endl;
	}
	return 0;
}