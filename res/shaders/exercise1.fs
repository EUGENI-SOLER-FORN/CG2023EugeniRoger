varying vec2 v_position;
varying vec2 v_uv;

uniform float u_task;
uniform vec3 u_dimesions;

void main()
{
	gl_FragColor = vec4(1.0);

	if(u_task == 0) gl_FragColor = vec4(v_uv.x, 0.0 , 1.0-v_uv.x, 1.0);
	
	else if(u_task == 1) gl_FragColor = vec4(distance(v_position, vec2(0)));
	
	else if(u_task == 2) gl_FragColor = vec4(step(5, mod((v_position.x) * 15, 6) ), 0.0, step(5, mod((v_position.y) * 15, 6) ), 1.0);
	
	else if(u_task == 3) gl_FragColor = vec4(floor(v_uv.x * 10.0)/10, floor(v_uv.y * 10.0)/10, 0, 1);
	
	else if(u_task == 4) gl_FragColor = vec4(0, step(sin(v_position.x * 3.14), v_position.y * 3.14) *(1 - v_uv.y) + (1-step(sin(v_position.x*3.14), v_position.y * 3.14)) * v_uv.y, 0, 1);
	
	else if(u_task == 5) gl_FragColor = vec4(step(1, mod((v_position.x + 1) * 10, 2)) +(1- step(1, mod((v_position.y + 1) * 10, 2))) - 2 * step(1, mod((v_position.x + 1) * 10, 2)) * (1-step(1, mod((v_position.y + 1) * 10, 2))));
	
}
