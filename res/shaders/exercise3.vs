varying vec2 v_uv;
varying vec2 v_position;

void main()
{	
	// Remember the UV's range [0.0, 1.0]
	v_uv = gl_MultiTexCoord0.xy;
	v_position = gl_Vertex.xy;
	gl_Position = gl_Vertex;
	
}