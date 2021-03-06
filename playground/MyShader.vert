#version 330 core

// Input vertex data, different for all executions of this shader.
// layout(location=??)用来标明是第几个attribute
// 配合opengl方面的glvertexAttribPointer可以告知OpenGL这是什么类型的属性
// glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v)可以查看最大属性编号
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

// Uniform变量是shader中只能用不能改的从外部(OpenGL)传入的“常量”
// attribute 只能在vertex shader中使用，fragment里不行
// 通常存顶点坐标、法线、纹理坐标、纹理颜色等
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPosition_worldspace;


//  这个会自动在每个Fragment着色器中获得
// 将纹理中的坐标uv传过去
// 顶点位置
// 视线方向
// 法线方向
// 光线方向
out vec2 uv;
out vec3 vertexPosition_worldspace;
out vec3 eyeDirection_cameraspace;
out vec3 normalDirection_cameraspace;
out vec3 lightDirection_cameraspace;


void main(){
	// 在Vertex Shader里至少要计算gl_Position
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);

	// 如果使用DDS纹理，因为DirectX与TGA的纵坐标v方向相反，因此在定点着色器应该反过来
	//uv = vertexUV;
	uv = vec2(vertexUV[0], 1 - vertexUV[1]);
	vertexPosition_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

	vec3 vertexPosition_cameraspace = (V * vec4(vertexPosition_modelspace, 1)).xyz;
	lightDirection_cameraspace = normalize((V * vec4(lightPosition_worldspace, 1)).xyz - vertexPosition_cameraspace); 
	eyeDirection_cameraspace = normalize(vec3(0, 0, 0) - vertexPosition_cameraspace);

	normalDirection_cameraspace = normalize((V * M * vec4(vertexNormal_modelspace, 0)).xyz);
}