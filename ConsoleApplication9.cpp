#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include"Stopwatch-master/include/stopwatch/Stopwatch.hpp"

using namespace std;

class verylong
{
    vector<int> n;
public:
    verylong();
    ~verylong();
    friend ostream& operator<<(ostream& out, const verylong& f);
    verylong& operator=(const verylong f);
    bool operator==(const verylong& f);
    bool operator!=(const verylong& f);
    bool operator>(const verylong& f);
    bool operator<(const verylong& f);
    bool operator>=(const verylong& f);
    bool operator<=(const verylong& f);
    verylong operator-(const verylong& f);
    friend verylong operator%(verylong& f1, verylong& f2);
    verylong del2();
    verylong Umn2();
    void genofnum(int k);
    friend verylong Eqlide(verylong f1, verylong f2);
    friend verylong Binary(verylong f1, verylong f2);
};

verylong::verylong()
{

}

verylong::~verylong()
{
    n.clear();
}

ostream& operator<<(ostream& out, const verylong& f)
{
    for (int i = 0; i < f.n.size(); i++)
    {
        out << f.n[i];
    }

    return out;
}

verylong& verylong::operator=(verylong f)
{
    n.clear();
    for (int i = 0; i < f.n.size(); i++)
    {
        n.push_back(f.n[i]);
    }

    return *this;
}

bool verylong::operator==(const verylong& f)
{
    if (n.size() != f.n.size()) { return false; }

    for (int i = 0; i < n.size(); i++)
    {
        if (n[i] != f.n[i]) { return false; }
    }

    return true;
}

bool verylong::operator!=(const verylong& f)
{
    if (n.size() != f.n.size()) { return true; }

    for (int i = 0; i < n.size(); i++)
    {
        if (n[i] != f.n[i]) { return true; }
    }

    return false;
}

bool verylong::operator>(const verylong& f)
{
    if (n.size() > f.n.size()) { return true; }
    if (n.size() < f.n.size()) { return false; }

    int i = 0;
    if (n.size() == f.n.size())
    {
        while (i < n.size())
        {
            if (n[i] != f.n[i]) { break; }
            i++;
        }

        if (i == n.size()) { return false; }
        else
        {
            if (n[i] > f.n[i]) { return true; }
            else { return false; }
        }
    }
}

bool verylong::operator<(const verylong& f)
{
    if (n.size() < f.n.size()) { return true; }
    if (n.size() > f.n.size()) { return false; }

    int i = 0;
    if (n.size() == f.n.size())
    {
        while (i < n.size())
        {
            if (n[i] != f.n[i]) { break; }
            i++;
        }

        if (i == n.size()) { return false; }
        else
        {
            if (n[i] < f.n[i]) { return true; }
            else { return false; }
        }
    }
}

bool verylong::operator>=(const verylong& f)
{
    if (n.size() > f.n.size()) { return true; }
    if (n.size() < f.n.size()) { return false; }

    int i = 0;
    if (n.size() == f.n.size())
    {
        while (i < n.size())
        {
            if (n[i] != f.n[i]) { break; }
            i++;
        }

        if (i == n.size()) { return true; }
        else
        {
            if (n[i] > f.n[i]) { return true; }
            else { return false; }
        }
    }
}

bool verylong::operator<=(const verylong& f)
{
    if (n.size() < f.n.size()) { return true; }
    if (n.size() > f.n.size()) { return false; }

    int i = 0;
    if (n.size() == f.n.size())
    {
        while (i < n.size())
        {
            if (n[i] != f.n[i]) { break; }
            i++;
        }

        if (i == n.size()) { return true; }
        else
        {
            if (n[i] < f.n[i]) { return true; }
            else { return false; }
        }
    }
}

