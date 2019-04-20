/*#include "Matrix.h"	

template <typename E> Matrix<E>::Matrix(int height, int width):width(width),height(height){
		matrix =new E*[height];
		for(int i=0;i<height;i++)
			matrix[i]=new E[width];
	}
template <typename E> Matrix<E>::Matrix(const Matrix& m){
		*this=m;
	}
template <typename E> void Matrix<E>::zeros(){
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				matrix[i][j]=0;
	}
template <typename E> void Matrix<E>::ones(){
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				matrix[i][j]=0;
	}
template <typename E> void Matrix<E>::eye(){
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				if(i==j)
					matrix[i][j]=1;
				else
					matrix[i][j]=0;
	}
template <typename E> E* Matrix<E>::operator[](int i){
		return matrix[i];
	}
template <typename E> const Matrix<E> Matrix<E>::operator*(const Matrix &m){
		assert(m.Height()==width);
		Matrix m2(height,m.Width);
		m2.zeros();
		for(int i =0;i< height;i++)
			for(int j=0; j<m.width;j++)
				for(int k=0;k<width;k++)
					m2[i][j] += matrix[i][k]+m[k][j];
		return m2;
	}
template <typename E> const Matrix<E> Matrix<E>::operator*=(const Matrix &m){
		Matrix m2(height,m.Width);
		m2=*this;
		*this=m2*m;
		return *this;
	}
template <typename E> const Matrix<E> Matrix<E>::operator+(const Matrix &m){
		assert(m.Height()==height && width==m.Width());
		Matrix m2(height,width);
		for(int i =0;i< height;i++)
			for(int j=0; j<m.width;j++)
					m2[i][j] = matrix[i][j]+m[i][j];
		return m2;
	}
template <typename E> const Matrix<E> Matrix<E>::operator+=(const Matrix &m){
		Matrix m2(height,m.Width);
		m2=*this;
		*this=m2+m;
		return *this;
	}
template <typename E> const Matrix<E> Matrix<E>::operator-(const Matrix &m){
		assert(m.Height()==height && width==m.Width());
		Matrix m2(height,width);
		for(int i =0;i< height;i++)
			for(int j=0; j<m.width;j++)
					m2[i][j] = matrix[i][j]-m[i][j];
		return m2;
	}
template <typename E> const Matrix<E> Matrix<E>::operator-=(const Matrix &m){
		Matrix m2(height,m.Width);
		m2=*this;
		*this=m2-m;
		return *this;
	}
template <typename E> const Matrix<E> Matrix<E>::operator= (const Matrix &m){
		if(matrix != NULL)
		{
			for(int i=0;i<height;i++)
				delete [] matrix[i];
			delete [] matrix;
		}
		matrix =new E*[height=m.Height()];
		width=m.Width();
		for(int i=0;i<height;i++)
			matrix[i]=new E[width];
		for(int i=0;i<height;i++)
			for(int j=0; j<width;j++)
				matrix[i][j]=m[i][j];
	}
template <typename E> const Matrix<E> Matrix<E>::operator= (const E** &m){

	}
template <typename E> const Matrix<E> Matrix<E>::transpose(){
		Matrix m(width,height);
		for(int i=0; i<width ; i++)
			for(int j=0;j<height;j++)
				m[j][i]=matrix[i][j];
	}*/