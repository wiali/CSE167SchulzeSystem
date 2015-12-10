// shadertype=glsl
#version 130
// Once again, this preprocessor will only fail if your OpenGL version
// is horribly outdated.



uniform sampler2D color_texture;
uniform sampler2D normal_texture;

void main() {
// Extract the normal from the normal map
vec3 normal = normalize(texture2D(normal_texture, gl_TexCoord[0].st).rgb * 2.0 - 1.0);

// Determine where the light is positioned (this can be set however you like)
vec3 light_pos = normalize(vec3(0.0, 1.0, 10.5));

// Calculate the lighting diffuse value
float diffuse = max(dot(normal, light_pos), 0.0);

vec3 color = diffuse * texture2D(color_texture, gl_TexCoord[0].st).rgb;

// Set the output color of our current pixel
gl_FragColor = vec4(color, 1.0);
}

