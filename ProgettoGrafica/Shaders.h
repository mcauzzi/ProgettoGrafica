#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>

// Shader sources
const GLchar* vertexShipSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 position;"
"in vec3 normal;"
"in vec2 coord;"
"out vec3 Position;"
"out vec3 Normal;"
"out vec2 Coord;"
"uniform mat4 model;"
"uniform mat4 normal_matrix;"
"uniform mat4 view;"
"uniform mat4 projection;"
"void main() {"
"	Normal = vec3(normal_matrix * vec4(normal,0.0));"
"	Coord = vec2(coord.x, 1.0-coord.y);"
"	gl_Position = projection * view * model * vec4(position, 1.0);"
"	vec4 vertPos = model * vec4(position, 1.0);"
"	Position = vec3(vertPos)/vertPos.w;"
"}";

const GLchar* fragmentShipSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 Position;"
"in vec3 Normal;"
"in vec2 Coord;"
"out vec4 outColor;"
"uniform mat4 normal_matrix;"
"uniform float shininess;"
"uniform vec3 material_ambient;"
"uniform vec3 material_diffuse;"
"uniform vec3 material_specular;"
"uniform vec3 light_direction;"
"uniform vec3 light_intensity;"
"uniform vec3 view_position;"
"uniform vec3 light_position;"

"void main() {"
"	vec3 view_direction = normalize(view_position - Position);"
"	vec3 light_direction2 = normalize(light_position - Position);"
"	vec3 R = normalize(reflect(-light_direction, Normal));"
"	vec3 R2 = normalize(reflect(-light_direction2, Normal));"
"	outColor = vec4(material_ambient, 1);"
"	outColor += vec4(light_intensity*material_diffuse,1) * max(dot(light_direction, Normal), 0.0);"
"	outColor +=  vec4(light_intensity*material_specular,1) * pow(max(dot(R, view_direction), 0.0), shininess);"
"	outColor +=  vec4(light_intensity*material_diffuse,1)  * max(dot(light_direction2, Normal), 0.0);"
"	outColor +=  vec4(light_intensity*material_specular,1) * pow(max(dot(R2, view_direction), 0.0), shininess);"
"}";

const GLchar* vertexSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 position;"
"in vec3 normal;"
"in vec2 coord;"
"out vec3 Position;"
"out vec3 Normal;"
"out vec2 Coord;"
"uniform mat4 model;"
"uniform mat4 normal_matrix;"
"uniform mat4 view;"
"uniform mat4 projection;"
"void main() {"
"	Normal = vec3(normal_matrix * vec4(normal,0.0));"
"	Coord = vec2(coord.x, 1.0-coord.y);"
"	gl_Position = projection * view * model * vec4(position, 1.0);"
"	vec4 vertPos = model * vec4(position, 1.0);"
"	Position = vec3(vertPos)/vertPos.w;"
"}";

const GLchar* fragmentSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 Position;"
"in vec3 Normal;"
"in vec2 Coord;"
"out vec4 outColor;"
"uniform mat4 normal_matrix;"
"uniform float shininess;"
"uniform vec3 material_ambient;"
"uniform vec3 material_diffuse;"
"uniform vec3 material_specular;"
"uniform vec3 light_direction;"
"uniform vec3 light_intensity;"
"uniform vec3 view_position;"
"uniform vec3 light_position;"
"uniform sampler2D textureSampler;"
"void main() {"
"	vec3 view_direction = normalize(view_position - Position);"
"	vec3 light_direction2 = normalize(light_position - Position);"
"	vec3 R = normalize(reflect(-light_direction, Normal));"
"	vec3 R2 = normalize(reflect(-light_direction2, Normal));"
"	outColor = vec4(material_ambient, 1);"
"	outColor += vec4(light_intensity*material_diffuse,1) * texture(textureSampler, Coord) * max(dot(light_direction, Normal), 0.0);"
"	outColor +=  vec4(light_intensity*material_specular,1) * pow(max(dot(R, view_direction), 0.0), shininess);"
"	outColor +=  vec4(light_intensity*material_diffuse,1)  * texture(textureSampler, Coord)* max(dot(light_direction2, Normal), 0.0);"
"	outColor +=  vec4(light_intensity*material_specular,1) * pow(max(dot(R2, view_direction), 0.0), shininess);"
"}";

const GLchar* fragmentSource2 =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 Position;"
"in vec3 Normal;"
"in vec2 Coord;"
"out vec4 outColor;"
"uniform float shininess;"
"uniform vec3 material_ambient;"
"uniform vec3 material_diffuse;"
"uniform vec3 material_specular;"
"uniform vec3 light_direction;"
"uniform vec3 light_intensity;"
"uniform vec3 view_position;"
"uniform vec3 light_position;"

