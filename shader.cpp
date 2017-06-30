#include "shader.h"

using namespace std;

Shader::Shader(const GLchar * vshader_path, const GLchar * fshader_path)
{
	string vshader_code;
	string fshader_code;
	
	ifstream vshader_file;
	ifstream fshader_file;

	vshader_file.exceptions (ifstream::failbit | ifstream::badbit);
	fshader_file.exceptions (ifstream::failbit | ifstream::badbit);


	try{
		vshader_file.open(vshader_path);
		fshader_file.open(fshader_path);
		
		stringstream vshader_stream, fshader_stream;

		vshader_stream << vshader_file.rdbuf();
		fshader_stream << fshader_file.rdbuf();

		vshader_file.close();
		fshader_file.close();

		vshader_code = vshader_stream.str();
		fshader_code = fshader_stream.str();
	}
	catch(ifstream::failure e){
		cout << "Error! Shader file couldn't be read." << endl;
	}
	
	const char * vertex_shader_code = vshader_code.c_str();
	const char * fragment_shader_code = fshader_code.c_str();


	unsigned int vshader, fshader;
	int success;
	char info_log[512];

	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vertex_shader_code, NULL);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vshader, 512, NULL, info_log);
		cout << "Error! Vertex shader compilation failed!\n"
		     << info_log
		     << endl;
	}

	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragment_shader_code, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fshader, 512, NULL, info_log);
		cout << "Error! Fragment shader compilation failed!\n"
		     << info_log
		     << endl;
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vshader);
	glAttachShader(this->ID, fshader);
	glLinkProgram(this->ID);
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(this->ID, 512, NULL, info_log);
		cout << "Error! Failed to link shader program.\n"
		     << info_log
		     << endl;

	}

	glDeleteShader(vshader);
	glDeleteShader(fshader);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
