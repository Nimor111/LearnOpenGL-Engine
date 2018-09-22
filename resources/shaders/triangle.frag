#version 330 core
out vec4 FragColor;
/* in vec3 ourColor; */
in vec2 TexCoord;
/* in vec3 vertexPosition; */
//in vec4 vertexColor; // input from the vertex shader ( same name and type )

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float visibility;

void main()
{
    /* FragColor = vec4(ourColor, 1.0f); */
    FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(1 - TexCoord.x, TexCoord.y)), visibility);
    /* FragColor = vec4(vertexPosition, 1.0f); */
}
