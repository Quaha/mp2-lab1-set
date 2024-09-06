// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <cmath>

TSet::TSet(int mp) : BitField(0)
{   
    if (mp < 0) throw "Wrong TSet max power!";

    this->MaxPower = mp;
    this->BitField = TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(0)
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(0)
{
    this->MaxPower = bf.GetLength();
    this->BitField = bf;
}

TSet::operator TBitField()
{   
    return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{   
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return (this->BitField.GetBit(Elem) == 1);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{   
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{   
    return (this->MaxPower == s.MaxPower && this->BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{   
    TSet result(0);
    
    result.MaxPower = max(this->MaxPower, s.MaxPower);
    result.BitField = this->BitField | s.BitField;

    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{   
    TSet result = *this;
    result.InsElem(Elem);

    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet result = *this;
    result.DelElem(Elem);

    return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet result(0);

    result.MaxPower = max(this->MaxPower, s.MaxPower);
    result.BitField = this->BitField & s.BitField;

    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result = *this;
    result.BitField = ~result.BitField;

    return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    for (int i = 0; i < s.MaxPower; i++) {
        char bit;
        cin >> bit;

        if (bit == '1') {
            s.InsElem(i);
        }
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{   
    for (int i = 0; i < s.MaxPower; i++) {
        std::cout << s.IsMember(i);
    }
    return ostr;
}
