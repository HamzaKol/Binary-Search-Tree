#ifndef STABLO_CPP
#define STABLO_CPP

#include "stablo.h"


template <typename Tip>
bool Stablo<Tip>::FindRek(Tip element, Cvor *cvor) {
    if (cvor->element == element) return true;
    if(element < cvor->element){
        if(cvor->ld != nullptr) return FindRek(element, cvor->ld);
        else return false;
    }
    else{
        if(cvor->dd != nullptr) return FindRek(element, cvor->dd);
        else return false;
    }
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::FindCvor(Tip element) {
  Cvor *trenutni = korijen;
  while(trenutni != nullptr) {
    if(trenutni->element == element)
        return trenutni;
    if(trenutni->element > element)
        trenutni = trenutni->ld;
    else trenutni = trenutni->dd;
  }
  return nullptr;
}

template <typename Tip>
void Stablo<Tip>::Insert(Tip element) {
  if(korijen == nullptr) {
    korijen = new Cvor(element);
    korijen->prioritet = rand();
    velicina = 1;
    return;
  }

  Cvor *trenutni = korijen;
  while(trenutni != nullptr) {
    if(trenutni->element == element)
        return;
    if(trenutni->element > element) {
       if(trenutni->ld != nullptr)
         trenutni = trenutni->ld;
       else {
         trenutni->ld = new Cvor(element, trenutni);
         velicina++;
         trenutni = trenutni->ld;
         break;
       }
    }
    else {
       if(trenutni->dd != nullptr)
         trenutni = trenutni->dd;
       else {
         trenutni->dd = new Cvor(element, trenutni);
         velicina++;
         trenutni = trenutni->dd;
         break;
       }
    }

  }
  if(trenutni->rod->ld == trenutni) PopraviStablo(trenutni, true);
  else PopraviStablo(trenutni, false);
}

template <typename Tip>
void Stablo<Tip>::Insert2(Tip element, int prio) {
  if(korijen == nullptr) {
    korijen = new Cvor(element);
    korijen->prioritet = rand();
    velicina = 1;
    return;
  }

  Cvor *trenutni = korijen;
  while(trenutni != nullptr) {
    if(trenutni->element == element)
        return;
    if(trenutni->element > element) {
       if(trenutni->ld != nullptr)
         trenutni = trenutni->ld;
       else {
         trenutni->ld = new Cvor(element, trenutni);
         velicina++;
         trenutni = trenutni->ld;
         break;
       }
    }
    else {
       if(trenutni->dd != nullptr)
         trenutni = trenutni->dd;
       else {
         trenutni->dd = new Cvor(element, trenutni);
         velicina++;
         trenutni = trenutni->dd;
         break;
       }
    }

  }

  FindCvor(element)->prioritet = prio;

  if(trenutni->rod->ld == trenutni) PopraviStablo(trenutni, true);
  else PopraviStablo(trenutni, false);


}

template <typename Tip>
void Stablo<Tip>::IspisiRek(Cvor* pointer){
    if(pointer != nullptr){
        if(pointer->ld != nullptr) IspisiRek(pointer->ld);
        if(pointer->dd != nullptr) IspisiRek(pointer->dd);
        std::cout<<"Broj je: "<<pointer->element<<"."<<std::endl;
        std::cout<<"    Prioritet mu je : "<<pointer->prioritet<<"."<<std::endl;
        if(pointer->rod != nullptr) std::cout<<"    Roditelj mu je: "<<pointer->rod->element<<"."<<std::endl;
        if(pointer->ld != nullptr) std::cout<<"    Lijevo dijete mu je: "<<pointer->ld->element<<"."<<std::endl;
        if(pointer->dd != nullptr) std::cout<<"    Desno dijete mu je: "<<pointer->dd->element<<"."<<std::endl;
    }
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiNajmanji(Cvor* pointer){
    while(true){
    if(pointer->ld == nullptr) return pointer;
    pointer = pointer->ld;
    }
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiNajveci(Cvor* pointer){
    while(true){
    if(pointer->dd == nullptr) return pointer;
    pointer = pointer->dd;
    }
}


template <typename Tip>
void Stablo<Tip>::PopraviStablo(Cvor* pointer, bool lijevi){
    if(pointer != korijen){
        if(pointer->prioritet > pointer->rod->prioritet){
            if(lijevi){
                pointer->rod->ld = pointer->dd;
                if(pointer->dd != nullptr) pointer->dd->rod = pointer->rod;
                pointer->dd = pointer->rod;
                pointer->rod = pointer->dd->rod;
                pointer->dd->rod = pointer;
                if(pointer->rod != nullptr){
                    if(pointer->rod->element > pointer->element) pointer->rod->ld = pointer;
                    else pointer->rod->dd = pointer;
                }
                else korijen = pointer;
            }
            else{
                pointer->rod->dd = pointer->ld;
                if(pointer->ld != nullptr) pointer->ld->rod = pointer->rod;
                pointer->ld = pointer->rod;
                pointer->rod = pointer->ld->rod;
                pointer->ld->rod = pointer;
                if(pointer->rod != nullptr){
                    if(pointer->rod->element > pointer->element) pointer->rod->ld = pointer;
                    else pointer->rod->dd = pointer;
                }
                else korijen = pointer;
                }
            }
        else return;
    }
    else return;

    if(pointer != korijen){
    if(pointer->rod->ld == pointer) PopraviStablo(pointer, true);
    else PopraviStablo(pointer, false);
    }
}

template <typename Tip>
void Stablo<Tip>::PopraviStabloObratno(Cvor* za_brisanje){

    while(true){
        if(za_brisanje->ld != nullptr){
            if(za_brisanje->dd != nullptr){
                if((za_brisanje->ld->prioritet >= za_brisanje->dd->prioritet)
                            && (za_brisanje->ld->prioritet > za_brisanje->prioritet)) PopraviStablo(za_brisanje->ld, true);
                else if (za_brisanje->dd->prioritet > za_brisanje->prioritet) PopraviStablo(za_brisanje->dd, false);
                else break;
                }
                else if (za_brisanje->ld->prioritet > za_brisanje->prioritet) PopraviStablo(za_brisanje->ld, true);
                else break;
            }
            else if ((za_brisanje->dd != nullptr) && (za_brisanje->dd->prioritet > za_brisanje->prioritet))
                PopraviStablo(za_brisanje->dd, false);
            else break;
        }
    }
template <typename Tip>
void Stablo<Tip>::Brisanje(Tip element){
      if(!Find(element)) return;
      Cvor* za_brisanje = FindCvor(element);
      if(za_brisanje->element != korijen->element){
        BrisanjeRek(za_brisanje);
      }
      else{
        BrisanjeKorijena(za_brisanje);
      }
}
template <typename Tip>
void Stablo<Tip>::BrisanjeKorijena(Cvor* za_brisanje){
    if(za_brisanje->ld == nullptr && za_brisanje->dd == nullptr){
        korijen = nullptr;
        delete za_brisanje;
        velicina--;
        za_brisanje = nullptr;
    }
    else if(za_brisanje->ld != nullptr && za_brisanje->dd == nullptr){
        korijen = za_brisanje->ld;
        za_brisanje->ld->rod = nullptr;
        delete za_brisanje;
        za_brisanje = nullptr;
        velicina--;
    }
    else if(za_brisanje->ld == nullptr && za_brisanje->dd != nullptr){
        korijen = za_brisanje->dd;
        za_brisanje->dd->rod = nullptr;
        delete za_brisanje;
        za_brisanje = nullptr;
        velicina--;
    }
    else{
        Cvor* zamjena = NadjiNajmanji(za_brisanje->dd);
        za_brisanje->element = zamjena->element;
        za_brisanje->prioritet = zamjena->prioritet;
        BrisanjeRek(zamjena);
        zamjena = nullptr;
        PopraviStabloObratno(za_brisanje);
        za_brisanje = nullptr;
    }
}
template <typename Tip>
void Stablo<Tip>::BrisanjeRek(Cvor* za_brisanje){
    if(za_brisanje->dd == nullptr && za_brisanje->ld == nullptr){
        if(za_brisanje->rod->ld == za_brisanje) za_brisanje->rod->ld = nullptr;
        else za_brisanje->rod->dd = nullptr;
        delete za_brisanje;
        za_brisanje = nullptr;
        velicina--;
    }
    else if(za_brisanje->dd != nullptr && za_brisanje->ld == nullptr){
        if(za_brisanje->rod->ld == za_brisanje) za_brisanje->rod->ld = za_brisanje->dd;
        else za_brisanje->rod->dd = za_brisanje->dd;
        za_brisanje->dd->rod = za_brisanje->rod;
        delete za_brisanje;
        za_brisanje = nullptr;
        velicina--;
    }
    else if(za_brisanje->dd == nullptr && za_brisanje->ld != nullptr){
        if(za_brisanje->rod->ld == za_brisanje) za_brisanje->rod->ld = za_brisanje->ld;
        else za_brisanje->rod->dd = za_brisanje->ld;
        za_brisanje->ld->rod = za_brisanje->rod;
        delete za_brisanje;
        za_brisanje = nullptr;
        velicina--;
    }
    else{
        Cvor* zamjena = NadjiNajmanji(za_brisanje->dd);
        za_brisanje->element = zamjena->element;
        za_brisanje->prioritet = zamjena->prioritet;
        BrisanjeRek(zamjena);
        zamjena = nullptr;
        PopraviStabloObratno(za_brisanje);
        za_brisanje = nullptr;
    }
}

template <typename Tip>
std::pair<Stablo<Tip>, Stablo<Tip>> Razdvajanje(Stablo<Tip> s, Tip k){
    Stablo<Tip> s1;
    Stablo<Tip> s2;
    s.VratiDvaStabla(s1, s2, k);
    std::pair <Stablo<Tip>, Stablo<Tip>> p(s1, s2);
    return p;
}

template <typename Tip>
void Stablo<Tip>::VratiDvaStabla(Stablo<Tip> &s1, Stablo<Tip> &s2, Tip k){
    Insert2(k, korijen->prioritet+100000000000);
    s1.Insert(0);
    s2.Insert(0);
    Cvor* k1 = korijen->ld;
    Cvor* k2 = korijen->dd;
    s1.Promijeni(k1);
    s2.Promijeni(k2);
}
template <typename Tip>
void Stablo<Tip>::Promijeni(Cvor* pointer){
    korijen = pointer;
}

template <typename Tip>
Stablo<Tip> Spajanje(Stablo<Tip> s1, Stablo<Tip> s2){
    if(s1.korijen == nullptr) return s2;
    if(s2.korijen == nullptr) return s1;
    Stablo<Tip> s;
    Tip a = s.SklopiIh(s1, s2);
    s.PopraviStabloObratno(s.FindCvor(a));
    s.Brisanje(a);
    return s;
}

template <typename Tip>
Tip Stablo<Tip>::SklopiIh(Stablo<Tip> &s1, Stablo<Tip> &s2){
    Tip broj = s1.NadjiNajveci(s1.VratiKorijen())->element;
    Insert2(broj, -1);
    korijen->ld = s1.VratiKorijen();
    s1.VratiKorijen()->rod = korijen;
    korijen->dd = s2.VratiKorijen();
    s2.VratiKorijen()->rod = korijen;
    return broj;
}

#endif // STABLO_CPP
