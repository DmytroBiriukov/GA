#include <garop.hpp>

void main()
{ // ����㧨�� ����� �� 䠩�� gaData.dat
  loadDataFromFile("gaData.dat");
  // �ந��樠����஢��� ��६����
  setParameters();
  // �������� ����� �� �࠭�
  printDataToScreen();
  getch();
  // �������� ��䨪 F(x)
//   printCriteriaGraph();
   criteriaGraphDetails();
   criteriaGraph();
}
