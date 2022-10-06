#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Math/Math.h"

namespace HRJRenderer {
	class Model
	{
    public:
        std::vector<Vector3> m_verts;     // array of vertices
        std::vector<Vector2> m_uv;        // array of tex coords
        std::vector<Vector3> m_norms;     // array of normal vectors
        std::vector<Vector3> m_facet_vrt;
        std::vector<Vector3> m_facet_tex;  // indices in the above arrays per triangle
        std::vector<Vector3> m_facet_nrm;
        //TGAImage m_diffusemap;         // diffuse color texture
        //TGAImage m_normalmap;          // normal map texture
        //TGAImage m_specularmap;        // specular map texture
        //void load_texture(const char* filename, const char* suffix, TGAImage& img);
    public:
        Model(const char* i_filename);
        Model();
        
    };
}


