// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_prime_numbers.cpp - Copyright (c) Гергель В.П. 20.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Тестирование битового поля и множества

#include <iomanip>

// #define USE_SET // Использовать класс TSet,
                // закоментировать, чтобы использовать битовое поле

#ifndef USE_SET // Использовать класс TBitField

#include "tbitfield.h"



int main()
{
    TBitField a(10);
    cout << "a(10): " << a << endl;

    a.SetBit(0); a.SetBit(3); a.SetBit(5);
    cout << "Set(0,3,5): " << a << endl;
    a.ClrBit(5);
    cout << "Clr(5): " << a << endl;
    cout << "Get(0,3,5): " << a.GetBit(0) << a.GetBit(3) << a.GetBit(5) << endl;

    TBitField b(a);
    b.ClrBit(0);
    cout << "b: " << b << " | a: " << a << endl;

    TBitField c(4);
    c = a;
    cout << "c: " << c << endl;

    const int B = 8 * sizeof(TELEM);
    TBitField e(B + 2);
    e.SetBit(B - 1); e.SetBit(B);
    cout << "e: " << e << endl;

    // Проверка ввода
    TBitField d(10);
    cout << "Enter 10 bits (0/1): ";
    cin >> d;
    cout << "d: " << d << endl;
    cout << "GetBit(0)=" << d.GetBit(0)
        << " GetBit(9)=" << d.GetBit(9) << endl;

    try { a.SetBit(-1); }
    catch (...) { cout << "SetBit(-1) OK\n"; }
    try { a.ClrBit(10); }
    catch (...) { cout << "ClrBit(10) OK\n"; }
    try { TBitField bad(0); }
    catch (...) { cout << "TBitField(0) OK\n"; }
    return 0;
}




/*int main()
{
  int n, m, k, count;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки битового поля" << endl;
  cout << "             Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TBitField s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.SetBit(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если m в s, удаление кратных
    if (s.GetBit(m))
      for (k = 2 * m; k <= n; k += m)
        if (s.GetBit(k))
          s.ClrBit(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.GetBit(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;
}
*/
#else

#include "tset.h"

int main()
{
  int n, m, k, count;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки множества" << endl;
  cout << "              Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TSet s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.InsElem(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если м в s, удаление кратных
    if (s.IsMember(m))
      for (k = 2 * m; k <= n; k += m)
       if (s.IsMember(k))
         s.DelElem(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.IsMember(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;
}

#endif