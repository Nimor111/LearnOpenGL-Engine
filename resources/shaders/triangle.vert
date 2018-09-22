#version 330 core
layout (location = 0) in vec3 aPos; // attr position 0
/* layout (location = 1) in vec3 aColor; // attr position 1 */
layout (location = 1) in vec2 aTexCoord; // attr position 2

// passing the colour to the fragment shader
//out vec4 vertexColor; // a colour output for the fragment shader

out vec3 ourColor; // output a colour to the fragment shader
/* out vec3 vertexPosition; */
out vec2 TexCoord;

/* uniform float xOffset; */
/* uniform mat4 transform; */
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    /* gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0); */
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    /* vertexPosition = aPos; */
    TexCoord = aTexCoord;
    /* ourColor = aColor; */
 //   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}
