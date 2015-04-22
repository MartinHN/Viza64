#version 120
#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_texture_rectangle : enable
#define GL_FRAGMENT_PRECISION_HIGH 1


varying vec4 vColor;

void main(){
//    vec2 st = 2*gl_PointCoord.st-vec2(1,1);
//    float curalpha = vColor.w;//*max(0.1,(1-length(st)));//max(0.f,1.f-texture2DRect(Tex,vec2(l,1)).x);
    
    
    gl_FragColor = vColor;//vec4(vColor.xyz,curalpha*curalpha*(3.0 - 2.0 * curalpha));
}
