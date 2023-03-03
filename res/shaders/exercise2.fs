varying vec2 v_uv;
varying vec2 v_nextXColor;

uniform float u_radius;
uniform float u_width;
uniform float u_height;
uniform float u_task;
uniform sampler2D u_image;

void main()
{
	gl_FragColor = vec4(1.0);

	vec4 pixelCol = texture2D(u_image, v_uv);
	vec4 blurred = pixelCol;
	
	if(u_task == 0) gl_FragColor = vec4((pixelCol.x + pixelCol.y + pixelCol.z)/3.0);
	
	else if(u_task == 1) gl_FragColor = 1.0 - pixelCol;
	
	else if(u_task == 2) gl_FragColor = vec4(1 - pixelCol.x, pixelCol.y, pixelCol.z * 0.5, pixelCol.w);
	
	else if(u_task == 3) gl_FragColor = vec4(step(0.5, (pixelCol.x + pixelCol.y + pixelCol.z)/3.0));
	
	else if(u_task == 4) {
		for(int i = 0; u_radius > i; i++) {
			blurred += texture2D(u_image, v_uv + vec2(i,0.0)/u_width);
			blurred += texture2D(u_image, v_uv - vec2(i,0.0)/u_width);
			blurred += texture2D(u_image, v_uv + vec2(0.0,i)/u_height);
			blurred += texture2D(u_image, v_uv - vec2(0.0,i)/u_height);
		}
		gl_FragColor = blurred / (4 * u_radius + 1.0);
	}

	else if(u_task == 5) gl_FragColor = pixelCol - vec4(distance(v_uv, vec2(0.5)) * inversesqrt(0.5));
}
