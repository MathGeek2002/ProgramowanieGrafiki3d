#include "Materials.h"
#include "Image.h"

UniformMaterial::UniformMaterial(MaterialType materialType)
{
  if ( materialType == GREEN_RUBBER ) {
    diffuse = glm::vec3(0.4f, 0.5f, 0.4f);
    shininess = 0.078125f * 128.f;
    ambient = glm::vec3(0.0f, 0.05f, 0.0f);
    specular = glm::vec3(0.04f, 0.7f, 0.04f);
  } else if ( materialType == COPPER ) {
    diffuse = glm::vec3(0.7038f, 0.27048, 0.0828f);
    shininess = 0.1f * 128.f;
    ambient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
    specular = glm::vec3(0.256777f, 0.137622f, 0.086014f);
  } else if ( materialType == GOLD ) {
    diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
    shininess = 0.4f * 128.f;
    ambient = glm::vec3(0.24725f,	0.1995f, 0.0745f);
    specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
  }
}


TextureMaterial::TextureMaterial(
    const char *difName,
    float shi,
    const char *speName,
    const char *ambName
  ) : shininess(shi)
{
  diffuse = 0;
  specular = 0;
  ambient = 0;

  Image *tex2d = new Image(difName);

  glGenTextures(1,&diffuse);
  glBindTexture(GL_TEXTURE_2D, diffuse);
  glTexImage2D(
    GL_TEXTURE_2D,0,GL_RGBA,tex2d->w,tex2d->h,0,
    GL_BGRA,GL_UNSIGNED_BYTE,tex2d->tex
  );
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(
    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_LINEAR_MIPMAP_LINEAR
  );

  if( speName == nullptr ){
    glGenTextures(1,&specular);
    glBindTexture(GL_TEXTURE_2D, specular);
    glTexImage2D(
      GL_TEXTURE_2D,0,GL_RGBA,tex2d->w,tex2d->h,0,
      GL_BGRA,GL_UNSIGNED_BYTE,tex2d->tex
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
      GL_LINEAR_MIPMAP_LINEAR
    );
  }

  if( ambName == nullptr ){
    glGenTextures(1,&ambient);
    glBindTexture(GL_TEXTURE_2D, ambient);
    glTexImage2D(
      GL_TEXTURE_2D,0,GL_RGBA,tex2d->w,tex2d->h,0,
      GL_BGRA,GL_UNSIGNED_BYTE,tex2d->tex
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
      GL_LINEAR_MIPMAP_LINEAR
    );
  }

  delete tex2d;

  if( speName != nullptr ){
    tex2d = new Image(speName);
    glGenTextures(1,&specular);
    glBindTexture(GL_TEXTURE_2D, specular);
    glTexImage2D(
      GL_TEXTURE_2D,0,GL_RGBA,tex2d->w,tex2d->h,0,
      GL_BGRA,GL_UNSIGNED_BYTE,tex2d->tex
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
      GL_LINEAR_MIPMAP_LINEAR
    );
    delete tex2d;
  }

  if( ambName != nullptr ){
    tex2d = new Image(ambName);
    glGenTextures(1,&ambient);
    glBindTexture(GL_TEXTURE_2D, ambient);
    glTexImage2D(
      GL_TEXTURE_2D,0,GL_RGBA,tex2d->w,tex2d->h,0,
      GL_BGRA,GL_UNSIGNED_BYTE,tex2d->tex
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
      GL_LINEAR_MIPMAP_LINEAR
    );
    delete tex2d;
  }
}

TextureMaterial::~TextureMaterial()
{
  if(diffuse)
    glDeleteTextures(1,&diffuse);
  if(specular)
    glDeleteTextures(1,&specular);
  if(ambient)
    glDeleteTextures(1,&ambient);
}

void
TextureMaterial::SetMaterial(Shader* shader)
{
  shader->SetScalar1("material.ambient", 0);
  shader->SetScalar1("material.diffuse", 1);
  shader->SetScalar1("material.specular", 2);
  shader->SetScalar1("material.shininess", shininess);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, ambient);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, diffuse);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, specular);
}
