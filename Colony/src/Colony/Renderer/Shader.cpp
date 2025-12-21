#include "clpcl.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Colony
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// 创建一个新的顶点着色器句柄
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// 发送顶点着色器源码给GL
		// std::string的c_str是以空字符结尾的
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// 编译顶点着色器
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			CL_CORE_ERROR("{0}", infoLog.data());
			CL_CORE_ASSERT(false, "顶点着色器编译失败！");
			return;
		}

		// 创建一个新的片段着色器句柄
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// 发送片段着色器源码给GL
		// std::string的c_str是以空字符结尾的
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// 编译片段着色器
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			CL_CORE_ERROR("{0}", infoLog.data());
			CL_CORE_ASSERT(false, "片段着色器编译失败！");
			return;
		}

		// 顶点着色器和片段着色器编译成功
		// 下一步是链接到程序里
		// 创建一个程序对象
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// 将着色器附加到程序上
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// 链接程序
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			CL_CORE_ERROR("{0}", infoLog.data());
			CL_CORE_ASSERT(false, "着色器链接失败！");
			return;
		}

		// 在链接成功后分离着色器
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
