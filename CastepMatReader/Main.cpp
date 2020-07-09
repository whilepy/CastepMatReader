#include "MatReader.h"

 
int main() {
	char filename[30],output[30];
	int nk, nev, ns;
	output[0] = '\0';
	std::cout << "请输入文件名(相对路径与绝对路径皆可):" << std::endl;
	std::cin >> filename;
	std::cout << "请输入k点数 本征值个数 自旋数(对照bands文件,空格分隔):" << std::endl;
	std::cin >> nk >> nev >> ns;
	MatReader mr(filename, nk, nev, ns);
	std::cout << "请输入输出文件名:" << std::endl;
	std::cin >> output;
	bool a = false;
	a = mr.OutputMat(output);
	if (a) 
	{
		std::cout << "成功导出!" << std::endl;
	}
	else 
	{
		std::cout << "导出失败!" << std::endl;
	}
	return 0;
}