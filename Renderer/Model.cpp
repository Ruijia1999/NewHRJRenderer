#include "Model.h"
HRJRenderer::Model::Model(const char* i_filename): m_verts(), m_uv(), m_norms(), m_facet_nrm(), m_facet_tex(), m_facet_vrt() {
    std::ifstream inStream;
    inStream.open(i_filename, std::ifstream::in);
    if (inStream.fail()) return;
    std::string line;
    while (!inStream.eof()) {
        std::getline(inStream, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vector3 vertex;
            for (int i = 0; i < 3; i++) iss >> vertex[i];
            m_verts.push_back(vertex);
        }
        else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vector3 n;
            float j;
            int q;
            for (int i = 0; i < 3; i++) iss >> n[i];
            m_norms.push_back(n.Normalize());
        }
        else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vector2 uv;
            for (int i = 0; i < 2; i++) iss >> uv[i];
            m_uv.push_back(uv);
        }
        else if (!line.compare(0, 2, "f ")) {
            int f, t, n;
            iss >> trash;
            int cnt = 0;
            Vector3 face;
            Vector3 texture;
            Vector3 normal;
            while (iss >> f >> trash >> t >> trash >> n) {
                face[cnt] = f;
                texture[cnt] = t;
                normal[cnt] = n;
                cnt++;
            }
            if (3 != cnt) {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                inStream.close();
                return;
            }
            m_facet_vrt.push_back(face);
            m_facet_tex.push_back(texture);
            m_facet_nrm.push_back(normal);
        }
    }
    inStream.close();
}