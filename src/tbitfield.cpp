// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>

TBitField::TBitField(int len)
{
    if (len < 0) throw "Wrong TBitField size!";
    if (len == 0) return;

    int type_size = sizeof(TELEM) * 8;

    this->BitLen = len;
    this->MemLen = (len + type_size - 1) / type_size;

    this->pMem = new TELEM[this->MemLen];

    for (int i = 0; i < this->MemLen; i++) {
        this->pMem[i] = static_cast<TELEM>(0);
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;

    this->pMem = new TELEM[this->MemLen];
    for (int i = 0; i < this->MemLen; i++) {
        this->pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] this->pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int type_size = sizeof(TELEM) * 8;

    return n / (type_size);
}

TELEM TBitField::GetMemMask(const int k) const // битовая маска для бита k (k < type_size)
{
    return static_cast<TELEM>(1ll << k);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= this->BitLen || n < 0) throw "TBitField index out of range!";

    int type_size = sizeof(TELEM) * 8;
    this->pMem[GetMemIndex(n)] |= GetMemMask(n % type_size);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= this->BitLen || n < 0) throw "TBitField index out of range!";

    int type_size = sizeof(TELEM) * 8;
    if (this->GetBit(n)) {
        this->pMem[GetMemIndex(n)] ^= GetMemMask(n % type_size);
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= this->BitLen || n < 0) throw "TBitField index out of range!";

    int type_size = sizeof(TELEM) * 8;
    bool result = static_cast<bool>(this->pMem[GetMemIndex(n)] & GetMemMask(n % type_size));
    return result;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;

    TELEM* pTempMem = new TELEM[this->MemLen];
    for (int i = 0; i < this->MemLen; i++) {
        pTempMem[i] = bf.pMem[i];
    }

    delete[] this->pMem;
    this->pMem = pTempMem;

    return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (this->BitLen != bf.BitLen) return false;

    for (int i = 0; i < this->MemLen; i++) {
        if (this->pMem[i] != bf.pMem[i]) return false;
    }
    return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{   
    TBitField result(0);
    if (this->BitLen > bf.BitLen) {
        result = *this;
    }
    else {
        result = bf;
    }

    int size = min(this->MemLen, bf.MemLen);
    for (int i = 0; i < size; i++) {
        result.pMem[i] = this->pMem[i] | bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{   
    TBitField result(0);
    if (this->BitLen > bf.BitLen) {
        result = *this;
    }
    else {
        result = bf;
    }

    int size = min(this->MemLen, bf.MemLen);
    for (int i = 0; i < size; i++) {
        result.pMem[i] = this->pMem[i] & bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(this->BitLen);

    int type_size = sizeof(TELEM) * 8;
    TELEM mask = static_cast<TELEM>(((1ll << (type_size - 1)) - 1) | (1ll << (type_size - 1)));

    for (int i = 0; i < result.MemLen; i++) {
        result.pMem[i] = this->pMem[i] ^ mask;
    }

    if (this->BitLen % type_size != 0 && this->BitLen > 0) {
        int signifier = BitLen % type_size;
        TELEM mask = static_cast<TELEM>((1ll << signifier) - 1);
        result.pMem[result.MemLen - 1] &= mask;
    }
    return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{   
    for (int i = 0; i < bf.BitLen; i++) {
        char bit;
        cin >> bit;

        if (bit == '1') {
            bf.SetBit(i);
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{   
    for (int i = 0; i < bf.BitLen; i++) {
        cout << bf.GetBit(i);
    }
    return ostr;
}
