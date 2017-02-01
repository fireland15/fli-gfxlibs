#include <iostream>
#include <functional>
#include <sstream>
#include <fstream>

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <fli-core\clock.hpp>
#include <fli-core\scene.hpp>
#include <fli-render\window.hpp>
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

opengl::GL gl;
opengl::OpenGlContext context;
opengl::Program program;
opengl::Shader vertexShader;
opengl::Shader fragmentShader;
opengl::MeshFactory meshFactory;
opengl::StaticMesh mesh;
opengl::StaticInstancedMesh inMesh;

std::string vshader = "../../src/glsl/vs.glsl";

std::string fshader = "../../src/glsl/fs.glsl";

glm::vec3 vertices[3] = {
	glm::vec3(-1.0f, -1.0f, 0.0f),
	glm::vec3(1.0f, -1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
};

glm::vec4 colors[3] = {
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
};

opengl::AttributeVariable instPosition;

glm::vec4 color = glm::vec4(0.99f, 0.99f, 0.99f, 0.99f);
float dColor = 0.00005f;
opengl::UniformVariable& ucolor = opengl::UniformVariable();
opengl::UniformVariable& projection = opengl::UniformVariable();

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
		vertexShader = opengl::ProgramFactory::CreateVertexShader(vertexSource);
		fragmentShader = opengl::ProgramFactory::CreateFragmentShader(fragmentSource);
		program = opengl::ProgramFactory::CreateProgram({ vertexShader, fragmentShader });
	}
	catch (opengl::shader_compilation_exception ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
	catch (opengl::program_link_exception ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}

	const opengl::AttributeVariable& position = program.GetAttributeVariable("position");
	const opengl::AttributeVariable& color = program.GetAttributeVariable("color");
	instPosition = program.GetAttributeVariable("inst_position");

	ucolor = program.GetUniformVariable("ucolor");
	projection = program.GetUniformVariable("projection");

	opengl::MeshDescriptor meshDesc;
	meshDesc.Vertices = std::vector<glm::vec3>(vertices, std::end(vertices));
	meshDesc.PositionVariable = position;

	opengl::VertexAttributeDescriptor colorDesc;
	colorDesc.pAttributes = &colors[0];
	colorDesc.Size = sizeof(colors);
	colorDesc.AttributeVariable = color;
	meshDesc.AttributeDescriptors.push_back(colorDesc);

	mesh = meshFactory.CreateStaticMesh(meshDesc);

	std::vector<opengl::VertexAttributeDescriptor> descriptors;

	opengl::VertexAttributeDescriptor instancePositionDesc;
	instancePositionDesc.AttributeVariable = instPosition;
	instancePositionDesc.pAttributes = (void*)1;
	instancePositionDesc.Size = 0;

	descriptors.push_back(instancePositionDesc);

	inMesh = meshFactory.CreateStaticInstancedMesh(meshDesc, descriptors);
}

void Render() {
	program.Use();

	if (color.x < 0.25f || color.x > 1.0f) {
		dColor *= -1;
	}

	color.x = color.x - dColor;
	color.y = color.y - dColor;
	color.z = color.z - dColor;

	glm::mat4 proj = glm::ortho(-10.0, 10.0, -10.0, 10.0);

	program.SetUniform(ucolor, color);
	program.SetUniform(projection, { proj });
	mesh.Render();

	std::vector<glm::vec3> instancePositions;
	instancePositions.push_back(glm::vec3(0.0f + std::sinf(color.x*90), 4.0f, 0.0f));
	instancePositions.push_back(glm::vec3(-2.0f, 2.0f + std::cosf(color.x * 90), 0.0f));
	instancePositions.push_back(glm::vec3(1.0f, 3.0f - std::sinf(color.x * 90), 0.0f));
	instancePositions.push_back(glm::vec3(4.0f + std::sinf(color.x * 90), -2.0f - 3 * std::cosf(color.x * 90) + 2 * std::sinf(color.x * 90), 0.0f));

	opengl::InstanceUpdateData instanceData;
	instanceData.Attribute = instPosition;
	instanceData.pData = glm::value_ptr(instancePositions[0]);
	instanceData.dataSize = sizeof(glm::vec3) * instancePositions.size();

	inMesh.SetInstancedData({ instanceData });
	inMesh.Render(instancePositions.size());
	opengl::OpenGlError error = opengl::GL::GetErrors();
	if (error.IsError()) {
		std::cout << error.ToString() << std::endl;
		exit(-1);
	}
}

int main() {
	std::cout.sync_with_stdio(false);
	HINSTANCE hInstance = GetModuleHandle(0);
	gfx::render::Window w(hInstance, "fli-app-1", glm::uvec2(100, 100), glm::uvec2(300, 300));

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

		gl.Clear(opengl::GL::Buffers::Color | opengl::GL::Buffers::Depth);

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