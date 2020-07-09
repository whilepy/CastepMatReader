#ifndef MATREADER_H
#define MATREADER_H

#include<stddef.h>
#include<fstream>
#include<iostream>


class MatReader 
{
public:
	unsigned int numKpoint;
	unsigned int numEigenvalues;
	unsigned int numSpinComponents;
private:
	int length;
	int len;
	int numElemt;
	char* charBuffer;
	char* reverseBuffer;
	double* doubleBuffer;
public:
	MatReader(const char* filename, unsigned int nk, unsigned int nev, unsigned int ns):
		numKpoint(nk),
		numEigenvalues(nev),
		numSpinComponents(ns),
		charBuffer(NULL),
		reverseBuffer(NULL),
		doubleBuffer(NULL),
		length(0),
		len(0),
		numElemt(0)
	{
		std::ifstream ifs("Si_Optics.cst_ome", std::ios::binary | std::ios::in);
		if (!ifs)
		{
			std::cerr << "打开文件失败!";
			throw;
		}
		ifs.seekg(0, std::ios::end);
		length = ifs.tellg();
		char* charBuffer = new char[length];
		ifs.seekg(0, std::ios::beg);
		ifs.read(charBuffer, length);
		ifs.close();
		len = numKpoint * numEigenvalues * numEigenvalues * 3 * numSpinComponents * 2 * sizeof(double);
		char* reverseBuffer = new char[len];
		numElemt = len / sizeof(double);
		if (!DocInspect()) 
		{
			std::cerr << "文件与参数不符!";
			throw;
		}
		int index = 0;
		int i = 0;
		for (i = length - 1; i >= 0; --i)
		{
			int r = i % (3 * sizeof(double));
			if (r > 3 && r < 20)
			{
				reverseBuffer[index] = charBuffer[i];
				index++;
			}
		}
		doubleBuffer = (double*)reverseBuffer;
	}
	~MatReader() 
	{
		if (charBuffer != NULL) 
		{
			delete[] charBuffer;
		}
		if (reverseBuffer != NULL)
		{
			delete[] reverseBuffer;
		}
		if (doubleBuffer != NULL) 
		{
			delete[] doubleBuffer;
		}
	}
	bool OutputMat(const char* filename = "output.csv") 
	{
		if (doubleBuffer == NULL) 
		{
			return false;
		}
		std::ofstream ofs(filename);

		if (!ofs)
		{
			std::cerr << "保存文件失败！";
			return false;
		}
		int i = 0;
		for (i = 0; i < numElemt; ++i)
		{
			int r = numEigenvalues * numEigenvalues * 3 * numSpinComponents * 2;
			if (i % r == 0)
			{
				/*ofs << std::endl;
				ofs << "\t\t\t----------------------第" << i / r + 1 << "个k点---------------------" << std::endl;*/
				ofs << "\n";
				ofs << "第" << i / r + 1 << "个k点\n";
			}
			if (i % (r / numSpinComponents) == 0)
			{
				/*ofs << "\t\t\t\t=======自旋为" << i / (r / numSpinComponents) % 1 << "========" << std::endl;*/
				ofs << "自旋为" << i / (r / numSpinComponents) % 1 << "\n";
			}
			if (i % (r / numSpinComponents / 3) == 0)
			{
				/*ofs << std::endl;
				ofs << "\t\t\t\t*********index = " << i / (r / numSpinComponents / 3) % 3 + 1 << "********" << std::endl;*/
				ofs << "\n";
				ofs << "index = " << i / (r / numSpinComponents / 3) % 3 + 1 << "\n";
			}
			if (i % (r / numSpinComponents / 3 / numEigenvalues) == 0)
			{
				/*ofs << std::endl;*/
				ofs << "\n";
			}
			if (i % 2 == 0)
			{
				ofs << doubleBuffer[i] << "i";
			}
			else
			{
				if (doubleBuffer[i] >= 0)
				{
					ofs << "+";
				}
				/*ofs << doubleBuffer[i] << "\t\t\t";*/
				ofs << doubleBuffer[i] << ",";
			}
		}
		ofs.close();
		return true;
	}
private:
	bool DocInspect() 
	{
		if (numElemt == 0) 
		{
			return false;
		}
		if (numElemt / 2 * 24 == length) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

};






#endif // !MATREADER_H
