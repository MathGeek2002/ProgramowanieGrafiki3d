#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Sphere::Sphere(int nx_, int nz_, float radius_,glm::vec3 color_ ) : nx(nx_), nz(nz_) , radius(radius_), color(color_)
{
    Create();

    Material *material = new UniformMaterial(
      color.r, color.g, color.b, // diffuse
      128.f,    // shininess
      0.f, 0.f, 0.f,  // ambient
      0.2f, 0.2f, 0.2f
    );

    type = MATERIAL;
    isMaterial = true;

    materials = new Material* [nMeshes];
    for( int i = 0; i < nMeshes; i++ )
      materials[i] = material;
}

Sphere::~Sphere()
{
  delete meshes[0];
  delete [] meshes;

  if( isMaterial )
    delete materials[0];
  delete [] materials;
}


glm::vec3 Sphere::GetPointOnSphere(float phi_, float theta_)
{
    float x = radius * glm::cos(phi_) * glm::sin(theta_);
    float y = radius * glm::cos(theta_);
    float z = radius * glm::sin(phi_) * glm::sin(theta_);

    return glm::vec3(x,y,z);
}

int Sphere::getId(int x,int z)
{
    return z * nx + x + 1;
}

float Sphere::theta(int i)
{
    return (glm::pi<float>() / nz) * i; 
}

float Sphere::phi(int i)
{
    return (2.f * glm::pi<float>() / nx) * i;
}

glm::vec2 Sphere::CalculateUV(glm::vec3 point)
{
    float u = 0.5f + atan2(point.x, point.z) / (2 * glm::pi<float>());
    float v = 0.5f - asin(point.y / radius) / glm::pi<float>();

    return glm::vec2(u,v);
}

void Sphere::Create()
{
    nMeshes = 1;
    meshes = new Mesh* [1];

    int nVertices = 2 + nx * (nz - 1);
    int nIndices = (nz - 2) * nx * 6 + nx * 6;

    int indicesCounter = 0;

    Vertex *vertices = new Vertex [nVertices];
    unsigned int *indices = new unsigned int [nIndices];

    for( int i = 0; i < nz - 2; i++ ){
        for( int j = 0; j < nx; j++ )
        {
            size_t k =  getId(  j,            i );
            size_t k2 = getId( (j + 1) % nx,  i );
            size_t k3 = getId(  j,           (i + 1) % nz );
            size_t k4 = getId( (j + 1) % nx, (i + 1) % nz );

            glm::vec3 v =  GetPointOnSphere( phi(j),            theta(i + 1) );
            glm::vec3 v2 = GetPointOnSphere( phi((j + 1) % nx), theta(i + 1) );
            glm::vec3 v3 = GetPointOnSphere( phi(j),            theta((i + 2) % nz) );
            glm::vec3 v4 = GetPointOnSphere( phi((j + 1) % nx), theta((i + 2) % nz) );

            vertices[k].position = v;
            vertices[k2].position = v2;
            vertices[k3].position = v3;
            vertices[k4].position = v4;

            vertices[k].normal = glm::normalize(v);
            vertices[k2].normal = glm::normalize(v2);
            vertices[k3].normal = glm::normalize(v3);
            vertices[k4].normal = glm::normalize(v4);

            indices[indicesCounter++] = k;
            indices[indicesCounter++] = k2;
            indices[indicesCounter++] = k3;

            indices[indicesCounter++] = k2;
            indices[indicesCounter++] = k4;
            indices[indicesCounter++] = k3;

            float r = 1.f;
            float g = 1.f;
            float b = 1.f;

            vertices[k].color = color;
            vertices[k2].color = color;
            vertices[k3].color = color;
            vertices[k4].color = color;
        }
    }

    for(int i = 0;i < nx; i++)
    {
        size_t k = 0;
        size_t k2 = getId(i, 1);
        size_t k3 = getId((i + 1) % nx, 1);

        glm::vec3 v =  GetPointOnSphere( phi(0),             theta(0) );
        glm::vec3 v2 = GetPointOnSphere( phi(k2),            theta(1) );
        glm::vec3 v3 = GetPointOnSphere( phi(k3),            theta(1) );

        vertices[k].position = v;
        vertices[k2].position = v2;
        vertices[k3].position = v3;

        vertices[k].normal = glm::normalize(v);
        vertices[k2].normal = glm::normalize(v2);
        vertices[k3].normal = glm::normalize(v3);

        vertices[k].color = color;

        indices[indicesCounter++] = k;
        indices[indicesCounter++] = k3;
        indices[indicesCounter++] = k2;

        k = nx * (nz - 1) + 1;
        k2 = getId(i, nz - 2);
        k3 = getId((i + 1) % nx, nz - 2);

        vertices[k].color = color;

        v =  GetPointOnSphere( phi(nx),             theta(nz) );
        v2 = GetPointOnSphere( phi(i),            theta(nz - 1) );
        v3 = GetPointOnSphere( phi((i + 1) % nx),            theta(nz - 1) );

        vertices[k].position = v;
        vertices[k2].position = v2;
        vertices[k3].position = v3;

        vertices[k].normal = glm::normalize(v);
        vertices[k2].normal = glm::normalize(v2);
        vertices[k3].normal = glm::normalize(v3);

        indices[indicesCounter++] = k;
        indices[indicesCounter++] = k2;
        indices[indicesCounter++] = k3;
    }

    for(int i = 0;i < nVertices; i++)
        vertices[i].texcoord = CalculateUV( vertices[i].position );

    meshes[0] = new Mesh(nVertices,
        vertices, nIndices, indices);

    delete [] vertices;
    delete [] indices;
}