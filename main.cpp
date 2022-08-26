#include <iostream>
#include "stablo.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <utility>

using namespace std;

int main() {
  srand (time(NULL));
  Stablo<int> s;
  s.Insert(33);
  s.Insert(13);
  s.Insert(56);
  s.Insert(23);
  s.Insert(34);
  s.Insert(7);
  s.Insert(38);
  s.Insert(39);
  s.Insert(24);
  s.Insert(11);
  cout<<"----------------------------"<<endl;
  cout<<"Prije Brisanja: "<<endl;
  cout<<"----------------------------"<<endl;
  s.Ispisi();
  s.Brisanje(33);
  s.Brisanje(13);
  s.Brisanje(56);
  s.Brisanje(23);
  cout<<"----------------------------"<<endl;
  cout<<"Nakon Brisanja: "<<endl;
  cout<<"----------------------------"<<endl;
  s.Ispisi();

  std::pair <Stablo<int>, Stablo<int>> p;
  int k = 15;
  p = Razdvajanje(s, k);
  cout<<"----------------------------"<<endl;
  cout<<"Svi manji od "<<k<<" su: "<<endl;
  cout<<"----------------------------"<<endl;
  p.first.Ispisi();
  cout<<endl;
  cout<<"----------------------------"<<endl;
  cout<<"Svi veci od "<<k<<" su: "<<endl;
  cout<<"----------------------------"<<endl;
  p.second.Ispisi();
  s = Spajanje(p.first, p.second);
  cout<<"----------------------------"<<endl;
  cout<<"Nakon spajanja: "<<endl;
  cout<<"----------------------------"<<endl;
  s.Ispisi();
}
