
// Demo multi-dimensional arrays.
// See here: https://www.youtube.com/watch?v=gNgUMA_Ur0U&list=WL&index=16

#include <iostream>
using std::cout;
using std::endl;

// Passing a matrix declared on the stack is tricky.
// See here: https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
template<int n_rows, int n_cols>
void PrintMatrix(int matrix[n_rows][n_cols]) {
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void PrintMatrix(int** matrix, int n_rows, int n_cols) {
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void PrintRowMajor(int* data, int n_rows, int n_cols) {
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      cout << data[n_cols*i + j] << " ";
    }
    cout << endl;
  }
}

void PrintColumnMajor(int* data, int n_rows, int n_cols) {
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      cout << data[n_rows*j + i] << " ";
    }
    cout << endl;
  }
}

int main() {

  // Allocate on the stack.
  int stack_matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  PrintMatrix<2, 3>(stack_matrix);
  // Nothing to delete.

  // To allocate on the heap, first allocate int array pointers for each row. Then, 
  // allocate space for data across the columns for each.
  int** heap_matrix = new int*[2];
  heap_matrix[0] = new int[3]{10, 20, 30};
  heap_matrix[1] = new int[3]{40, 50, 60};
  // Or if you don't want to initialize...
  //for (int i = 0; i < 2; i++) { heap_matrix[i] = new int[3]; }
  PrintMatrix(heap_matrix, 2, 3);

  // Delete heap-allocated matrix data row by row, then delete the row pointers.
  for (int i = 0; i < 2; i++) { delete[] heap_matrix[i]; }
  delete[] heap_matrix;

  // This typical design means that each row is likely stored in different memory locations
  // leading to cache misses when accessing different rows.
  int* row_major = new int[2*3];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      row_major[3*i + j] = 100*(3*i + j + 1);
    }
  }
  PrintRowMajor(row_major, 2, 3);
  delete[] row_major; // easy to delete

  int* column_major = new int[2*3];
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 2; i++) {
      column_major[2*j + i] = 1000*(2*j + i + 1);
    }
  }
  PrintColumnMajor(column_major, 2, 3);
  delete[] column_major; // easy to delete
}
