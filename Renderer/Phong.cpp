#include "Phong.h"
HRJRenderer::Vector3 HRJRenderer::PhongShader::vertexShader(const HRJRenderer::Vector3& i_vec, const HRJRenderer::Vector3& i_normal, int index, const Color& i_color, const Draw::ConstantBuffer& constantBuffer) {
	HRJRenderer::Vector4 vtx_Camera = constantBuffer.worldToCameraTransform * HRJRenderer::Vector4(i_vec, 1);
	HRJRenderer::Vector4 vtx_Projected = constantBuffer.cameraPerspectiveTransform * (vtx_Camera);
	vtx_Projected /= vtx_Projected.w;
	float intensity = abs(Math::GetAngel(i_normal, constantBuffer.lightSetting.diffuseLight.direction));
	Color color = i_color * constantBuffer.lightSetting.diffuseLight.lightColor;
	color = color * intensity;
	colors[index] = color;
	HRJRenderer::Vector3 vtx_View((vtx_Projected.x + 1) * 250, (-vtx_Projected.y + 1) * 250, (vtx_Projected.z + 1) * 250);
	return vtx_View;
}
COLORREF HRJRenderer::PhongShader::fragmentShader( const HRJRenderer::Vector3& barycentric, const Draw::ConstantBuffer& constantBuffer) {
	Color color0 = colors[0] * barycentric.x;
	Color color1 = colors[1] * barycentric.y;
	Color color2 = colors[2] * barycentric.z;
	return (color0 + color1 + color2).ToCOLORREF();
}
