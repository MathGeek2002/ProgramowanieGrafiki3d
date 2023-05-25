/*
  Utworzono 05-06-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <FreeImage.h>
#include <GL/glew.h>

class Image {
  FIBITMAP *img;// wskaznik do obrazka
  FIBITMAP *img32;// chcemy pracowac z tekstura 32 bitowa
  int bPP;
public:
  GLubyte *tex;
  int w, h;
  Image(const char *name);
  ~Image();
};

#endif
