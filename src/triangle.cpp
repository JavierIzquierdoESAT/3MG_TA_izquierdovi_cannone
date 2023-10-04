#include "triangle.hpp"
#include "../src/stdafx.hpp"

void paint(Triangle& t, Window& w) {

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

}