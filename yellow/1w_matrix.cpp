#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix () {
		Reset(0,0);
	};
	Matrix (const int& num_rows, const int& num_cols) {
		Reset(num_rows, num_cols);
	}

	void Reset(const int& num_rows, const int& num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("Out of range");
		}
		matrix.clear();
		is_empty = !num_rows || !num_cols;
		matrix.assign(num_rows, vector<int>(num_cols));
	}

	int At(const int& row, const int& col) const {
		// throw_if_out_of_range(row, col);
		return matrix.at(row).at(col);
	}

	int& At(const int& row, const int& col) {
		// throw_if_out_of_range(row, col);
		return matrix.at(row).at(col);
	}

	int GetNumRows() const {
		return matrix.size();
	}

	int GetNumColumns() const {
		return matrix.empty() ? 0 : matrix[0].size();
	}

	bool empty() const {
		return is_empty;
	}

private:
	vector<vector<int>> matrix;

	bool is_empty = true;

//	void throw_if_out_of_range(const int& row, const int& col) const{
//		if (!matrix.size() ||
//			row < 0 || row > this->GetNumRows()-1 ||
//			col < 0 || col > this->GetNumColumns()-1){
//			throw out_of_range("Out of range");
//		}
//	}
};

istream& operator>>(istream& stream, Matrix& matrix) {
	int rows, cols;
	stream >> rows >> cols;
	Matrix result(rows, cols);
	for (int i = 0; i < result.GetNumRows(); ++i) {
		for (int j = 0; j < result.GetNumColumns(); ++j) {
			if (!(stream >> result.At(i, j))) {
				throw invalid_argument("Not enough arguments");
			}
		}
	}
	matrix = result;
	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
	stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	for (int i = 0; i < matrix.GetNumRows(); ++i) {
		stream << (!i ? "" : "\n") << matrix.At(i, 0);
		for (int j = 1; j < matrix.GetNumColumns(); ++j) {
			stream << " " << matrix.At(i, j);
		}
	}
	return stream;
}

bool operator==(const Matrix& m1, const Matrix& m2){
	if (m1.empty() && m2.empty())
		return true;

	if (m1.GetNumRows() != m2.GetNumRows() || m1.GetNumColumns() != m2.GetNumColumns()) {
		return false;
	}

	for (int i = 0; i < m1.GetNumRows(); ++i) {
		for (int j = 0; j < m1.GetNumColumns(); ++j) {
			if (m1.At(i, j) != m2.At(i, j)) {
				return false;
			}
		}
	}
	return true;
}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
	if (m1.empty() && m2.empty())
		return {};

	if (m1.GetNumRows() != m2.GetNumRows() || m1.GetNumColumns() != m2.GetNumColumns()) {
		throw invalid_argument("Invalid argument");
	}

	Matrix result(m1.GetNumRows(), m1.GetNumColumns());
	for (int i = 0; i < m1.GetNumRows(); ++i) {
		for (int j = 0; j < m1.GetNumColumns(); ++j) {
			result.At(i, j) = m1.At(i, j) + m2.At(i, j);
		}
	}

	return result;
}

int main() {


//	Matrix m1(1,1), m2(0,7);

//	cout << "m1.GetNumRows()= " << m1.GetNumRows() << endl;
//	cout << "m1.GetNumColumns()= " << m1.GetNumColumns() << endl;
//	cout << "m2.GetNumRows()= " << m2.GetNumRows() << endl;
//	cout << "m2.GetNumColumns()= " << m2.GetNumColumns() << endl;
//
//	cout << m1 + m2 << endl;

//	cout << m1.empty() << endl;
//	cout << m2.empty() << endl;
//
//	cout << (m1 == m2) << endl;

	return 0;
}