// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec3 v_world_normal;
varying vec3 v_world_position;
varying vec2 v_uv;
varying vec4 v_final_color;

uniform float u_shine;
uniform vec3 u_K_a;
uniform vec3 u_K_d;
uniform vec3 u_K_s;

uniform vec3 u_I_a;
uniform vec3 u_I_d;
uniform vec3 u_I_s;


void main()
{
	// Set the ouput color per pixel
	gl_FragColor = v_final_color; //texture2D(u_texture, v_uv); 
}
