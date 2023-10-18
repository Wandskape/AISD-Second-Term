#include <iostream>
using namespace std;

void hanoiTower(int N, int i, int k, int temp) {
    if (N == 1) {
        cout << "Переместить диск 1 с " << i << " на " << k << " стержень" << endl;
        return;
    }

    hanoiTower(N - 1, i, temp, k);
    cout << "Переместить диск " << N << " с " << i << " на " << k << " стержень" << endl;
    hanoiTower(N - 1, temp, k, i);
}

int main() {
    setlocale(LC_ALL, "rus");

    int N, k;
    cout << "Введите количество дисков (N): ";
    cin >> N;
    cout << "Введите количество стержней (k): ";
    cin >> k;

    hanoiTower(N, 1, k, 2);

}
