// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw
		exception("Length must be positive");
	BitLen = len;
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen))
		throw
		exception("Out of borders");
	return n / (sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof (TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))
		throw
		exception("Out of borders");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
		throw
		exception("Out of borders");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
		throw
		exception("Out of borders");
	TELEM bit = pMem[GetMemIndex(n)] & GetMemMask(n);
	return bit >> (n % (sizeof (TELEM) * 8));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[]pMem;
		pMem = new TELEM[MemLen];
		if (pMem != NULL)
		{
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
	}
		return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)
	  return 0;
  for (int i = 0; i < MemLen; i++)
  {
	  if ((pMem[i]) != (bf.pMem[i]))
		  return 0;
  }  
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i = 0;
	int n = bf.BitLen;
	if (n < BitLen)
		n = BitLen;
	TBitField t(n);
	for (; i < MemLen; i++)
		t.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		t.pMem[i] |= bf.pMem[i];
	return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i = 0;
	int n = BitLen;
	if (n < bf.BitLen)
		n = bf.BitLen;
	TBitField t(n);
	for (i; i < MemLen; i++)
		t.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		t.pMem[i] &= bf.pMem[i];
	return t;
}

TBitField TBitField::operator~(void) // отрицание
{
	int n = BitLen;
	int i = 0;
	TBitField t(n);
	for (; i < MemLen - 1; i++)
		t.pMem[i] = ~pMem[i];
	TELEM k = 0;
	for (i = 0; i < (BitLen % 32); i++)
		k |= GetMemMask(i);
	t.pMem[MemLen - 1] = (~pMem[MemLen - 1]) & k;
	return t;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char digital;
	do
		istr >> digital;
	while (digital != ' ');
	while (1)
	{
		if (digital == '0')
			bf.ClrBit(i++);
		else if (digital == '1')
			bf.SetBit(i++);
		else
			break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i))
			ostr << "1";
		else
			ostr << "0";
	}
	return ostr;
}
