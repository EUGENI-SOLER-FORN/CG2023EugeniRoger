varying vec2 v_uv;
varying vec2 v_nextXColor;

uniform float u_width;
uniform float u_height;
uniform sampler2D u_image;
uniform float u_task;
uniform float u_time;
uniform float u_radius;
uniform float u_pixelRate;
uniform float u_flipped;

void main()
{
	vec4 pixelCol = texture2D(u_image, v_uv);
	gl_FragColor = pixelCol;
	
	if(u_task == 0) {
		vec2 rotated_uv = v_uv - vec2(0.5, 0.5);
		rotated_uv = vec2(rotated_uv.x * cos(u_time) - rotated_uv.y * sin(u_time), rotated_uv.x * sin(u_time) + rotated_uv.y * cos(u_time)); 
		rotated_uv += vec2(0.5, 0.5);
		vec4 rotatedCol = texture2D(u_image, rotated_uv);
		gl_FragColor = step(0, rotated_uv.x) * step(0, rotated_uv.y) * step(0, 1-rotated_uv.x) * step(0, 1-rotated_uv.y) *rotatedCol;
	}
	else if(u_task == 1) {
		gl_FragColor = texture2D(u_image, vec2(floor(v_uv.x * u_pixelRate)/u_pixelRate, floor(v_uv.y * u_pixelRate)/u_pixelRate));
	}
	else if(u_task == 2){
		gl_FragColor.x = texture2D(u_image, v_uv - vec2(u_radius)/u_height).x;
		gl_FragColor.y = texture2D(u_image, v_uv).y;
		gl_FragColor.z = texture2D(u_image, v_uv + vec2(u_radius)/u_height).z;
		gl_FragColor.w = 1.0;
	}
}
