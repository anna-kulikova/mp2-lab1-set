// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField t(BitField);
	return t;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	int t = BitField.GetBit(Elem);
	return t;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 0;
	if (BitField != s.BitField)
		return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 1;
	if (BitField != s.BitField)
		return 1;
	return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField t = BitField | s.BitField;
	TSet un(t);
	return un;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet s(BitField);
	s.BitField.SetBit(Elem);
	return s;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet s(BitField);
	s.BitField.ClrBit(Elem);
	return s;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField t = BitField & s.BitField;
	TSet in(t);
	return in;
}

TSet TSet::operator~(void) // дополнение
{
	TSet s(~BitField);
	return s;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	char symbol;
	do
		istr >> symbol;
	while (symbol != '{');
	do
	{
		istr >> i;
		s.InsElem(i);
		do
			istr >> symbol;
		while ((symbol != ',') && (symbol != '}'));
	} 
	while (symbol != '}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	char symbol = ' ';
	ostr << "{";
	int n = s.GetMaxPower();
	for (int i = 0; i < n; i++)
		if (s.IsMember(i))
		{
			ostr << symbol << ' ' << 1;
			symbol = ',';
		}
	return ostr;
}
