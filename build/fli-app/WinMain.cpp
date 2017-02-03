#include <iostream>
#include <functional>
#include <sstream>
#include <fstream>

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <glew\glew.h>
#include <gl/GL.h>

#include <fli-core\clock.hpp>
#include <fli-core\scene.hpp>
#include <fli-render\window.hpp>
#include <fli-opengl\shader.hpp>
#include <fli-opengl\program.hpp>
#include <fli-opengl\context.hpp>
#include <fli-opengl\opengl.hpp>
#include <fli-opengl\buffer.hpp>
#include <fli-opengl\mesh_factory.hpp>
#include <fli-opengl\mesh_descriptor.hpp>
#include <fli-opengl\static_mesh.hpp>
#include <fli-opengl\vertex_attribute_descriptor.hpp>
#include <fli-opengl\program_factory.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

opengl::OpenGlContext context;
opengl::up_Program program;
opengl::up_Shader vertexShader;
opengl::up_Shader fragmentShader;
opengl::StaticMesh* mesh;
opengl::StaticInstancedMesh* inMesh;

std::vector<glm::vec3> instancePositions;
std::vector<glm::vec2> instanceVelocity;

std::string vshader = "../../src/glsl/vs.glsl";

std::string fshader = "../../src/glsl/fs.glsl";

glm::vec3 vertices[3] = {
	glm::vec3(-2.0f, -2.0f, 0.0f),
	glm::vec3(2.0f, -2.0f, 0.0f),
	glm::vec3(0.0f, 2.0f, 0.0f)
};

glm::vec4 colors[3] = {
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
};

opengl::AttributeVariable instPosition;

glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
opengl::UniformVariable& ucolor = opengl::UniformVariable();
opengl::UniformVariable& projection = opengl::UniformVariable();

glm::mat4 proj = glm::ortho(0.0, 1000.0, 0.0, 1000.0);

void CheckErrors() {
	opengl::OpenGlError err = opengl::gl::GetErrors();
	if (err.IsError()) {
		std::cout << err.ToString() << std::endl;
		throw std::exception();
	}
}

