#include "ABase.h"
#include "Vector.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace {

void PrintDivider(const string& strTitle)
{
	cout << "\n========================================" << endl;
	cout << "  " << strTitle << endl;
	cout << "========================================" << endl;
}

void PrintSubDivider(const string& strLabel)
{
	cout << "\n--- " << strLabel << " ---" << endl;
}

void PrintVectorState(const char* strTag, size_t iSize, size_t iCapacity)
{
	cout << "[" << strTag << "] size: " << iSize << ", capacity: " << iCapacity << endl;
}

void PrintValues(const char* strTag, const vector<ABase>& vStd)
{
	cout << "[" << strTag << "] values: ";
	for (size_t i = 0; i < vStd.size(); ++i)
	{
		cout << vStd[i].GetValue();
		if (i + 1 < vStd.size())
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void PrintValues(const char* strTag, Vector<ABase>& vMy)
{
	cout << "[" << strTag << "] values: ";
	for (size_t i = 0; i < vMy.size(); ++i)
	{
		cout << vMy[static_cast<int>(i)].GetValue();
		if (i + 1 < vMy.size())
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void ComparePushBack()
{
	PrintDivider("push_back (copy / move)");

	PrintSubDivider("std::vector<ABase>");
	{
		vector<ABase> vStd;
		vStd.reserve(16);
		PrintVectorState("init", vStd.size(), vStd.capacity());

		ABase aLhs(10);
		vStd.push_back(aLhs);
		vStd.push_back(ABase(20));
		vStd.push_back(std::move(aLhs));

		PrintVectorState("after push", vStd.size(), vStd.capacity());
		PrintValues("std", vStd);
	}

	PrintSubDivider("Vector<ABase>");
	{
		Vector<ABase> vMy;
		PrintVectorState("init", vMy.size(), vMy.capacity());

		ABase aLhs(10);
		vMy.push_back(aLhs);
		vMy.push_back(ABase(20));
		vMy.push_back(std::move(aLhs));

		PrintVectorState("after push", vMy.size(), vMy.capacity());
		PrintValues("my", vMy);
	}
}

void CompareEmplaceBack()
{
	PrintDivider("emplace_back");

	PrintSubDivider("std::vector<ABase>");
	{
		vector<ABase> vStd;
		vStd.reserve(16);
		vStd.emplace_back(100);
		vStd.emplace_back(200);
		vStd.emplace_back(ABase(300));
		ABase c(400);
		vStd.emplace_back();
		vStd.emplace_back(c);
		PrintVectorState("after emplace", vStd.size(), vStd.capacity());
		PrintValues("std", vStd);
	}

	PrintSubDivider("Vector<ABase>");
	{
		Vector<ABase> vMy;
		vMy.emplace_back(100);
		vMy.emplace_back(200);
		vMy.emplace_back(ABase(300));
		ABase c(400);
		vMy.emplace_back();
		vMy.emplace_back(c);
		PrintVectorState("after emplace", vMy.size(), vMy.capacity());
		PrintValues("my", vMy);
	}
}

void CompareGrowth()
{
	PrintDivider("growth / reallocate (17x push_back)");

	PrintSubDivider("std::vector<ABase>");
	{
		vector<ABase> vStd;
		vStd.reserve(16);
		for (int i = 1; i <= 17; ++i)
		{
			vStd.push_back(ABase(i));
		}
		PrintVectorState("after growth", vStd.size(), vStd.capacity());
		PrintValues("std", vStd);
	}

	PrintSubDivider("Vector<ABase>");
	{
		Vector<ABase> vMy;
		for (int i = 1; i <= 17; ++i)
		{
			vMy.push_back(ABase(i));
		}
		PrintVectorState("after growth", vMy.size(), vMy.capacity());
		PrintValues("my", vMy);
	}
}

void ComparePopBack()
{
	PrintDivider("pop_back");

	PrintSubDivider("std::vector<ABase>");
	{
		vector<ABase> vStd;
		vStd.reserve(16);
		vStd.push_back(ABase(1));
		vStd.push_back(ABase(2));
		vStd.push_back(ABase(3));
		cout << "before pop_back" << endl;
		PrintValues("std", vStd);

		vStd.pop_back();
		cout << "after 1x pop_back" << endl;
		PrintVectorState("std", vStd.size(), vStd.capacity());
		PrintValues("std", vStd);
	}

	PrintSubDivider("Vector<ABase>");
	{
		Vector<ABase> vMy;
		vMy.push_back(ABase(1));
		vMy.push_back(ABase(2));
		vMy.push_back(ABase(3));
		cout << "before pop_back" << endl;
		PrintValues("my", vMy);

		vMy.pop_back();
		cout << "after 1x pop_back" << endl;
		PrintVectorState("my", vMy.size(), vMy.capacity());
		PrintValues("my", vMy);
	}
}

void CompareClear()
{
	PrintDivider("clear");

	PrintSubDivider("std::vector<ABase>");
	{
		vector<ABase> vStd;
		vStd.reserve(16);
		vStd.push_back(ABase(1));
		vStd.push_back(ABase(2));
		cout << "before clear" << endl;
		PrintVectorState("std", vStd.size(), vStd.capacity());

		vStd.clear();
		cout << "after clear" << endl;
		PrintVectorState("std", vStd.size(), vStd.capacity());
	}

	PrintSubDivider("Vector<ABase>");
	{
		Vector<ABase> vMy;
		vMy.push_back(ABase(1));
		vMy.push_back(ABase(2));
		cout << "before clear" << endl;
		PrintVectorState("my", vMy.size(), vMy.capacity());

		vMy.clear();
		cout << "after clear" << endl;
		PrintVectorState("my", vMy.size(), vMy.capacity());
	}
}

} // namespace

int main()
{
	cout << "STL vector vs MySTL Vector comparison (ABase logs copy/move)" << endl;

	ComparePushBack();
	CompareEmplaceBack();
	CompareGrowth();
	ComparePopBack();
	CompareClear();

	cout << "\nDone." << endl;
	return 0;
}
