#version 330

uniform sampler2D texture;

in vec3 vs_normal;
in vec3 vs_camera;
in vec3 vs_lumiere;
in vec2 vs_vertexTexCoor;

out vec4 out_fragColor;

struct LightProperties
{
    vec3   vAmbiant;
    vec3   vDiffuse;
    vec3   vSpecular;
};
uniform LightProperties u_light;

struct MaterialProperties
{
    vec3   vAmbiant;
    vec3   vDiffuse;
    vec3   vSpecular;
    float  fSpecPower;
};
uniform MaterialProperties u_material;

vec3 ambientLighting()
{
    return u_light.vAmbiant;
}

vec3 diffuseLighting( in vec3 N, in vec3 L )
{
    float NdotL = dot( N, L );
    float diffuseTerm = clamp( NdotL, 0, 1 );
    return u_light.vDiffuse * diffuseTerm;
}

vec3 specularLightingGouraudPhong( in vec3 N, in vec3 L, in vec3 V )
{
    vec3 R = reflect(-L,N);
    float specularTerm = pow( max( dot( R, V ), 0.f ), u_material.fSpecPower );
    return u_material.vSpecular * u_light.vSpecular * specularTerm;
}

void main()
{
   vec3 L = normalize(vs_lumiere);
   vec3 V = normalize(vs_camera);
   vec3 N = normalize(vs_normal);

   vec3 Iamb = ambientLighting();
   vec3 Idif = diffuseLighting(N,L);
   vec3 Ispe = specularLightingGouraudPhong(N,L,V);

   vec3 ITex = texture2D(texture,vs_vertexTexCoor).rgb;

   out_fragColor = vec4((Idif+Iamb)*ITex+Ispe,1.0f);
   //On ajoute les composante de lumiere de Phong
}
