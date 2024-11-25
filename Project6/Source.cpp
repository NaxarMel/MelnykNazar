#include <iostream>
#include <vector>
#include <random>
#include <Eigen/Dense> // ��������� Eigen ��� ������ � ������ ��������

using namespace std;
using namespace Eigen;

int main() {
    // ʳ������ �����
    const int N = 10;

    // ������ ������� ������ (���)
    Vector3d mean(0, 0, 0);

    // ����������� �������
    Matrix3d k;
    k << 235, 284, 311,
        284, 325, 183,
        311, 183, 345;

    // ��������� ���������� ����� � ����������� ��������
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> normal_dist(0.0, 1.0);

    // ������������ ���������� ��� ������� k
    Matrix3d L = k.llt().matrixL();

    // �������� ����������
    vector<Vector3d> results;

    // ��������� �������
    for (int i = 0; i < N; ++i) {
        Vector3d z;
        for (int j = 0; j < 3; ++j) {
            z[j] = normal_dist(gen); // �������� �������� �������� ��� ������������ ����������� ��������
        }
        Vector3d x = mean + L * z; // �������������
        results.push_back(x);
    }

    // ��������� ����������
    cout << "����������� ������� �����:" << endl;
    for (int i = 0; i < results.size(); ++i) {
        cout << "X" << i + 1 << ": " << results[i].transpose() << endl;
    }

    return 0;
}