bool Setup() {
	wglSwapIntervalEXT(0);

	std::ifstream vsStream = std::ifstream(vshader);
	vsStream.open(vshader);
	std::ifstream fsStream = std::ifstream(fshader);
	fsStream.open(fshader);

	opengl::ShaderSource vertexSource = opengl::ShaderSource(std::ifstream(vshader));
	opengl::ShaderSource fragmentSource = opengl::ShaderSource(std::ifstream(fshader));

	fsStream.close();
	vsStream.close();

	try {
		vertexShader = opengl::program_factory::CreateVertexShader(vertexSource);
		fragmentShader = opengl::program_factory::CreateFragmentShader(fragmentSource);
		std::vector<opengl::up_Shader> shaders;
		shaders.push_back(std::move(vertexShader));
		shaders.push_back(std::move(fragmentShader));
		program = opengl::program_factory::CreateProgram(std::move(shaders));
	}
	catch (opengl::shader_compilation_exception ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
	catch (opengl::program_link_exception ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}

	CheckErrors();

	const opengl::AttributeVariable& position = program->GetAttributeVariable("position");
	const opengl::AttributeVariable& color = program->GetAttributeVariable("color");
	instPosition = program->GetAttributeVariable("inst_position");

	ucolor = program->GetUniformVariable("ucolor");
	projection = program->GetUniformVariable("projection");

	opengl::MeshDescriptor meshDesc;
	meshDesc.Vertices = std::vector<glm::vec3>(vertices, std::end(vertices));
	meshDesc.PositionVariable = position;

	opengl::VertexAttributeDescriptor colorDesc;
	colorDesc.pAttributes = &colors[0];
	colorDesc.Size = sizeof(colors);
	colorDesc.AttributeVariable = color;
	meshDesc.AttributeDescriptors.push_back(colorDesc);

	mesh = opengl::mesh_factory::CreateStaticMesh(meshDesc);

	CheckErrors();

	std::vector<opengl::VertexAttributeDescriptor> descriptors;

	opengl::VertexAttributeDescriptor instancePositionDesc;
	instancePositionDesc.AttributeVariable = instPosition;
	instancePositionDesc.pAttributes = (void*)1;
	instancePositionDesc.Size = 0;

	descriptors.push_back(instancePositionDesc);

	inMesh = opengl::mesh_factory::CreateStaticInstancedMesh(meshDesc, descriptors);

	std::srand(time(NULL));

	for (float i = 0; i < 200; i++) {
		for (float j = 0; j < 200; j++) {
			glm::vec2 V0(0.0f, 0.0f);
			V0.x = -(j - 100) * 0.001f;
			V0.y = (i - 100) * 0.001f;

			float x = (float)(rand() % 10000) / 10.0f;
			float y = (float)(rand() % 10000) / 10.0f;


			instancePositions.push_back(glm::vec3(x, y, 0.0f));
			instanceVelocity.push_back(V0);
		}
	}

	return true;
}

glm::vec2 CalculateAccelerationToPoint(
	float gravConstant, 
	float mass1, float mass2, 
	glm::vec2 pos1, glm::vec2 pos2) {
	float distance = glm::distance(pos1, pos2);
	if (distance < 5.0)
		distance = 5.0f;

	float force = (gravConstant * mass1 * mass2) / (distance * distance);

	float acceleration = force / mass2;

	glm::vec2 dir = glm::normalize(pos1 - pos2);
	glm::vec2 accelVec = acceleration * dir;

	return accelVec;
}

glm::vec2 center = glm::vec2(428.0f, 500.0f);

void Render() {
	program->Use();

	program->SetUniform(ucolor, color);
	program->SetUniform(projection, { proj });
	mesh->Render();

	for (unsigned int i = 0; i < instancePositions.size(); i++) {
		instancePositions[i].x += instanceVelocity[i].x;
		instancePositions[i].y += instanceVelocity[i].y;

		glm::vec2 pos = glm::vec2(instancePositions[i].x, instancePositions[i].y);
		glm::vec2 accel = CalculateAccelerationToPoint(0.01f, 100.0f, 1.0f, center, pos);

		instanceVelocity[i] += accel;
	}

	opengl::InstanceUpdateData instanceData;
	instanceData.Attribute = instPosition;
	instanceData.pData = &instancePositions[0][0];
	instanceData.dataSize = (unsigned int)(sizeof(glm::vec3) * instancePositions.size());

	inMesh->SetInstancedData({ instanceData });
	inMesh->Render((unsigned int)instancePositions.size());
}

void ResizeDisplay(eWindowResize type, glm::uvec2 dim) {
	std::cout << "resize to: (" << dim.x << ", " << dim.y << ")." << std::endl;
	glViewport(0, 0, dim.x, dim.y);

	glm::vec2 span(1000.0f, 1000.0f);

	float aspect = (float)dim.x / (float)dim.y;

	if (aspect > 1) {
		span.x *= aspect;
	}
	else {
		span.y = span.x / aspect;
	}

	proj = glm::ortho(0.0f, span.x, 0.0f, span.y);
}

int main() {
	std::cout.sync_with_stdio(false);
	HINSTANCE hInstance = GetModuleHandle(0);
	gfx::render::Window w(hInstance, "fli-app-1", glm::uvec2(100, 100), glm::uvec2(1000, 1000));
	w.AddResizeWindowHandler(ResizeDisplay);


	opengl::OpenGlContext* c = w.GetOpenGlContext();
	if (!Setup()) {
		return (-1);
	}

	gfx::core::Clock clock;
	gfx::core::Clock::Timepoint t = clock.Now();
	gfx::core::Clock::Duration d = clock.TimeFromEpoch(t);

	int i = 0;

	glClearColor(0.390f, 0.582f, 0.926f, 1.0f);

	while (i++, !w.ShouldClose()) {
		w.ProcessMessages();

		opengl::gl::Clear(opengl::gl::Buffers::Color | opengl::gl::Buffers::Depth);

		Render();
		c->SwapBuffer();

		d = clock.TimeFromNow(t);
		if (i % 1000 == 0) {
			double s = d.Seconds();
			std::stringstream ss;
			ss << "fps: " << 1.0 / s;
			SetWindowText(w.GetHWnd(), TEXT(ss.str().c_str()));
		}
		t = clock.Now();
	}

}