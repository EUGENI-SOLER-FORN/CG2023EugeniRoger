// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec3 v_world_normal;
varying vec3 v_world_position;
varying vec2 v_uv;

uniform vec3 u_eye_position;

uniform mat4 u_model;
uniform mat4 u_viewprojection;

uniform float u_shine;
uniform vec3 u_K_a;
uniform vec3 u_K_d;
uniform vec3 u_K_s;

uniform vec3 u_light_position;
uniform vec3 u_I_a;
uniform vec3 u_I_d;
uniform vec3 u_I_s;

uniform float u_apply_texture;
uniform sampler2D u_texture;
uniform sampler2D u_texture_normals;

void main()
{
	vec4 K_a = vec4(u_K_a, 1);
	vec4 K_d = vec4(u_K_d, 1);
	vec4 K_s = vec4(u_K_s, 1);

	vec3 n = normalize(v_world_normal.xyz);

	if(u_apply_texture == 1.0){
		K_d = texture2D(u_texture, v_uv);
		K_a = K_d;
		K_s = vec4(texture2D(u_texture, v_uv).w);

		n = texture2D(u_texture_normals, v_uv).xyz;
		n = n * 2 - vec3(1.0);
		n = (u_model * vec4(n, 0.0)).xyz;
	}

	vec3 N = n;
	vec3 L = normalize(u_light_position - v_world_position);
	vec3 V = normalize(u_eye_position - v_world_position);
	vec3 R = normalize(reflect(-L, N));

	vec4 I_p = vec4(u_I_a, 1) * K_a; // Bsse color
	I_p += K_d* vec4(u_I_d, 1) * dot(L, N); // Diffuse
	I_p += K_s * vec4(u_I_s, 1) * pow(dot(R, V), u_shine); // Specular


	// Set the ouput color per pixel
	gl_FragColor =  I_p; //texture2D(u_texture, v_uv); 
}
