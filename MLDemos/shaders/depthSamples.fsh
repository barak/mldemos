#version 120
#extension GL_EXT_gpu_shader4 : require

const float Near = 1.0;
const float Far = 60.0;
const float Depth = 1.0 / (Far - Near);

uniform sampler2D color_texture;

flat varying vec4 lvec;

vec4 pack (float depth)
{
    const vec4 bias = vec4(1.0 / 255.0,
                1.0 / 255.0,
                1.0 / 255.0,
                0.0);

    float r = depth;
    float g = fract(r * 255.0);
    float b = fract(g * 255.0);
    float a = fract(b * 255.0);
    vec4 colour = vec4(r, g, b, a);

    return colour - (colour.yzww * bias);
}

void main()
{
    vec2 pos = gl_PointCoord.xy-vec2(0.5,0.5);
    float radius = dot(pos,pos);
    if(radius > 0.21) discard;
    float z = (lvec.z / lvec.w);
    gl_FragColor = texture2D(color_texture, gl_PointCoord.xy);
    if(gl_FragColor.a < 0.001) discard;
    gl_FragColor = vec4(z,z,z,1);
//    gl_FragColor = pack(z);
    return;
}
