varying vec2 v_uv;
uniform float task;

void main()
{
	gl_FragColor = vec4(1.0);
	
	gl_FragColor = vec4(v_uv.x, 0.0 , 1.0-v_uv.x, 1.0);
}
