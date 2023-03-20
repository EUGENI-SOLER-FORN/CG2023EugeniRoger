// Global variables from the CPU
// Variables to pass to the fragment shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec4 v_final_color;

//here create uniforms for all the data we need here
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

void main()
{	
	v_uv = gl_MultiTexCoord0.xy;

	// Convert local position to world space
	vec3 world_position = (u_model * vec4( gl_Vertex.xyz, 1.0)).xyz;

	// Convert local normal to world space
	vec3 world_normal = (u_model * vec4( gl_Normal.xyz, 0.0)).xyz;

	// Pass them to the fragment shader interpolated
	v_world_position = world_position;
	v_world_normal = world_normal;

	vec3 N = normalize(world_normal);
	vec3 L = normalize(u_light_position - world_position);
	vec3 V = normalize(u_eye_position - world_position);
	vec3 R = normalize(reflect(-L, N));
	
	vec4 K_a = vec4(u_K_a, 1);
	vec4 K_d = vec4(u_K_d, 1);
	vec4 K_s = vec4(u_K_s, 1);

	if(u_apply_texture == 1.0){
		K_d = texture2D(u_texture, v_uv);
		K_a = K_d;
		K_s = vec4(texture2D(u_texture, v_uv).w);
	}

	vec4 I_p = vec4(u_I_a, 1) * K_a; // Bsse color
	I_p += K_d * vec4(u_I_d, 1) * clamp(dot(L, N), 0, 1); // Diffuse
	I_p += K_s * vec4(u_I_s, 1) * pow(clamp(dot(R, V), 0, 1), u_shine); // Specular
	
	v_final_color = I_p;

	// Project the vertex using the model view projection matrix
	gl_Position = u_viewprojection * vec4(world_position, 1.0); //output of the vertex shader
}