verylong verylong::operator-(const verylong& f) //я ее сделала до перегрузок операторов сравнения для элементов класса
{
    vector<int> z; //нужен для того, чтобы работать с наибольшим значением и менять его, если необходимо (когда мы будем занимать 1 у больших разрядов)
    if (f.n.size() > n.size())
    {
        for (int i = 0; i < f.n.size(); i++)
            z.push_back(f.n[i]);
    }
    else
    {
        for (int i = 0; i < n.size(); i++)
            z.push_back(n[i]);
    }

    verylong result;
    bool q = true; //если равняется 0, то f > n, в обратном случае f <= n
    stack<int> st; //используем стек, в него сначала вносим значения

    if (n.size() == f.n.size())
    {
        int i = 0;
        while (i < n.size()) //проверяем равенство двух значений
        {
            if (n[i] > f.n[i]) { break; }
            if (n[i] < f.n[i]) { q = false; break; }

            i++;
        }
        if (i == n.size()) { result.n.push_back(0); return result; } //если два числа одинаковые, хотя по идее, нам это не надо

        int k = n.size() - 1; //понимаем, что числа разные

        if (!q) //f > n, z в начале равняется n в этом случае
        {
            z.clear();
            for (int i = 0; i < f.n.size(); i++)
                z.push_back(f.n[i]);
        }

        while (k >= 0)
        {
            int v;

            if (z[k] < 0) { cout << "Чё?" << endl;  break; } // для отладки

            if (q) { v = z[k] - f.n[k]; } //n(z) > f
            else { v = z[k] - n[k]; } //f(z) > n

            if (v < 0) //придется занимать
            {
                int zero = 1; //у какого разряда занимаем? явно не у текущего, поэтому zero != 0
                while (z[k - zero] == 0 && k - zero >= 0) //у нуля не займешь единицу
                {
                    z[k - zero] = 9;
                    zero++; //двигаемся в следующий разряд
                }
                z[k - zero]--; //занимаем
                v += 10; //используем занимаемую единицу
            }
            st.push(v);

            k--;
        }
    }
    else //тут тоже самое, но для значений разного размера
    {
        if (n.size() < f.n.size()) { q = !q; }

        int kn = n.size() - 1;
        int kf = f.n.size() - 1;
        if (q) //тот же перебор, что и прежде, но с одним нюансом
        {
            while (kf >= 0) //пока не заканчиваются разряды у первого числа
            {
                int v;
                if (z[kn] < 0)
                {
                    cout << "Э?" << endl;
                    break;
                }
                v = z[kn] - f.n[kf];

                if (v < 0)
                {
                    int zero = 1;
                    while (z[kn - zero] == 0 && kn - zero > 0)
                    {
                        z[kn - zero] = 9;
                        zero++;
                    }
                    z[kn - zero]--;

                    v += 10;
                }
                st.push(v);

                kn--;
                kf--; //вот такой нюанс
            }

            while (kn >= 0) { st.push(z[kn]); kn--; } //оставшиеся разряды в большем числе просто сносим в результат, как в вычитании
        }
        else //тут все то же самое
        {
            while (kn >= 0)
            {
                int v;

                if (z[kf] < 0)
                {
                    break;
                }
                v = z[kf] - n[kn];

                if (v < 0)
                {
                    int zero = 1;
                    while (z[kf - zero] == 0 && kf - zero > 0)
                    {
                        z[kf - zero] = 9;
                        zero++;
                    }
                    z[kf - zero]--;

                    v += 10;
                }
                st.push(v);

                kn--;
                kf--;
            }

            while (kf >= 0) { st.push(z[kf]); kf--; }
        }
    }

    while (st.top() <= 0 && !st.empty()) { st.pop(); } //при вынесении оставшихся разрядов последние могут хранить нули (1000 - 999 = 0001)

    while (!st.empty())
    {
        result.n.push_back(st.top());
        st.pop();
    }

    return result;
}

verylong operator%(verylong& f1, verylong& f2) //просто вычитаем из большего меньшее, пока не получим значение, меньшее вычитаемого
{
    verylong result;
    if (f1 == f2)
    {
        result.n.push_back(0);

        return result;
    }

    bool f = true;
    if (f2 > f1) { f = !f; }

    if (f)
    {
        result = f1;
        while (result >= f2) { result = result - f2; }
    }
    else
    {
        result = f2;
        while (result >= f1) { result = result - f1; }
    }

    return result;
}