"void main() {"
"	vec3 light_direction2 = normalize(light_position - Position);"
"	outColor = vec4(light_intensity*material_diffuse,1) *max(dot(light_direction, normalize(Normal)), 0.0);"
"	outColor +=  vec4(light_intensity*material_diffuse,1)  * max(dot(light_direction2, normalize(Normal)), 0.0);"
"}";

// le posizioni passate formano gia' un cubo compreso tra [-1,-1,-1] e [1,1,1], l'intervallo cioe' del clip-space
// non dobbiamo quindi applicare nessuna trasformazione
// moltiplicando i vertici per l'inversa della view_matrix otteniamo un versore che punta lungo proiezione sferica del cubo, ed e' esattamente
// il tipo di coordinata richiesta per le texture di tipo cubemap
const GLchar* vertexSkySource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"uniform mat3 view_rot;"
"in vec3 position;"
"out vec3 Coord;"
"void main() {"
"	Coord = view_rot * position;"
"	gl_Position = vec4(position, 1.0);"
"}";

const GLchar* fragmentSkySource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 Coord;"
"out vec4 outColor;"
"uniform samplerCube textureSampler;"
"void main() {"
"	outColor =  texture(textureSampler, Coord);"
"}";

// visto che passiamo un quadrato con le coordinate gia' all'interno dell'intervallo -1,1 (clip-space) non dobbiamo applicare nessuna trasformazione
const GLchar* vertexGuiSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec2 position;"
"in vec2 coord;"
"out vec2 Coord;"
"uniform float size;"
"void main() {"
"	Coord = vec2(coord.x, 1.0-coord.y);"
"	gl_Position = vec4(position, 0.0, 1.0);"
"}";

// shader per il rendering del quadrato con la texture per il pulsante
const GLchar* fragmentGuiSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec2 Coord;"
"out vec4 outColor;"
"uniform sampler2D textureSampler;"
"void main() {"
"outColor =  texture(textureSampler, Coord);"
"}";


const GLchar* groundVertexSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 position;"
"in vec3 color;"
"in vec2 coord;"
"out vec3 Color;"
"out vec2 Coord;"
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection;"
"void main() {"
"   Color = color;"
"   Coord = coord;"
"   gl_Position = projection * view * model * vec4(position, 1.0);"
"}";

const GLchar* finishVertexSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 position;"
"in vec3 normal;"
"in vec2 coord;"
"out vec3 Position;"
"out vec3 Normal;"
"out vec2 Coord;"
"uniform mat4 model;"
"uniform mat4 normal_matrix;"
"uniform mat4 view;"
"uniform mat4 projection;"
"void main() {"
"	Normal = vec3(normal_matrix * vec4(normal,0.0));"
"	Coord = vec2(coord.x, 1.0-coord.y);"
"	gl_Position = projection * view * model * vec4(position, 1.0);"
"	vec4 vertPos = model * vec4(position, 1.0);"
"	Position = vec3(vertPos)/vertPos.w;"
"}";

const GLchar* finishFragmentSource =
#if defined(__APPLE_CC__)
"#version 150 core\n"
#else
"#version 130\n"
#endif
"in vec3 Position;"
"in vec3 Normal;"
"in vec2 Coord;"
"uniform float Time;"
"out vec4 outColor;"
"uniform mat4 normal_matrix;"
"uniform float shininess;"
"uniform vec3 material_ambient;"
"uniform vec3 material_diffuse;"
"uniform vec3 material_specular;"
"uniform vec3 light_direction;"
"uniform vec3 light_intensity;"
"uniform vec3 view_position;"
"uniform vec3 light_position;"
"uniform sampler2D textureSampler;"
"void main() {"
"	vec3 view_direction = normalize(view_position - Position);"
"	vec3 light_direction2 = normalize(light_position - Position);"
"	vec3 R = normalize(reflect(-light_direction, Normal));"
"	vec3 R2 = normalize(reflect(-light_direction2, Normal));"
"	outColor = vec4(material_ambient,1);"
"	outColor += vec4(light_intensity*material_diffuse*vec3(sin(10*Time)/2+0.5f, cos(10*Time+3.14/2)/2+0.5f, cos(10*Time)/2+0.5f),1) * texture(textureSampler, Coord) * max(dot(light_direction, Normal), 0.0);"
"	outColor +=  vec4(light_intensity*material_specular,1) * pow(max(dot(R, view_direction), 0.0), shininess);"
"	outColor +=  vec4(light_intensity*material_diffuse*vec3(sin(10*Time)/2+0.5f, cos(10*Time+3.14/2)/2+0.5f, cos(10*Time)/2+0.5f),1)  * texture(textureSampler, Coord)* max(dot(light_direction2, Normal), 0.0);"
"	outColor +=  vec4(light_intensity*material_specular,1) * pow(max(dot(R2, view_direction), 0.0), shininess);"
"}";

#endif
