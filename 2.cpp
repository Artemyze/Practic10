//массив С из расстояний от начала координат до точек с координатами (A[0],B[0]),(A[1],B[1]),…	
//найти две таких точки, которые равноудалены* от начала координат и при этом лежат 
//в разных четвертях (определить номера точек или выдать сообщение, что таких точек нет)
//считать точки равноудалёнными, если их расстояния до начала координат отличаются не больше, чем на 0,001.
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define TOLERANCE 0.001 // значение допуска

void sort(double **mas, int size, bool asc) 
{
    int i = 0; //Указатели в начало и в конец массива
    int j = size - 1;
    double mid = mas[size / 2][0]; //Центральный элемент массива
    do { //Делим массив, пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        if (asc){
            while(mas[i][0] < mid) { //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
                i++;
            }
            while(mas[j][0] > mid) { //В правой части пропускаем элементы, которые больше центрального
                j--;
            }
        } 
        else {              // блок else реализовывает сортировку по убыванию(меняем '<' на '>' и наоборот)
            while(mas[i][0] > mid) {
                i++;
            }
            while(mas[j][0] < mid) {
                j--;
            }
        }
        if (i <= j) { //Меняем элементы местами
            for(int r = 0; r < 2; r++){
                double tmp = mas[i][r];
                mas[i][r] = mas[j][r];
                mas[j][r] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);
    
    if (i < size) {
        sort(&mas[i], size - i, asc);//сортируем правую часть от середины
    }
    if(j > 0) {
        sort(mas, j + 1, asc);//сортируем левую часть от середины массива
    }
}

double *read_array(int len){  // ввод элементов массивов А и В
    double *arr = new double[len];
    cout << "Enter elements of array:\n";
    for(int i = 0; i < len; i++){
        cin >> arr[i];
    }
    return arr;
}

void print_array(double **arr, int len){ // печать двумерного массива
    for(int i = 0; i < len; i++){
            cout.width(10);
            cout << setprecision(5) << arr[i][0]; 
            if (((i+1)%2 == 0) || (i+1 == len)) cout << endl;
    }
}

void my_task(double *arr1, double *arr2, double **C, int len){ // найдем и запишем в С расстояние от начала координат
    for(int i = 0; i < len; i++) {
        C[i][0] = sqrt(pow(arr1[i],2) + pow(arr2[i], 2));
        C[i][1] = double(i);
    }
}

void check_array1(double **arr1, int *Indexes, int len){ 
    int j = 0;
    for(int n = 0; n < len*2; n++) Indexes[n] = len;
    for(int i = 0; i < len - 1; i++){                       // в Indexes записываем индексы массивов А и В где лежат координаты равноудаленных точек
        if(abs(arr1[i][0] - arr1[i+1][0]) < TOLERANCE) {
            Indexes[j] = arr1[i][1];
            j++;
            Indexes[j] = arr1[i+1][1];
            j++;
        }
    }
}

int check_array2(double *A, double *B, int *Indexes, int len, int i, int n = 0){
        if (Indexes[i] != len) {
            if ((A[Indexes[i]] < 0 && A[Indexes[i+1]] > 0 ) || (A[Indexes[i]] > 0 && A[Indexes[i+1]] < 0 ) ||  // проверка на разность четвертей
               (B[Indexes[i]] < 0 && B[Indexes[i+1]] > 0 ) || (B[Indexes[i]] > 0 && B[Indexes[i+1]] < 0 )){
            cout << "Точки А и В с координатами: A(" << A[Indexes[i]] << ", " << B[Indexes[i]] << "), B(" << A[Indexes[i+1]] << ", " << B[Indexes[i+1]] << ") равноудалены и лежат в разных четвертях.\n"; 
            n++;
            }
            n = check_array2(A, B, Indexes, len, i = i + 2, n);
        }
        return n;
}

int main(){
    int len, fer;
    double  *A, *B, **C;
    bool asc;
    cout << "Введите размер массивов А и В:\n";
    cin >> len; 
    cout << "Введите направленность сортировки массива С. Введите '1' - по возрастанию, введите '0' - по убыванию: \n";
    cin >> asc;
    int *Indexes = new int[len*2]; // массив хранящий индексы всех точек, которые попарно равноудалены
    A = read_array(len);
    B = read_array(len);
    C = new double *[len];
    for(int i = 0; i < len; i++) C[i] = new double [2]; // в С массиве будем хранить в первом столбце расстояние между точками, во втором - индексы эти точек
    my_task(A, B, C, len); // функция заполнения массива С
    cout << "Несортированный массив:\n";
    print_array(C, len);
    cout << "Сортированный:\n";
    sort(C, len, asc); // сортируем массив С
    print_array(C, len);
    check_array1(C, Indexes, len); //проверяем в отсортированном массиве С рядом стоящие точки, если есть равноудаленные - заносим индексы точек в Indexes
    fer = check_array2(A, B, Indexes, len, 0); // fer - счетчик количества точек удовлетворяющих заданию 
    if (fer == 0) cout << "Нет равноудаленных точек, лежащих в разных четвертях!\n";
    for (int i=0; i<2; i++) delete [] C[i];
    delete [] C;
    delete [] A;
    delete [] B;
    delete [] Indexes;
}
