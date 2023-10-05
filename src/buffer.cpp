#include "buffer.hpp"
#include "GL/glew.h"

Buffer::Buffer() : buffer_id_{0}, size_{0}, vertex_array_id_{0} {}


Buffer::~Buffer()
{
	release();
}

void Buffer::init(unsigned int size)
{

		size_ = size;
		glGenBuffers(1, &buffer_id_);
    bindBuffer(kTarget_Vertex_Data);
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	

}

void Buffer::initWithData(const void* data, unsigned int size)
{
	
		size_ = size;
		glGenBuffers(1, &buffer_id_);
		bindBuffer(kTarget_Vertex_Data);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	
}

void Buffer::bindBuffer(const Target t)
{
	switch (t)
	{
	case kTarget_Vertex_Data: {
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
		break;
	}

	case kTarget_Elements: {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
		break;
	}
	default:
		printf("Bind buffer target not valid");
		break;
	}
}

void Buffer::bindVertexArray() { glBindVertexArray(vertex_array_id_); }

unsigned int Buffer::size() const
{
	return size_;
}

void Buffer::uploadData(const void* data, unsigned int size, unsigned int offset)
{

	bindBuffer(kTarget_Vertex_Data);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void Buffer::release()
{
	
		glDeleteBuffers(1, &buffer_id_);
    glDeleteVertexArrays(1, &vertex_array_id_);
		buffer_id_ = 0;
    vertex_array_id_ = 0;
		size_ = 0;
	
}

void Buffer::enableVertexArray(const unsigned int size,
                                   const unsigned int stride,
																	 const unsigned int offset) {

    glGenVertexArrays(1, &vertex_array_id_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

		bindVertexArray();
	
}


unsigned Buffer::buffer_id() const { return buffer_id_; }
