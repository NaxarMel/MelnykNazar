#include <iostream>
#include <vector>
#include <random>
#include <Eigen/Dense> // Бібліотека Eigen для роботи з лінійною алгеброю

using namespace std;
using namespace Eigen;

int main() {
    // Кількість блоків
    const int N = 10;

    // Задаємо середній вектор (нулі)
    Vector3d mean(0, 0, 0);

    // Кореляційна матриця
    Matrix3d k;
    k << 235, 284, 311,
        284, 325, 183,
        311, 183, 345;

    // Генерація випадкових чисел з нормального розподілу
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> normal_dist(0.0, 1.0);

    // Декомпозиція Холецького для матриці k
    Matrix3d L = k.llt().matrixL();

    // Зберігаємо результати
    vector<Vector3d> results;

    // Генерація векторів
    for (int i = 0; i < N; ++i) {
        Vector3d z;
        for (int j = 0; j < 3; ++j) {
            z[j] = normal_dist(gen); // Генеруємо випадкові значення для стандартного нормального розподілу
        }
        Vector3d x = mean + L * z; // Трансформація
        results.push_back(x);
    }

    // Виведення результатів
    cout << "Змодельовані вектори станів:" << endl;
    for (int i = 0; i < results.size(); ++i) {
        cout << "X" << i + 1 << ": " << results[i].transpose() << endl;
    }

    return 0;
}