verylong verylong::del2()
{
    verylong result;

    int i = 0, r = 0; //счетчик и остаток соответственно
    bool e = false; //если не вснесем, будет плохо
    while (i < n.size()) //имитируем деление столбиком
    {
        int v;
        if (r == 0 && n[i] == 0) { result.n.push_back(0); i++; } //если нет остатка и разряд равен 0, то просто добавляем в результат
        else
        {
            if (n[i] < 2)
            {

                if (r == 0)
                {
                    int temp = 10 * n[i] + n[i + 1]; //при делении столбиком при очередном делении получаем остаток, и добавляем к нему следующий разряд
                    if (temp % 2 == 1) { e = true; } //если бы мы сразу остатку присвоили 1, то выполнилась бы следующее условие

                    if (i != 0) { result.n.push_back(0); } //когда в делимом первый разряд равнялся единице, то первым знаком в результате был 0, и при вычитании возникала ошибка
                    result.n.push_back(temp / 2);
                    i++; //так как мы уже перешли на следующий разряд
                }
                if (r == 1) //аналогично, но в этом случае мы не переходим на следующий разряд, так как мы в результате получили 1
                {
                    int temp = 10 + n[i];
                    r = 0;
                    if (temp % 2 == 1) { e = true; }
                    result.n.push_back(temp / 2);
                }

                if (e) { r = 1; e = !e; } //уже тут через е меняем значение остатка, если необходимо
            }
            else //n >= 2, тут все аналогично
            {
                if (r == 0)
                {
                    result.n.push_back(n[i] / 2);
                    if (n[i] % 2 != 0) { e = true; }
                }
                if (r == 1)
                {
                    e = true;
                    result.n.push_back((10 + n[i]) / 2);
                    if (n[i] % 2 == 0) { e = false; }
                }

                if (e) { r = 1; e = false; }
                else { r = 0; }
            }

            i++;
        }
    }

    return result;
}

verylong verylong::Umn2() //также имитация умножения на два "на бумаге"
{
    if (n.size() == 1 && n[0] == 0) { return *this; } //n = 0

    verylong result;
    stack<int> st;
    int i = n.size() - 1, k = 0; //счетчик разрядов и число, которое мы запоминаем при умножении, когда получается результат > 9
    bool f = 0; //тот же счетчик, что и е при делении
    while (i >= 0) //если мы напишем i >= 0, то оставшаяся единица(k), если она есть не запишется в результат 
    {
        //4 случая при умножении
        int v = 2 * n[i];

        if (v < 10 && k == 0) { st.push(v); f = 0; } //самый приятный случай
        if (v < 10 && k == 1) //мы запомнили единицу, перешли на новый разряд, и при умножении на два он все равно меньше 10
        {
            v++;//мы запоминаему единицу складывали с числом
            if (v > 9) //можно записать v == 10, но это на два знака больше
            {
                st.push(v % 10);
                if (i == 0) { st.push(1); break; }
                f = 1;
            }
            else
            {
                st.push(v);
                f = 0;
            }
        }
        if (v > 9 && k == 0)
        {
            st.push(v % 10);
            if (i == 0) { st.push(1); break; }
            f = 1;
        }
        if (v > 9 && k == 1)
        {
            v++;
            st.push(v % 10);
            if (i == 0) { st.push(1); break; }
            f = 1;
        }

        if (f) { k = 1; }
        else { k = 0; }

        i--;
    }

    while (st.top() == 0 && st.size() > 0) { st.pop(); }

    while (!st.empty())
    {
        result.n.push_back(st.top());
        st.pop();
    }

    return result;
}

void verylong::genofnum(int k) //аргумент нужен, чтобы при генерировании двух чисел количество их разрядов не сильно отличалось
{
    n.clear();
    n.push_back(0); //чтобы войти в цикл
    while (n[0] == 0) { n[0] = rand() % 10; } //чтобы высший разряд в числе не был равен 0 (тут с этим строго)

    for (int i = 1; i < 30 + k; i++) //он работал при i < 20 + k 9 и 1 секунду при евклиде и бинарном соответственно, так что я увеличила значения, и бинарный алгоритм все равно очень быстрый
    {
        n.push_back(rand() % 10);
    }
}

verylong Eqlide(verylong f1, verylong f2)
{
    verylong c;
    while (true)
    {
        c = f1 % f2; //внутри операции % предусмотрено, чтобы большее число делилось на меньшее, и не важно, где оно стоит. может это тупо, но запись сокращает
        if (c.n.size() == 1 && c.n[0] == 0) //если с = 0
        {
            if (f1 > f2) { return f2; }
            else { return f1; }
        }
        if (f1 > f2) { f1 = c; } //в этих двух условиях наибольшее число заменяем с
        else { f2 = c; }
    }
}

