#include <garop.hpp>

void main()
{ // загрузить данные из файла gaData.dat
  loadDataFromFile("gaData.dat");
  // проинициализировать переменные
  setParameters();
  // показать данные на экране
  printDataToScreen();
  getch();
  // показать график F(x)
//   printCriteriaGraph();
   criteriaGraphDetails();
   criteriaGraph();
}
