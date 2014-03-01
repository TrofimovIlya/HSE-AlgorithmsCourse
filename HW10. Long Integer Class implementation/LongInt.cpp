// Трофимов Илья
// 272(2)ПИ

#include <iostream> 
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std; 

class LongInt {
    private:  
        string number;
        int radix; 
        int* array; 
        int N; 

    public: 
        LongInt(string numb, int rad) {
            number = numb;
            radix = rad;
            N = getN();
            array = new int[N];
            input();
        }

        LongInt() {
            number = "0";
            radix = 10;
            N = 0;
            array = new int[2];
            array[0] = 1;
            array[1] = 0;
        }
        
        int getN() {
            int tempRadix = radix;
            N = 0; 
            while (tempRadix > 9) {
                tempRadix = tempRadix / 10;
                N++;
            }
            int L = N;
            N = number.size() / N;
            if (N == 0) { 
                N++;
            } else if (number.size() % L > 0) {
                N++;
            }
            N++;
            return N;
        }

        int* getNumber() {
            return array;
        }

        int getRadix() {
            return radix;
        }

        void setNumber(string numb) {
            number = numb;
            input();
        }

        void setNumber(int* numb) {
            array = numb;
        }

        void setRadix(int rad) {
            radix = rad;
        }

        static LongInt calculateFib(int N) { 
            if (N == 0) {
                return LongInt("0", 1000);
            }
            LongInt* ar = new LongInt[N + 1];
            ar[0] = LongInt("0", 1000);
            ar[1] = LongInt("1", 1000);
            for (int i = 2; i < N + 1; i++) {
                ar[i] = ar[i - 1].plus(ar[i - 2]);
            }
            LongInt numb = ar[N];
            for (int i = 0; i < N; i++) {
                delete [] ar[i].getNumber();
            }
            delete [] ar;
            return numb;
        }

        void consoleInput() {
            cout << "Введите число: " << endl;
            cin >> number;
            cout << "Введите  основание системы счисления: "<< endl;
            cin >> radix;
            N = getN();
            array = new int[N];
            input();
        }

        void open(string fileName) {
            fstream file;
            file.open(fileName, fstream::in);
            file >> number;
            file >> radix;
            N = getN();
            array = new int[N];
            file.close();
            input();
        }

        void consoleOutput() {
            int temp;
            int number = 0;
            temp = radix - 1;
            while (temp > 9) {
                temp = temp / 10;
                number++;
            }
            number++;
            if (array[0] == 0) {
                cout << 0;
            }
            for (int i = array[0]; i >= 1; i--) {
                if (i != array[0]) {
                    int count = 0;
                    temp = array[i];
                    while (temp > 9) {
                        temp = temp / 10;
                        count++;
                    }
                    count++;
                    if (count < number) {
                        for (int j = 0; j < (number - count); j++) {
                            cout << "0";
                        }
                    }
                    cout << array[i];
                } else {
                    cout << array[i];
                }
            }
        }

        void save(string fileName) {
            fstream outFile;
            outFile.open (fileName, fstream::out);
            int temp;
            int count2 = 0;
            temp = radix - 1;

            while (temp > 9) {
                temp = temp / 10;
                count2++;
            }

            count2++;
            if (array[0] == 0) {
                outFile << 0;
            }
            for (int i = array[0]; i >= 1; i--) {
                if (i != array[0]) {
                    int count = 0;
                    temp = array[i];
                    while (temp > 9) {
                        temp = temp / 10;
                        count++;
                    }
                    count++;
                    if (count < count2) {
                        for (int j = 0; j < (count2 - count); j++) {
                            outFile << "0";
                        }
                    }
                    outFile << array[i];
                } else {
                    outFile << array[i];
                }
            }
            outFile << endl;
            outFile.close();
        }

        void input() {
            for (int i = 0; i < N; i++) {
                array[i] = 0;
            }
            int j = 0;
            while (j < number.size()) { 
                char ch = number[j];
                j++;
                if ((ch >= '0') && (ch <= '9')) {
                    for (int i = array[0]; i > 0; i--) {
                        array[i + 1] = array[i + 1] + array[i] * 10 / radix;
                        array[i] = array[i] * 10 % radix;
                    }
                    array[1] = array[1] + (ch -'0');
                    if (array[array[0] + 1] > 0) {
                        array[0] = array[0] + 1;
                    }
                } 
            }
        }

        void zero() {
            number = "0";
            radix = 10;
            N = 0;
            delete [] array;
            array = new int[2];
            array[0] = 1;
            array[1] = 0;
        }
        
