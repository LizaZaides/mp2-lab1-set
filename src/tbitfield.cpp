// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <algorithm>

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len <= 0) throw "Длина битового поля должна быть положительной";
    BitLen = len;
    MemLen = (BitLen+31) / 32; 
    pMem = new TELEM[MemLen]; 
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0;i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / ((sizeof(TELEM)) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM res = 1;
    int idBit = n % 32;
    res <<= idBit;
    return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return FAKE_INT;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) throw ("неверное значение");
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[id] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) throw ("неверное значение");
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[id] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    int res = pMem[id];
    res &= mask;
    if (res == 0) return 0;
    else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bf.BitLen != BitLen) return false;
    for (int i = 0; i < MemLen - 1; i++) {
        if (pMem[i] != bf.pMem[i]) return false;
    }
    for (int i = (MemLen - 1) * sizeof(TELEM) * 8;i < BitLen;i++) {
        if (bf.GetBit(i) != GetBit(i)) return false;
    }
    return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int maxLen = BitLen;
    if (bf.BitLen > maxLen) { maxLen = bf.BitLen; }
    TBitField result(maxLen);
    for (int i = 0; i < maxLen; i++)
    {
        int bit1 = 0;
        int bit2 = 0;
        if (i < BitLen) { bit1 = GetBit(i); }
        if (i < bf.BitLen) { bit2 = bf.GetBit(i); }
        if (bit1 || bit2) { result.SetBit(i); }
    }

    return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int maxLen = BitLen;
    if (bf.BitLen > maxLen) { maxLen = bf.BitLen; }

    TBitField result(maxLen);

    for (int i = 0; i < maxLen; i++)
    {
        int bit1 = 0;
        int bit2 = 0;
        if (i < BitLen) { bit1 = GetBit(i); }
        if (i < bf.BitLen) { bit2 = bf.GetBit(i); }
        if (bit1 && bit2) { result.SetBit(i); }
    }

    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res = *this;
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~res.pMem[i];
    }
    int bits_last = BitLen % (sizeof(TELEM) * 8);
    if (bits_last != 0) {
        int bits_trash = (sizeof(TELEM) * 8) - bits_last;
        TELEM mask = ~(TELEM)0 >> bits_trash;
        res.pMem[MemLen - 1] &= mask;
    }
    return res;
}
// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char tmp;
    istr >> tmp;
    int  i = 0;
    while (tmp == '1' || tmp == '0') {
        if (tmp == '0') bf.ClrBit(i);
        else bf.SetBit(i);
        i++;
        istr >> tmp;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
