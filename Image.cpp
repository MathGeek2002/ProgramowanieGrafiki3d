/*
  Utworzono 05-06-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
 */
#include "Image.h"

Image::Image(const char *name){
  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(name,0);// sprawdzamy i
  //pobieramy typ pliku
  img = FreeImage_Load(format,name);// ladujemy plik o danym formacie
  bPP =  FreeImage_GetBPP(img);// sprawdzamy liczbe bitow na piksel
  if( bPP == 32 ){
    img32 = img;// jesli wczytany obrazek jest w 32 bpp to nic nie
    //trzeba robic
  }else{// w przeciwnym wypadku konwertujemy do 32 bpp
    img32 = FreeImage_ConvertTo32Bits(img);
  }
  w = FreeImage_GetWidth(img32);// pobieramy wysokosc
  h = FreeImage_GetHeight(img32);// pobieramy szerokosc
  tex = FreeImage_GetBits(img32);// pobieramy wskaznik do danych pikseli
}

Image::~Image(){
  FreeImage_Unload(img32);// zwalniamy pamiec z obrazkiem
  if( bPP != 32 ) FreeImage_Unload(img);// zwalniamy pamiec na obrazek po
  // konwersji
}
