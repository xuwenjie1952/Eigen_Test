#include "funset.hpp"
#include <iostream>
#include <Eigen/Dense>

template <typename T>
static void matrix_mul_matrix(T* p1, int iRow1, int iCol1, T* p2, int iRow2, int iCol2, T* p3)
{
	if (iRow1 != iRow2) return;

	//������, Matrix�����ľ���Ĭ���ǰ��д洢
	//Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map1(p1, iRow1, iCol1);
	//Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map2(p2, iRow2, iCol2);
	//Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map3(p3, iCol1, iCol2);

	//������
	Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > map1(p1, iRow1, iCol1);
	Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > map2(p2, iRow2, iCol2);
	Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > map3(p3, iCol1, iCol2);

	map3 = map1 * map2;
}

int test_eigen_base()
{
	//1. ����Ķ���
	Eigen::MatrixXd m(2, 2);
	Eigen::Vector3d vec3d;
	Eigen::Vector4d vec4d(1.0, 2.0, 3.0, 4.0);

	//2. ��̬���󡢾�̬����
	Eigen::MatrixXd matrixXd;
	Eigen::Matrix3d matrix3d;

	//3. ����Ԫ�صķ���
	m(0, 0) = 1;
	m(0, 1) = 2;
	m(1, 0) = m(0, 0) + 3;
	m(1, 1) = m(0, 0) * m(0, 1);
	std::cout << m << std::endl << std::endl;

	//4. ���þ����Ԫ��
	m << -1.5, 2.4,
		6.7, 2.0;
	std::cout << m << std::endl << std::endl;
	int row = 4;
	int col = 5;
	Eigen::MatrixXf matrixXf(row, col);
	matrixXf << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
	std::cout << matrixXf << std::endl << std::endl;
	matrixXf << Eigen::MatrixXf::Identity(row, col);
	std::cout << matrixXf << std::endl << std::endl;

	//5. ���þ����С
	Eigen::MatrixXd matrixXd1(3, 3);
	m = matrixXd1;
	std::cout << m.rows() << "  " << m.cols() << std::endl << std::endl;

	//6. ��������
	m << 1, 2, 7,
		3, 4, 8,
		5, 6, 9;
	std::cout << m << std::endl;
	matrixXd1 = Eigen::Matrix3d::Random();
	m += matrixXd1;
	std::cout << m << std::endl << std::endl;
	m *= 2;
	std::cout << m << std::endl << std::endl;
	std::cout << -m << std::endl << std::endl;
	std::cout << m << std::endl << std::endl;

	//7. ������ת�á�������󡢰������
	std::cout << m.transpose() << std::endl << std::endl;
	std::cout << m.conjugate() << std::endl << std::endl;
	std::cout << m.adjoint() << std::endl << std::endl;
	std::cout << m << std::endl << std::endl;
	m.transposeInPlace();
	std::cout << m << std::endl << std::endl;

	//8. ������ˡ������������
	std::cout << m*m << std::endl << std::endl;
	vec3d = Eigen::Vector3d(1, 2, 3);
	std::cout << m * vec3d << std::endl << std::endl;
	std::cout << vec3d.transpose()*m << std::endl << std::endl;

	//9. ����Ŀ����
	std::cout << m << std::endl << std::endl;
	std::cout << m.block(1, 1, 2, 2) << std::endl << std::endl;
	std::cout << m.block<1, 2>(0, 0) << std::endl << std::endl;
	std::cout << m.col(1) << std::endl << std::endl;
	std::cout << m.row(0) << std::endl << std::endl;

	//10. �����Ŀ����
	Eigen::ArrayXf arrayXf(10);
	arrayXf << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
	std::cout << vec3d << std::endl << std::endl;
	std::cout << arrayXf << std::endl << std::endl;
	std::cout << arrayXf.head(5) << std::endl << std::endl;
	std::cout << arrayXf.tail(4) * 2 << std::endl << std::endl;

	//11. �����������ֵ����������
	Eigen::Matrix2f matrix2f;
	matrix2f << 1, 2, 3, 4;
	Eigen::SelfAdjointEigenSolver<Eigen::Matrix2f> eigenSolver(matrix2f);
	if (eigenSolver.info() == Eigen::Success) {
		std::cout << eigenSolver.eigenvalues() << std::endl << std::endl;
		std::cout << eigenSolver.eigenvectors() << std::endl << std::endl;
	}

	Eigen::SelfAdjointEigenSolver<Eigen::Matrix2f>::RealVectorType eigen_values = eigenSolver.eigenvalues();
	Eigen::Vector2f vec = eigen_values.array();
	std::cout << vec[0] << "    " << vec[1] << std::endl;

	//12. ��Map����̬�����ʹ��
	int array1[4] = { 1, 2, 3, 4 };
	int array2[4] = { 5, 6, 7, 8 };
	int array3[4] = { 0, 0, 0, 0 };
	matrix_mul_matrix(array1, 2, 2, array2, 2, 2, array3);
	for (int i = 0; i < 4; i++)
		std::cout << array3[i] << std::endl;

	return 0;
}

int test_matrix_inverse()
{
	Eigen::MatrixXd m(3, 2), m_(2, 3);
	m << 1, 2, 3, 4, 5, 6;
	m_ = m.reverse(); // ת�þ���

	Eigen::MatrixXd m2(3, 3), m2_(3, 3);
	m2 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	m2_ = m2.inverse(); // �����
	Eigen::MatrixXd m3 = m2.inverse();

	return 0;
}