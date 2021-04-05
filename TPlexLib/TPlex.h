#pragma once
#include "TBase.h"
#include "TPoint.h"
#include "TLine.h"
#include "TSquare.h"
#include "TCanvas.h"
#include <string>
#include <cstring>

class TPlex : public TBase {
protected:
	TBase* left;
	TBase* right;
public:
	TPlex();
	TPlex(TPoint* a, TPoint* b);
	TPlex(char* s);
	TPlex(const TPlex& p);

	virtual void Print();
	virtual double GetVal(int i);
	virtual void SetVal(double val, int i);
	virtual double& operator[](char* name);
	virtual double& operator[](int i);

	virtual TBase* GetChild(int i);
	virtual void SetChild(TBase* c, int i);
	virtual TBase* PrintAll(TBase* p);
	TBase* GetLeft();
	TBase* GetRight();

	TPlex* GetLeftPlex();
	TPlex* GetRightPlex();

	void SetLeft(TBase* x);
	void SetRight(TBase* x);
	bool AddLine(TPoint* a, TPoint* b);

	virtual int GetChildCount()
	{
		return 2;
	}

	virtual TBase* Clone();
};

TPlex::TPlex() 
{
	left = new TPoint();
	right = new TPoint();
}

TPlex::TPlex(char* s) 
{
	int numbers = 0;
	int cc = strlen(s);
	int j = 0;
	int num = 0;


	for (int i = 0; i < cc; i++)
	{
		if (s[i] != ' ' && s[i] != ',')
		{
			j = i + 1;
			while (s[j] != ' ' && s[j] != ',')
			{
				j++;
			}

			i = j + 1;
			numbers++;
		}

	}

	if (numbers % 2 != 0 && numbers < 4)
	{
		throw -1;
	}

	double* array = new double[numbers]; 
	std::string n = "";
    j = 0;
    numbers = 0;

	for (int i = 0; i < cc; i++)
	{
		if (s[i] != ' ' && s[i] != ',')
		{
			n += s[i];
			j = i + 1;
			while (s[j] != ' ' && s[j] != ',')
			{
				n += s[j];
				num = atoi(n.c_str());
				j++;
			}

			array[numbers] = num;
			i = j + 1;
			n = "";
			numbers++;
		}
	}

	left = new TPoint(array[0], array[1]);
	right = new TPoint(array[2], array[3]);

	for (int i = 4; i < numbers; i++)
	{
		TPoint* temp_left = new TPoint(array[i - 2], array[i - 1]);
		TPoint* temp_right = new TPoint(array[i], array[i + 1]);

		this->AddLine(temp_left, temp_right);
		i++;
	}
}

TPlex::TPlex(TPoint* a, TPoint* b) 
{
	if (a != NULL)
		left = a;

	if (b != NULL)
		right = b;
}

TPlex::TPlex(const TPlex& p) 
{
	left = p.left->Clone();
	right = p.right->Clone();
}

void TPlex::Print()
{
	PrintAll(0);
};

TBase* TPlex::PrintAll(TBase* p)
{
	TBase* p1 = left->PrintAll(0);
	TBase* p2 = right->PrintAll(0);
	std::cout << "Plex: " << std::endl;
	p1->Print();
	p2->Print();
	std::cout << std::endl;
	return p2;
}

double TPlex::GetVal(int i) {
	throw - 1;
}

void TPlex::SetVal(double val, int i) {
	throw - 1;
}

double& TPlex::operator[](char* name) {
	throw - 1;
}

double& TPlex::operator[](int i) {
	throw - 1;
}

TBase* TPlex::GetChild(int i) {
	if (i == 0)
		return left;
	else if (i == 1)
		return right;
	else
		throw - 1;
}

void TPlex::SetChild(TBase* c, int i)
{
	if (i == 0)
		left = c;
	else if (i == 1)
		right = c;
	else
		throw - 1;
}

TBase* TPlex::GetLeft()
{
	return left;
}
TBase* TPlex::GetRight()
{
	return right;
}

TPlex* TPlex::GetLeftPlex()
{
	return dynamic_cast<TPlex*>(left);
}
TPlex* TPlex::GetRightPlex()
{
	return dynamic_cast<TPlex*>(right);
}

void TPlex::SetLeft(TBase* x)
{
	left = x;
}
void TPlex::SetRight(TBase* x)
{
	right = x;
}
bool TPlex::AddLine(TPoint* a, TPoint* b)
{
	TPlex* l = GetLeftPlex();
	bool isAdd = false;
	if (l != 0)
		isAdd = l->AddLine(a, b);
	else
	{
		if (left == a)
		{
			left = new TPlex(b, a);
			return true;
		}
	}
	if (isAdd)
		return isAdd;

	TPlex* r = GetRightPlex();
	isAdd = false;
	if (r != 0)
		isAdd = r->AddLine(a, b);
	else
	{
		if (right->GetVal(0) == a->GetX0() && right->GetVal(1) == a->GetX1())
		{
			right = new TPlex(b, a);
			return true;
		}
	}
	return isAdd;
}

TBase* TPlex::Clone()
{
	return new TPlex(*this);
}
