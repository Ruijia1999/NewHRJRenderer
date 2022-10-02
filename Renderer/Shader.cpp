#include "Shader.h"

HRJRenderer::Vector4 HRJRenderer::Shader::FlatShading::vertexShader(const HRJRenderer::Vector3& i_vec) {
	return Vector4(i_vec, 1);
}
void HRJRenderer::Shader::FlatShading::fragmentShader(const HRJRenderer::Vector3& i_vec, COLORREF& i_color, HRJRenderer::Vector3 normal, const Light::LightSetting& lightsetting) {
	i_color += COLORREF(RGB(1, 0, 0));
}
