//---------------------------------------------------------------------------

#pragma hdrstop

#include "uPN.h"
#include <stack>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
typedef struct _Notation {
	UnicodeString Value;
	int RelPrior, StackPrior, Rank;
} Notation;
//---------------------------------------------------------------------------
Notation MakeNotation(UnicodeString Value, int RelPrior, int StackPrior, int Rank)
{
	Notation Item;
	Item.Value = Value;
	Item.RelPrior = RelPrior;
	Item.StackPrior = StackPrior;
	Item.Rank = Rank;
	return Item;
}
Notation* ParseInputStr(UnicodeString Str, int *size)
{
	Notation* PostFix = new Notation[*size];
	int i = 1, Current = 0;
	while (i <= *size)
	{
		if (UnicodeString(Str[i]) == "+" || UnicodeString(Str[i]) == "-") {
			PostFix[Current++] = MakeNotation(Str[i], 1, 2, -1);
		} else if (UnicodeString(Str[i]) == "*" || UnicodeString(Str[i]) == "/") {
			PostFix[Current++] = MakeNotation(Str[i], 3, 4, -1);
		} else if (UnicodeString(Str[i]) == "^") {
			PostFix[Current++] = MakeNotation(Str[i], 6, 5, -1);
		} else if (UnicodeString(Str[i]) == "(") {
			PostFix[Current++] = MakeNotation(Str[i], 9, 0, -2);
		} else if (UnicodeString(Str[i]) == ")") {
			PostFix[Current++] = MakeNotation(Str[i], 0, -2, -2);
		} else if ((UnicodeString(Str[i]) >= "0" && UnicodeString(Str[i]) <= "9")
		  || UnicodeString(Str[i]) == ",")
		{
			UnicodeString Value = "";
			while (i <= *size && ((UnicodeString(Str[i]) >= "0" &&
			  UnicodeString(Str[i]) <= "9") || UnicodeString(Str[i]) == ","))
			{
				Value = Value + UnicodeString(Str[i]);
				i++;
			}
			i--;
			PostFix[Current++] = MakeNotation(Value, 7, 8, 1);
		}
        i++;
	}
	Notation *Temp = new Notation[Current];
	for (int i = 0; i < Current; i++) {
		Temp[i] = PostFix[i];
	}
    *size = Current;
	return Temp;
}
Notation* StackConversion(Notation *PostFix, int *size) {
	int Current = 0;
	Notation* Result = new Notation[*size];
	stack<Notation> Stack;
	for (int i = 0 ; i < *size; i++) {
		if (Stack.empty()) {
			Stack.push(PostFix[i]);
		} else if (PostFix[i].RelPrior > Stack.top().StackPrior) {
			Stack.push(PostFix[i]);
		} else if (PostFix[i].Value == ")") {
			while (Stack.top().Value != "(")
			{
				Result[Current++] = Stack.top();
				Stack.pop();
            }
			Stack.pop();
		} else {
			while (!Stack.empty() &&
			  (PostFix[i].RelPrior <= Stack.top().StackPrior)) {
				Result[Current++] = Stack.top();
				Stack.pop();
			}
			Stack.push(PostFix[i]);
        }
	}
	while (!Stack.empty()) {
		Result[Current++] = Stack.top();
		Stack.pop();
	}
	Notation* Temp = new Notation[Current];
	for (int i = 0; i < Current; i++) {
		Temp[i] = Result[i];
	}
	*size = Current;
	return Temp;
}
Currency Calculate(Notation* PostFix, int size) {
	stack<Currency> Stack;
	for (int i = 0; i < size; i++) {
		if (PostFix[i].Rank == 1) {
			Stack.push(StrToCurr(PostFix[i].Value));
		} else {
			Currency a = Stack.top();
			Stack.pop();
			Currency b = Stack.top();
			Stack.pop();
			if (PostFix[i].Value == "+") {
				a = b + a;
			} else if (PostFix[i].Value == "-") {
				a = b - a;
			} else if (PostFix[i].Value == "*") {
				a = b * a;
			} else if (PostFix[i].Value == "/") {
				a = b / a;
			} else if (PostFix[i].Value == "^") {
				a = (Currency) pow(b, (int) a);
			}
			Stack.push(a);
        }
	}
	return Stack.top();
}
Currency GetValue(UnicodeString Str)
{
	int size = Str.Length();
	Notation *PostFix = new Notation[size];
	PostFix = ParseInputStr(Str, &size);
	PostFix = StackConversion(PostFix, &size);
	return Calculate(PostFix, size);
}