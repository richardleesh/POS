#include "PosApp.h"
int main(){
  sict::PosApp app("posapp.txt", "bill.txt");
  app.run();
  return 0;
}