verylong Binary(verylong f1, verylong f2)
{
    int k = 1; //счетчик, сколько раз мы умножаем на два нод, перед тем, как вернуть значение (х2)
    while (true)
    {
        if (f1.n[0] == 0 && f1.n.size() == 1) //f1 == 0, возвращаем f2
        {
            if (k > 1)
            {
                while (k != 1)
                {
                    f2 = f2.Umn2();
                    k /= 2;
                }
            }

            return f2;
        }
        if (f2.n[0] == 0 && f2.n.size() == 1) //f2 == 0, возвращаем f1
        {
            if (k > 1)
            {
                while (k != 1)
                {
                    f1 = f1.Umn2();
                    k /= 2;
                }
            }

            return f1;
        }
        if (f1 == f2) //чтобы не делать лишнего действия
        {
            if (k > 1)
            {
                while (k > 1)
                {
                    f1 = f1.Umn2();
                    k /= 2;
                }
            }

            return f1;
        }
        if (f1.n.size() == 1 && f1.n[0] == 1 || f2.n.size() == 1 && f2.n[0] == 1) //если f1 = 1 или f2 = 1, в этих случаях резульиат равен 1 * k
        {
            verylong c;//результат

            if (k == 0) { c.n.push_back(1); return c; }
            if (k > 9) //так как у меня элемент вектора содержит только одну цифру, то дробим k, и добавляем по одному значению сначала в стек, а потом возвращаем результат
            {
                stack<int> st;
                while (k > 9)
                {
                    st.push(k % 10);
                    k /= 10;
                }

                while (!st.empty())
                {
                    c.n.push_back(st.top());
                    st.pop();
                }

                return c;
            }

            c.n.push_back(k);
            return c;
        }

        while (f1.n[f1.n.size() - 1] % 2 == 0 && f2.n[f2.n.size() - 1] % 2 == 0) //f1 % 2 == 0 && f2 & 2 == 0
        {
            f1 = f1.del2();
            f2 = f2.del2();

            k += 2;
        }

        if (f1.n[f1.n.size() - 1] % 2 == 0 && f2.n[f2.n.size() - 1] % 2 != 0) //f1 % 2 == 0 && f2 & 2 != 0
        {
            f1 = f1.del2();
        }
        if (f2.n[f2.n.size() - 1] % 2 == 0 && f1.n[f1.n.size() - 1] % 2 != 0) //f1 % 2 != 0 && f2 & 2 == 0
        {
            f2 = f2.del2();
        }

        if (f1.n[f1.n.size() - 1] % 2 != 0 && f2.n[f2.n.size() - 1] % 2 != 0) //f1 % 2 != 0 && f2 & 2 != 0
        {
            if (f1 > f2) { f1 = f1 - f2; }
            else { f2 = f2 - f1; }
        }
    }
}

struct for_queue //чтобы генерировать значения
{
    verylong a;
    verylong b;
};

int main()
{
    setlocale(LC_ALL, "rus");

    namespace sw = stopwatch; //часики
    sw::Stopwatch watch1, watch2;

    verylong a, b, n;

    queue<for_queue> q;
    for_queue z;

    //string h = "C:/Users/1/Desktop/output.txt";
    string h;
    cout << "Введите путь к файлу, в который запишутся данные: ";
    cin >> h;

    ofstream out;

    out.open(h);
    if (!out.is_open())
    {
        cout << "Нет доступа к диску для записи или некорректно введено имя файла" << endl;
        return -1;
    }

    for (int i = 0; i < 100; i++) //генерация чисел и заполнение очереди
    {
        int k = rand() % 10; //для аргумента генератора числа
        int r = rand() % 4; //чтобы размер разряда второго числа различался на небольшое число
        if (k - r < 0)
        {
            a.genofnum(k);
            b.genofnum(k + r);
        }
        else
        {
            a.genofnum(k);
            b.genofnum(k - r);
        }

        z.a = a;
        z.b = b;
        q.push(z);
    }

    out << "Способ вычисления: алгоритм Евклида" << endl;

    watch1.start();
    for (int i = 0; i < 100; i++)
    {
        z = q.front();
        q.push(q.front()); //для следующего цикла нам нужны те же значения для очереди, может заполнение расходует больше времени
        q.pop();
        a = z.a;
        b = z.b;

        n = Eqlide(a, b);

        out << i + 1 << ". " << a << ' ' << b << ' ' << n << endl;
    }

    uint64_t elapsed_s = watch1.elapsed<sw::seconds>(); //сразу останавливаем часы

    out << endl << "Способ вычисления: бинарный алгоритм" << endl;

    watch2.start();
    for (int i = 0; i < 100; i++)
    {
        z = q.front();
        q.pop();
        a = z.a;
        b = z.b;

        n = Binary(a, b);
        out << i + 1 << ". " << a << ' ' << b << ' ' << n << endl;
    }
    uint64_t elapsed_s1 = watch2.elapsed<sw::seconds>();

    out << endl << "Время выполнения алгоритма Евклида: " << elapsed_s << "s" << endl; //выводим значения
    out << "Время выполнения бинарного алгоритма: " << elapsed_s1 << "s" << endl;

    out.close();

    return 0;
}