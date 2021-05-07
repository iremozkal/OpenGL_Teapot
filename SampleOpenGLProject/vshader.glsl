#version 150 
#define PI 3.14159

in vec4 vPosition; 
in vec4 vColor;
out vec4 color; 
uniform mat4 model_view; 
uniform mat4 projection; 
uniform float object;
uniform float theta_teapot;

void main() {	
	if(object == 0.0){ /*Surface*/
		mat4 tr = mat4(1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			-0.1, 0.3, 0.0, 1.0);

		mat4 rx = mat4(1.0, 0.0, 0.0, 0.0,
			0.0, cos((-90) * PI / 180), sin((-90) * PI / 180), 0.0,
			0.0, -sin((-90) * PI / 180), cos((-90) * PI / 180), 0.0,
			0.0, 0.0, 0.0, 1.0);

		gl_Position = projection * model_view * tr * rx * vPosition / vPosition.w;
		color = vec4(0.25, 0.25, 0.25, 1.0);

	}else{/*Teapot*/
		mat4 tr = mat4(1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, -0.1, 0.4, 1.0);

		mat4 sc = mat4(0.15, 0.0, 0.0, 0.0,
			0.0, 0.15, 0.0, 0.0,
			0.0, 0.0, 0.15, 0.0,
			0.0, 0.0, 0.0, 1.0);

		mat4 ry = mat4(cos((theta_teapot)* PI / 180), 0.0, -sin((theta_teapot)* PI / 180), 0.0,
			0.0, 1.0, 0.0, 0.0,
			sin((theta_teapot)* PI / 180), 0.0, cos((theta_teapot)* PI / 180), 0.0,
			0.0, 0.0, 0.0, 1.0);

		gl_Position = projection * model_view * tr * ry * sc * vPosition / vPosition.w;
		color = vec4(0.6, 0.6, 0.6, 1.0);
	}		
} 