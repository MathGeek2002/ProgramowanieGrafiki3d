#!/usr/bin/env python

my_libs = ['GL', 'GLU', 'GLEW', 'SDL2', 'freeimage']

env = Environment(
            LIBS = my_libs
            )

env.sources = []
env.sources += env.Object(['RenderEngine.cpp',
                           'Shader.cpp',
                           'Camera.cpp',
                           'View.cpp',
                           'Transform.cpp',
                           'Mesh.cpp',
                           'Model.cpp',
                           'Plane.cpp',
                           'Box.cpp',
                           'Lights.cpp',
                           'Materials.cpp',
                           'Image.cpp',
                           'Sphere.cpp'])


env.Program(target = 'Program',
            source = env.sources + env.Object('Program.cpp')
            )