        LongInt plus(LongInt numb) {
            int* tempArray = numb.getNumber();
            int k = max(array[0], tempArray[0]);
            int* resAr = new int[k + 2];
            resAr[k + 1] = 0;
            if (array[0] > tempArray[0]) {
                for (int i = 1; i <= k; i++) {
                    resAr[i] = array[i];
                }
                for (int i = 1; i <= tempArray[0]; i++) { 
                    resAr[i + 1] = resAr[i + 1] + (resAr[i] + tempArray[i]) / radix;
                    resAr[i] = (resAr[i] + tempArray[i]) % radix;
                } 
            } else {
                for (int i = 1; i <= k; i++) {
                    resAr[i] = tempArray[i];
                }
                for (int i = 1; i <= array[0]; i++) { 
                    resAr[i + 1] = resAr[i + 1] + (resAr[i] + array[i]) / radix; 
                    resAr[i] = (resAr[i] + array[i]) % radix;
                } 
            }           
            if (resAr[k + 1] == 0) {
                resAr[0] = k; 
            } else {
                resAr[0] = k + 1;
            }
            LongInt obj = LongInt();
            obj.setNumber(resAr);
            obj.setRadix(radix);
            return obj;
        }

        LongInt minus(LongInt numb) {
            int* tempArray = numb.getNumber();
            int i, temp, pos = 0;
            if (less(numb)) {
                return LongInt("0", radix);
            } else {
                int* resAr = new int[max(array[0], tempArray[0]) + 1];
                for (i = 1; i <= tempArray[0]; i++) {
                    temp = array[i] - tempArray[i] + pos;
                    if (temp < 0) {
                        resAr[i] = temp + radix;
                        pos = -1; 
                    } else {
                        resAr[i] = temp;
                        pos = 0;
                    }
                }
                for (; i <= array[0]; i++) { 
                    temp = array[i] + pos; 
                    if (temp < 0) {
                        resAr[i] = temp + radix;
                        pos = -1; 
                    } 
                    else { 
                        resAr[i] = temp;
                        pos = 0;
                    }
                }

                i = array[0];

                while ( (i > 0) && (resAr[i] == 0)) {
                    i--; 
                }

                resAr[0] = i;
                LongInt obj = LongInt();
                obj.setNumber(resAr);
                obj.setRadix(radix);
                return obj;
            }
        }

        bool equals(LongInt numb) {
            bool isEqual = false; 
            int* tempArray = numb.getNumber();
            if (array[0] != tempArray[0]) {
                return isEqual;
            } else { 
                int i = 1;
                while ((i <= array[0]) && (array[i] == tempArray[i])) {
                    i++;
                }
                isEqual = (i == (array[0] + 1));
            }
            return isEqual;
        }
        
        bool more(LongInt numb) {
            int* tempArray = numb.getNumber();
            bool isMore = false; 
            if (array[0] < tempArray[0]) {
                return isMore;
            } else if (array[0] > tempArray[0]) {
                isMore = true; 
                return isMore;
            } else { 
                int i = array[0];
                while ((i > 0) && (array[i] == tempArray[i])) {
                    i--;
                }
                if (i == 0) {
                    isMore = false;
                } else if (array[i]>tempArray[i]) {
                    isMore = true;
                } else {
                    isMore = false;
                }
            }
            return isMore;
        }

        bool moreOrEqual(LongInt numb) {
            return more(numb) || equals(numb);
        }

        bool notEquals(LongInt numb) {
            return !equals(numb);
        }

        bool less(LongInt numb) {
            return (!more(numb)) && (!equals(numb));
        }
};

void main() {         
    setlocale(LC_ALL,"Russian"); 
    ifstream in("input.txt"); 
    int NT; 
    in >> NT;
    int radix;
    in >> radix;
    for (int i = 0; i < NT; i++) {  
        cout << "Тест " << i + 1 << endl;
        string firstNumber;
        string secondNumber;
        in >> firstNumber;
        in >> secondNumber;
        LongInt oneNumber = LongInt(firstNumber, radix);
        LongInt twoNumber = LongInt(secondNumber, radix);
        oneNumber.consoleOutput();
        
        if (oneNumber.notEquals(twoNumber)) {
            if (oneNumber.more(twoNumber)) {
                cout << " больше ";
            } else {
                cout << " меньше ";
            }
        } else {
            cout << " равно ";
        }
        twoNumber.consoleOutput();
        cout << endl;
        delete [] oneNumber.getNumber();
        delete [] twoNumber.getNumber();
    }
    in.close();
    cout << endl;
    cout << "N-e число Фибоначчи:" << endl;
    cout << "Введите N от 50 до 101: ";
    int N;
    cin >> N;
    LongInt result = LongInt();
    result = result.calculateFib(N);
    result.consoleOutput(); 
    delete [] result.getNumber();
    cout << endl;
    system("pause");
}