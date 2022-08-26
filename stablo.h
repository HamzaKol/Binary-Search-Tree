#ifndef STABLO_H
#define STABLO_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <utility>

template <typename Tip>
class Stablo {
  struct Cvor {
    Tip element;
    int prioritet;
    Cvor *rod, *ld, *dd;
    Cvor(Tip element, Cvor *rod = nullptr, Cvor *ld = nullptr, Cvor *dd = nullptr, int prioritet = rand()):
        element(element), rod(rod), ld(ld), dd(dd), prioritet(prioritet) {}
  };

  Cvor *korijen;
  int velicina;
  bool FindRek(Tip element, Cvor *cvor);
  void IspisiRek(Cvor* pointer);
  Cvor* FindCvor(Tip vrijednost);
  Cvor* NadjiNajmanji(Cvor* pointer);
  Cvor* NadjiNajveci(Cvor* pointer);
  void BrisanjeRek(Cvor* za_brisanje);
  void BrisanjeKorijena(Cvor* za_brisanje);
  void PopraviStabloObratno(Cvor* za_brisanje);
  void Insert2(Tip element, int prioritet);
  void VratiDvaStabla(Stablo<Tip> &s1, Stablo<Tip> &s2, Tip k);
  void Promijeni(Cvor* pointer);
  Tip SklopiIh(Stablo<Tip> &s1, Stablo<Tip> &s2);
  Cvor* VratiKorijen(){ return korijen;}

  public:

  void Ispisi(){IspisiRek(korijen);}
  Stablo():korijen(nullptr),velicina(0) {}
  void Insert(Tip element);
  bool Find(Tip element){return FindRek(element, korijen);}
  void PopraviStablo(Cvor* pointer, bool lijevi);
  void Brisanje(Tip element);
  template <typename Tp>
  friend std::pair<Stablo<Tp>, Stablo<Tp>> Razdvajanje(Stablo<Tp> s, Tp k);
  template <typename Tp>
  friend Stablo<Tp> Spajanje(Stablo<Tp> s1, Stablo<Tp> s2);
};

#include "stablo.cpp"

#endif // STABLO_H
