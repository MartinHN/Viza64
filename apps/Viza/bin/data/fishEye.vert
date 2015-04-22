#version 120


#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_texture_rectangle : enable
#define GL_FRAGMENT_PRECISION_HIGH 1


uniform float maxradius;
uniform float strength;
uniform vec2 mouse;


varying vec4 vColor;

vec4 Distort(vec4 p,vec2 _center, float _radius, float _strength)
{
    vec2 v = (p.xy / p.w)  - _center;
    // Convert to polar coords:
    float radius = length(v) ;
    if (radius > 0 && radius<_radius)
    {
        float theta = atan(v.y,v.x);
        
        // Distort:
        radius = 	_radius*pow(radius/_radius, _strength);
        
        // Convert back to Cartesian:
        v.x = _center.x + radius * cos(theta);
        v.y = _center.y + radius * sin(theta);
        p.xy = v.xy * p.w;
    }
    return p;
}

void main()
{
    vec4 P = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position =  Distort(P,mouse,maxradius,strength);
    vColor = gl_Color;

}



