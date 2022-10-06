#include "FlatShader.h"

HRJRenderer::Vector3 HRJRenderer::FlatShader::vertexShader(const HRJRenderer::Vector3& i_vec, const Draw::ConstantBuffer& constantBuffer) {
	HRJRenderer::Vector4 vtx_Camera = constantBuffer.worldToCameraTransform * HRJRenderer::Vector4(i_vec, 1);
	HRJRenderer::Vector4 vtx_Projected = constantBuffer.cameraPerspectiveTransform * (vtx_Camera);
	vtx_Projected /= vtx_Projected.w;
	HRJRenderer::Vector3 vtx_View((vtx_Projected.x + 1) * 250, (-vtx_Projected.y + 1) * 250, (vtx_Projected.z + 1) * 250);
	return vtx_View;
}
COLORREF HRJRenderer::FlatShader::fragmentShader(Color& i_color, HRJRenderer::Vector3 normal, const Draw::ConstantBuffer& constantBuffer) {
	float intensity = abs(Math::GetAngel(normal, constantBuffer.lightSetting.diffuseLight.direction));
	Color color = Color(1.0f, 1.0f, 1.0f, 1) * constantBuffer.lightSetting.diffuseLight.lightColor;
	color = color * intensity;
	return color.ToCOLORREF();
}
